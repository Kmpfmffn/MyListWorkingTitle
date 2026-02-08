#include "ListElement.h"
#include "Constants.h"

#include "MainFrame.h"
#include "List.h"


int elemWidth = 300;
int elemHeight = 50;
wxSize elemSize(elemWidth, elemHeight);

ListElement::ListElement(List* list, wxString title, Status status)
	: wxPanel(list, wxID_ANY),
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

	wxStaticText* titleST = new wxStaticText(this, wxID_ANY, m_Title);
	titleST->SetForegroundColour(mfnSECONDARY_TEXT_COLOUR);
	titleST->SetFont(titleST->GetFont().Scale(2));
	elementSizer->Add(titleST, wxSizerFlags(1).CenterVertical().Border(wxLEFT, 5));

	wxButton* deleteButton = new wxButton(this, wxID_ANY, "X", wxDefaultPosition, wxSize(elemHeight, elemHeight));
	deleteButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) { List* list = m_List; this->Destroy(); list->Layout(); list->FitInside(); });
	deleteButton->SetBackgroundColour(*wxRED);
	deleteButton->SetForegroundColour(*wxBLACK);
	deleteButton->SetFont(deleteButton->GetFont().Scale(2.3f).Bold());
	elementSizer->Add(deleteButton, wxSizerFlags());
	// everything


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

void ListElement::onToggleStatus(wxCommandEvent& evt) {
	this->toggleStatus();
	if (m_Status == Status::DONE)
		m_ToggleButton->SetLabel(UNICODE_CHECKBOX_CHECKED);
	else
		m_ToggleButton->SetLabel(UNICODE_CHECKBOX_UNCHECKED);
}