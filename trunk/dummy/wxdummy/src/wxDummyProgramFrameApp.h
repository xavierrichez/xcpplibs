//---------------------------------------------------------------------------
//
// Name:        wxDummyProgramFrameApp.h
// Author:      Guru Kathiresan
// Created:     12/10/2003 9:47:07 PM
// Copyright:
//
//---------------------------------------------------------------------------


#include <wx/wx.h>

class wxDummyProgramFrameApp:public wxApp
{
public:
	bool OnInit();
	int OnExit();
	int OnButtonOKClick();
};

