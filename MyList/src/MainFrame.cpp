#include "MainFrame.h"
#include "Constants.h"

#include "ListManager.h"
#include "List.h"

	/*
	m_MainPanel
		ListFolder
			ListPanel
				ListElements
		ListPanel
			ListElements
	*/

enum {
	wxID_LOAD = 10000,
	wxID_NEW_LIST,
	wxID_NEW_ELEMENT,
};

MainFrame::MainFrame() 
	: wxFrame(nullptr, wxID_ANY, "MyListApp", wxDefaultPosition, mfnWINDOW_SIZE)
{
	SetMinClientSize(wxSize(mfnWINDOW_WIDTH/2, mfnWINDOW_HEIGHT/2));

	// MenuBar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(wxID_LOAD, "&Load list\tCtrl+l");
	fileMenu->AppendSeparator();

	fileMenu->Append(wxID_NEW_LIST, "&New List\tCtrl+Shift+n");
	fileMenu->Append(wxID_NEW_ELEMENT, "&New Element\tCtrl+n");
	fileMenu->AppendSeparator();

	fileMenu->Append(wxID_EXIT, "&Exit\tEsc");
	menuBar->Append(fileMenu, "&File");
	SetMenuBar(menuBar);

	// Bind MenuBar Events
	Bind(wxEVT_MENU, [&](wxCommandEvent& evt) {
		wxMessageBox("Create new list here!"); 
		}, wxID_NEW_LIST);
	Bind(wxEVT_MENU, [&](wxCommandEvent& evt) {
		onMenuNewElement();
		}, wxID_NEW_ELEMENT);
	Bind(wxEVT_MENU, [&](wxCommandEvent& evt) { wxMessageBox("Load list here!"); }, wxID_LOAD);
	Bind(wxEVT_MENU, [&](wxCommandEvent& evt) { Close(true); }, wxID_EXIT);

	// Key bindings
	Bind(wxEVT_CHAR_HOOK, &MainFrame::onKeyPress, this);

	m_MainPanel = new wxPanel(this, wxID_ANY);
	m_MainSizer = new wxBoxSizer(wxVERTICAL);
	m_ListManager = new ListManager(this);
	m_MainPanel->SetBackgroundColour(mfnPRIMARY_BACKGROUND_COLOUR);


	m_MainPanel->SetSizer(m_MainSizer);
	m_MainSizer->FitInside(m_MainPanel);
}


void MainFrame::onKeyPress(wxKeyEvent& evt) {
	evt.Skip();
}

void MainFrame::onMenuNewElement() {

	wxDialog* dialog = new wxDialog(this, wxID_ANY, "New Element");
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	wxTextCtrl* titleTC = new wxTextCtrl(dialog, wxID_ANY, "New item", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	titleTC->SetMinSize(wxSize(300, -1));
	titleTC->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent& evt) {
		m_ListManager->getCurrentList()->addElement(titleTC->GetValue());
		dialog->Destroy();
		});
	dialogSizer->Add(titleTC, wxSizerFlags(1).CenterHorizontal().Border(wxALL, 5));


	wxPanel* btnPanel = new wxPanel(dialog, wxID_ANY);
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* btnCancel = new wxButton(btnPanel, wxID_ANY, "CANCEL");
	btnCancel->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
		dialog->Destroy();
		});
	btnSizer->Add(btnCancel, wxSizerFlags(1).Expand().Border(wxRIGHT, 2));

	wxButton* btnAdd = new wxButton(btnPanel, wxID_ANY, "ADD");
	btnAdd->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) { 
		m_ListManager->getCurrentList()->addElement(titleTC->GetValue());
		dialog->Destroy();
		});
	btnSizer->Add(btnAdd, wxSizerFlags(1).Expand().Border(wxLEFT, 2));

	btnPanel->SetSizer(btnSizer);
	dialogSizer->Add(btnPanel, wxSizerFlags(1).Expand().Border(wxALL, 5));


	dialog->SetSizerAndFit(dialogSizer);
	dialog->CenterOnParent();
	dialog->ShowModal();
}