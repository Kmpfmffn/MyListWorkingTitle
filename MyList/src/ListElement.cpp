#include "ListElement.h"
#include "Constants.h"

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
	wxButton* checkboxButton = new wxButton(this, wxID_ANY, m_Title, wxPoint(-1, -1), wxSize(elemHeight, elemHeight));
	checkboxButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) { m_List->addElement("new Element"); });
	elementSizer->Add(checkboxButton, wxSizerFlags().Border(wxALL, 2));

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