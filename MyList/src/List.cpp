#include "List.h"
#include "MainFrame.h"

#include "Constants.h"

List::List(MainFrame* mainFrame, wxString title)
	: wxScrolledWindow(mainFrame->getMainPanel(), wxID_ANY),
	  m_MainFrame(mainFrame),
	  m_Title(title)
{
	// TODO: Separate m_TitleLabel from ScrolledWindow
	this->SetBackgroundColour(mfnSECONDARY_BACKGROUND_COLOUR);
	m_ListSizer = new wxBoxSizer(wxVERTICAL);
	m_TitleLabel = new wxStaticText(this, wxID_ANY, m_Title, wxDefaultPosition, wxSize(50, -1));
	m_TitleLabel->SetForegroundColour(mfnPRIMARY_TEXT_COLOUR);
	m_TitleLabel->SetBackgroundColour(mfnPRIMARY_BACKGROUND_COLOUR);
	m_TitleLabel->SetFont(m_TitleLabel->GetFont().Scale(2));
	m_ListSizer->Add(m_TitleLabel, wxSizerFlags().Expand().Border(wxALL, 2));


	// temporary for development (needs to be read from save later)
	/*for (int i = 0; i < 11; i++) {
		m_Elements.push_back(new ListElement(this, wxString::Format("Item %d", i)));
	}*/
	// temporary


	this->SetSizer(m_ListSizer);
	SetScrollRate(0, 9);
	m_ListSizer->FitInside(this);
	m_MainFrame->getMainSizer()->Add(this, wxSizerFlags(1).Expand().Border(wxALL, 5));
	this->Hide();
}


bool List::addElement(wxString title, Status status) {
	m_Elements.push_back(new ListElement(this, title, status));
	Layout();
	FitInside();
	return 1;
}