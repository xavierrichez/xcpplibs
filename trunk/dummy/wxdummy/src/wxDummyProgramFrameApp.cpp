//---------------------------------------------------------------------------
//
// Name:        wxDummyProgramFrameApp.cpp
// Author:      Guru Kathiresan
// Created:     12/10/2003 9:47:07 PM
// Copyright:
//
//---------------------------------------------------------------------------
#include "wxDummyProgramFrameApp.h"
#include "wxDummyProgramFrame.h"

IMPLEMENT_APP(wxDummyProgramFrameApp)

bool wxDummyProgramFrameApp::OnInit()
{
	wxDummyProgramFrame *myFrame = new wxDummyProgramFrame(NULL);
	SetTopWindow(myFrame);
	myFrame->Show(TRUE);
	return TRUE;
}
 
int wxDummyProgramFrameApp::OnExit()
{
	return 0;
}

