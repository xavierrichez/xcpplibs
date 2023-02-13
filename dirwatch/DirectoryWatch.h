/*
* multithreaded directory watcher
* applicable only on Windows or MacOS, as Linux has inotify
* @see also https://github.com/emcrisostomo/fswatch
*/
#pragma once

#include <thread>
#include <string>
#include <filesystem>
#include <functional>
#include <unordered_map>

class DirectoryWatcher
{
public:
    DirectoryWatcher(std::string iPath, int iRefreshDelayInMs);

	void Watch();

	void OnCreate(const std::function<void(std::string)>& action);
	void OnUpdate(const std::function<void(std::string)>& action);
	void OnDelete(const std::function<void(std::string)>& action);

private:
	// input params
	std::string mWatchedDirectory;
	int mRefreshDelayMs;

	// action functions
	std::function<void(std::string)> mOnCreate;
	std::function<void(std::string)> mOnUpdate;
	std::function<void(std::string)> mOnDelete;

	// file list
	std::unordered_map<std::string, std::filesystem::file_time_type> mDirMap;
};