#include "ListElement.h"
#include "Constants.h"

#include "MainFrame.h"
#include "ListManager.h"
#include "List.h"

#include <algorithm>


int elemWidth = 300;
int elemHeight = 50;
wxSize elemSize(elemWidth, elemHeight);

ListElement::ListElement(List* list, wxString title, Status status)
	: wxPanel(list->getListPanel(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 2621440L, "MainListElementPanel"),
	  m_List(list),
	  m_Title(title), m_Status(status)
{
	SetBackgroundColour(mfnTERTIARY_BACKGROUND_COLOUR);

	wxBoxSizer* elementSizer = new wxBoxSizer(wxHORIZONTAL);

	// everything rendered inside the ListElement
	m_ToggleButton = new wxButton(this, wxID_ANY, UNICODE_CHECKBOX_UNCHECKED, wxDefaultPosition, wxSize(elemHeight, elemHeight));
	m_ToggleButton->SetFont(m_ToggleButton->GetFont().Scale(3));
	if (m_Status == Status::DONE)
		m_ToggleButton->SetLabel(UNICODE_CHECKBOX_CHECKED);
	m_ToggleButton->Bind(wxEVT_BUTTON, &ListElement::onToggleStatus, this);
	elementSizer->Add(m_ToggleButton, wxSizerFlags().Border(wxALL, 2));

	m_TitleST = new wxStaticText(this, wxID_ANY, m_Title);
	m_TitleST->SetForegroundColour(mfnSECONDARY_TEXT_COLOUR);
	m_TitleST->SetFont(m_TitleST->GetFont().Scale(2));
	m_TitleST->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction) &ListElement::onClickPanel, NULL, this);
	elementSizer->Add(m_TitleST, wxSizerFlags(1).CenterVertical().Border(wxLEFT, 5));

	wxButton* deleteButton = new wxButton(this, wxID_ANY, "X", wxDefaultPosition, wxSize(elemHeight, elemHeight));
	deleteButton->Bind(wxEVT_BUTTON, &ListElement::onDelete, this);
	deleteButton->SetBackgroundColour(*wxRED);
	deleteButton->SetForegroundColour(*wxBLACK);
	deleteButton->SetFont(deleteButton->GetFont().Scale(2.3f).Bold());
	elementSizer->Add(deleteButton, wxSizerFlags().Align(wxRIGHT));
	// everything


	this->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction) &ListElement::onClickPanel, NULL, this);
	this->SetSizer(elementSizer);
	elementSizer->SetSizeHints(this);
	m_List->getListSizer()->Add(this, wxSizerFlags().Border(wxALL, 3).Expand());
}

void ListElement::toggleStatus() {
	if (m_Status == Status::DONE)
		m_Status = Status::UNDONE;
	else
		m_Status = Status::DONE;
}

void ListElement::changeTitle(wxString title) {
	m_Title = title;
	m_TitleST->SetLabel(title);
	Update();
	Layout();
	m_List->getMainFrame()->getListManager()->saveToFile();
}

void ListElement::onToggleStatus(wxCommandEvent& evt) {
	this->toggleStatus();
	if (m_Status == Status::DONE)
		m_ToggleButton->SetLabel(UNICODE_CHECKBOX_CHECKED);
	else
		m_ToggleButton->SetLabel(UNICODE_CHECKBOX_UNCHECKED);

	m_List->getMainFrame()->getListManager()->saveToFile();
}

void ListElement::onClickPanel(wxCommandEvent& evt) {
	wxDialog* dialog = new wxDialog(this, wxID_ANY, "Edit Element");
	dialog->SetMinSize(wxSize(300, -1));
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	// Title staticText
	wxStaticText* titleST = new wxStaticText(dialog, wxID_ANY, "Title: ");
	dialogSizer->Add(titleST, wxSizerFlags(1));

	// Title textCtrl
	wxTextCtrl* titleTC = new wxTextCtrl(dialog, wxID_ANY, m_Title, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	titleTC->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent& evt) {
		changeTitle(titleTC->GetValue());
		dialog->Destroy();
		});
	dialogSizer->Add(titleTC, wxSizerFlags(1));

	// Button panel and sizer
	wxPanel* buttonPanel = new wxPanel(dialog);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	// Cancel button
	wxButton* btnCancel = new wxButton(buttonPanel, wxID_ANY, "Cancel");
	buttonSizer->Add(btnCancel, wxSizerFlags(1).Expand().Border(wxRIGHT, 2));

	// Change(commit) button
	wxButton* btnChange = new wxButton(buttonPanel, wxID_ANY, "Change");
	buttonSizer->Add(btnChange, wxSizerFlags(1).Expand().Border(wxLeft, 2));

	buttonPanel->SetSizer(buttonSizer);
	dialogSizer->Add(buttonPanel, wxSizerFlags(1).Expand());

	dialog->SetSizerAndFit(dialogSizer);
	dialog->CenterOnParent();
	dialog->ShowModal();
}

void ListElement::onDelete(wxCommandEvent& evt) {
	List* list = m_List;
	list->removeElement(this);
	this->Destroy();
	list->Layout();
	list->FitInside();
	list->getMainFrame()->getListManager()->saveToFile(); // saves the List after deletion
}