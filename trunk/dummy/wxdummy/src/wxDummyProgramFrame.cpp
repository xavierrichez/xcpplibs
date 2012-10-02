//---------------------------------------------------------------------------
//
// Name:        wxDummyProgramFrame.cpp
// Author:      
// Created:     10/27/2004 12:22:10 AM
// Copyright:
//
//---------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "wxDummyProgramFrame.cpp"
#endif

/* for compilers that support precompilation
   includes "wx/wx.h" */

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


#include "wxDummyProgramFrame.h"

////Header Include Start
////Header Include End


//----------------------------------------------------------------------------
// wxDummyProgramFrame
//----------------------------------------------------------------------------

    ////Event Table Start
BEGIN_EVENT_TABLE(wxDummyProgramFrame,wxFrame)
	////Manual Code Start
	EVT_CLOSE(wxDummyProgramFrame::wxDummyProgramFrameClose)
	//EVT_SIZE(wxDummyProgramFrame::wxDummyProgramFrameResize)
	EVT_BUTTON(ID_BUTTONOPEN, wxDummyProgramFrame::wxDummyProgramFrameOpen)
	EVT_TEXT(ID_EDITOPEN, wxDummyProgramFrame::wxDummyProgramFrameEdit)
	EVT_BUTTON(ID_BUTTONCANCEL, wxDummyProgramFrame::wxDummyProgramFrameCancel)
	EVT_BUTTON(ID_BUTTONOK, wxDummyProgramFrame::wxDummyProgramFrameRun)
	////Manual Code End
END_EVENT_TABLE()
    ////Event Table End



wxDummyProgramFrame::wxDummyProgramFrame( wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
    : wxFrame( parent, id, title, position, size, style),
    DirInitialized(false)
{
    CreateGUIControls();
}

wxDummyProgramFrame::~wxDummyProgramFrame()
{

} 

void wxDummyProgramFrame::CreateGUIControls(void)
{
    ////GUI Items Creation Start

	wxBoxSizer* WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(TRUE);

	wxBoxSizer* WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer4,1,wxGROW | wxALL,1);

	StaticTextCapacite =  new wxStaticText(this, ID_STATICTEXTCAPACITE ,_("Capacite"), wxPoint(1,1), wxSize(89,25)  );
	StaticTextCapacite->SetFont(wxFont(14, wxSWISS ,wxNORMAL,wxNORMAL,FALSE,_T("Times New Roman")));
	WxBoxSizer4->Add(StaticTextCapacite,0,wxALIGN_TOP | wxALL,5);

	EditCapacite =  new wxTextCtrl(this, ID_EDITCAPACITE, _("1024") , wxPoint(92,3), wxSize(150,24) );
	WxBoxSizer4->Add(EditCapacite,1,wxGROW | wxALL,5);

	wxArrayString arrayStringFor_ComboBoxUnits;
	arrayStringFor_ComboBoxUnits.Add(_("octets"));
	arrayStringFor_ComboBoxUnits.Add(_("Ko"));
	arrayStringFor_ComboBoxUnits.Add(_("Mo"));
	arrayStringFor_ComboBoxUnits.Add(_("Go"));
	ComboBoxUnits =  new wxComboBox(this, ID_COMBOBOXUNITS ,_("octets") ,wxPoint(244,3), wxSize(81,24), arrayStringFor_ComboBoxUnits   );
	WxBoxSizer4->Add(ComboBoxUnits,0,wxGROW | wxALL,5);

	wxBoxSizer* WxBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer3,1,wxGROW | wxALL,1);

	StaticTextDestination =  new wxStaticText(this, ID_STATICTEXTDESTINATION, _("Destination"), wxPoint(1,1),  wxSize(87,25) );
	StaticTextDestination->SetFont(wxFont(14, wxSWISS ,wxNORMAL ,wxNORMAL ,FALSE ,_T("Times New Roman")));
	WxBoxSizer3->Add(StaticTextDestination,0,wxALIGN_TOP | wxALL,5);

	EditOpen =  new wxTextCtrl(this, ID_EDITOPEN, _("./dummy.file"),  wxPoint(90,3),wxSize(200,24) );
	WxBoxSizer3->Add(EditOpen,1,wxGROW | wxALL,5);

	ButtonOpen =  new wxButton(this, ID_BUTTONOPEN, _("..."),  wxPoint(292,3), wxSize(33,28) );
	ButtonOpen->SetFont(wxFont(12, wxSWISS ,wxNORMAL,wxNORMAL,FALSE,_T("Times New Roman")));
	WxBoxSizer3->Add(ButtonOpen,0,wxALIGN_TOP | wxALL,5);

	wxBoxSizer* WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2,0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);

	ButtonOK =  new wxButton(this, ID_BUTTONOK, _("&OK"),  wxPoint(5,5), wxSize(51,28)  ,  wxCLIP_CHILDREN );
	ButtonOK->SetFont(wxFont(12, wxSWISS ,wxNORMAL,wxNORMAL,FALSE,_T("Times New Roman")));
	WxBoxSizer2->Add(ButtonOK,0,wxALIGN_CENTER_VERTICAL | wxALL,5);

	ButtonCancel =  new wxButton(this, ID_BUTTONCANCEL, _("&Annuler") , wxPoint(66,5),wxSize(74,28) );
	ButtonCancel->SetFont(wxFont(12, wxSWISS ,wxNORMAL,wxNORMAL,FALSE,_T("Times New Roman")));
	WxBoxSizer2->Add(ButtonCancel,0,wxALIGN_CENTER_VERTICAL | wxALL,5);

	DirDialogChoice =  new wxDirDialog(this, "Système de fichiers cible" , "."  );

	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	this->SetTitle(_("wxDummy"));
	this->Center();
	this->SetIcon(wxNullIcon);
	
    ////GUI Items Creation End
}

void wxDummyProgramFrame::wxDummyProgramFrameClose(wxCloseEvent& event)
{
    // --> Don't use Close with a Frame,
    // use Destroy instead.
    Destroy();
}

void wxDummyProgramFrame::wxDummyProgramFrameCancel(wxCommandEvent &event)
{
    Destroy();
}
 
/*void wxDummyProgramFrame::wxDummyProgramFrameResize(wxSizeEvent& event)
{;}*/

void wxDummyProgramFrame::wxDummyProgramFrameOpen(wxCommandEvent &event)
{
     if (DirDialogChoice->ShowModal() == wxID_OK)
     {
			EditOpen->SetValue(DirDialogChoice->GetPath());
			DirInitialized=true;
     }
}

void wxDummyProgramFrame::wxDummyProgramFrameEdit(wxCommandEvent &event)
{
	DirInitialized=true;
}

void wxDummyProgramFrame::wxDummyProgramFrameRun(wxCommandEvent &event)
{
	if (DirInitialized)
	{
		wxString command("dummy ");
		command << EditCapacite->GetValue() << ' ';
		char unit=ComboBoxUnits->GetValue().c_str()[0];
		command << unit << ' ' << EditOpen->GetValue() << '\n';
		system(command.c_str());
	}
}
