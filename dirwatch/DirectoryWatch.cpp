/*
* multithreaded directory watcher
* applicable only on Windows or MacOS, as Linux has inotify
* @see also https://github.com/emcrisostomo/fswatch
*/

#include "DirectoryWatch.h"
#include <iostream>
#include <vector>

static void created(const std::string &path)
{
    printf("created '%s'\n", path.c_str());
}

static void updated(const std::string& path)
{
    printf("updated '%s'\n", path.c_str());
}

static void deleted(const std::string& path)
{
    printf("deleted '%s'\n", path.c_str());
}

DirectoryWatcher::DirectoryWatcher(std::string iPath, int iRefreshDelayInMs) :
    mWatchedDirectory(iPath),
    mRefreshDelayMs(iRefreshDelayInMs),
    mOnCreate(created),
    mOnUpdate(updated),
    mOnDelete(deleted)
{
}

void DirectoryWatcher::Watch()
{
    if( !std::filesystem::is_directory(std::filesystem::path(mWatchedDirectory) ) )
    {
        printf("not a regular directory %s\n", mWatchedDirectory.c_str());
        return;
    }
    printf("watching %s\n", mWatchedDirectory.c_str());
    // save all the directory entries to the list
    try {
        for (auto entry : std::filesystem::recursive_directory_iterator(mWatchedDirectory, std::filesystem::directory_options::skip_permission_denied))
        {
            try {
                mDirMap[entry.path().string()] = std::filesystem::last_write_time(entry);
            }
            catch (const std::filesystem::filesystem_error& ex)
            {
                std::cout << "Exception: " << ex.what() << '\n';
            }
        }
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(mRefreshDelayMs));

            auto it = mDirMap.begin();
            while (it != mDirMap.end())
            {   // check the existing directory list
                std::string path = it->first;
                if (!std::filesystem::exists(it->first))
                {   // file deleted
                    mOnDelete(it->first);
                    it = mDirMap.erase(it);
                }
                else
                {
                    it++;
                }
            }

            // Check if a file was created or modified
            for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(mWatchedDirectory, std::filesystem::directory_options::skip_permission_denied))
            {
                if (entry.is_directory())
                    continue; // skip

                auto lastWriteTime = std::filesystem::last_write_time(entry);
                std::string path = entry.path().string();

                if (!mDirMap.count(path))
                {   // new file created
                    mDirMap[path] = lastWriteTime;
                    mOnCreate(path);
                }
                else
                {
                    if (mDirMap[path] != lastWriteTime)
                    {   // file modified
                        mDirMap[path] = lastWriteTime;
                        mOnUpdate(path);
                    }
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        std::cout << "Exception: " << ex.what() << '\n';
    }
}

void WatchFun(std::string iPath, int iRefreshDelayInMs)
{
    DirectoryWatcher watcher(iPath, iRefreshDelayInMs);
    watcher.Watch();
}


int main() {
    std::setvbuf(stdout, NULL, _IONBF, 0); //< otherwise printf sucks on windows

    // TODO: get the dir list from the command line
    std::vector<std::string> dirList = { "./" };// , "c:\\Users\\Me"};
    std::vector<std::thread> threadList;
    for( std::string dir : dirList )
    {
        std::thread t(WatchFun, dir, 500);
        threadList.push_back(std::move(t));
    }
    for( int i=0; i<threadList.size(); i++ )
    {
        if (threadList.at(i).joinable())
        {
            printf("terminate %d\n", i);
            threadList.at(i).join();
        }
        else
            printf("cant join %d\n", i);
    }
}
