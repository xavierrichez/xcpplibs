//---------------------------------------------------------------------------
//
// Name:        wxDummyProgramFrame.h
// Author:      
// Created:     10/27/2004 12:22:10 AM
// Copyright:
//
//---------------------------------------------------------------------------
#ifndef __wxDummyPROGRAMFRAME_HPP_
#define __wxDummyPROGRAMFRAME_HPP_


#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif



////Header Include Start
#include <wx/dirdlg.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
////Header Include End

#include <wx/frame.h>

////GUI Control ID Start
#define ID_BUTTONCANCEL 1157
#define ID_BUTTONOK 1156
#define ID_WXBOXSIZER2 1120
#define ID_BUTTONOPEN 1165
#define ID_EDITOPEN 1164
#define ID_STATICTEXTDESTINATION 1167
#define ID_WXBOXSIZER3 1121
#define ID_COMBOBOXUNITS 1161
#define ID_EDITCAPACITE 1160
#define ID_STATICTEXTCAPACITE 1166
#define ID_WXBOXSIZER4 1122
#define ID_WXBOXSIZER1 1113
////GUI Control ID End

////Dialog Style Start
	#define THIS_DIALOG_STYLE wxCAPTION | wxSYSTEM_MENU | wxTHICK_FRAME | wxSTAY_ON_TOP | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX |  wxCLOSE_BOX
////Dialog Style End

class wxDummyProgramFrame : public wxFrame
{
private:
    DECLARE_EVENT_TABLE()
    bool DirInitialized;
public:
    wxDummyProgramFrame( wxWindow *parent, wxWindowID id = 1,
                         const wxString &title = _T("wxDummyProgramFrame"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = THIS_DIALOG_STYLE);
    virtual ~wxDummyProgramFrame();
public:
  ////GUI Control Declaration Start
	wxDirDialog *DirDialogChoice;
	wxButton *ButtonCancel;
	wxButton *ButtonOK;
	wxBoxSizer *WxBoxSizer2;
	wxButton *ButtonOpen;
	wxTextCtrl *EditOpen;
	wxStaticText *StaticTextDestination;
	wxBoxSizer *WxBoxSizer3;
	wxComboBox *ComboBoxUnits;
	wxTextCtrl *EditCapacite;
	wxStaticText *StaticTextCapacite;
	wxBoxSizer *WxBoxSizer4;
	wxBoxSizer *WxBoxSizer1;
  ////GUI Control Declaration End

public:
    void wxDummyProgramFrameClose(wxCloseEvent &event);
    void CreateGUIControls(void);
    void wxDummyProgramFrameResize(wxSizeEvent &event);
    void wxDummyProgramFrameOpen(wxCommandEvent &event);
	void wxDummyProgramFrameEdit(wxCommandEvent &event);    
    void wxDummyProgramFrameCancel(wxCommandEvent &event);
    void wxDummyProgramFrameRun(wxCommandEvent &event);    
};


#endif
 
 
 
 
