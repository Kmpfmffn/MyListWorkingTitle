#include "List.h"
#include "ListManager.h"
#include "MainFrame.h"

#include "Constants.h"

List::List(MainFrame* mainFrame, wxString title)
	: wxPanel(mainFrame->getMainPanel(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 2621440L, "ListMainPanel"),
	  m_MainFrame(mainFrame),
	  m_Title(title)
{
	this->SetBackgroundColour(mfnSECONDARY_BACKGROUND_COLOUR);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	m_TitleLabel = new wxStaticText(this, wxID_ANY, m_Title, wxDefaultPosition, wxSize(50, -1));
	m_TitleLabel->SetForegroundColour(mfnPRIMARY_TEXT_COLOUR);
	m_TitleLabel->SetBackgroundColour(mfnPRIMARY_BACKGROUND_COLOUR);
	m_TitleLabel->SetFont(m_TitleLabel->GetFont().Scale(2));
	mainSizer->Add(m_TitleLabel, wxSizerFlags().Expand().Border(wxALL, 2));

	m_ListPanel = new wxScrolledWindow(this, wxID_ANY);
	m_ListPanel->SetName("ScrolledPanel");
	m_ListSizer = new wxBoxSizer(wxVERTICAL);
	m_ListPanel->SetScrollRate(0, 9);
	m_ListPanel->SetSizer(m_ListSizer);
	m_ListSizer->FitInside(m_ListPanel);
	mainSizer->Add(m_ListPanel, wxSizerFlags(1).Expand().Border(wxALL, 2));

	this->SetSizer(mainSizer);
	m_MainFrame->getMainSizer()->Add(this, wxSizerFlags(1).Expand().Border(wxALL, 5));
	this->Hide();
}


bool List::addElement(wxString title, Status status) {
	m_Elements.push_back(new ListElement(this, title, status));
	m_ListPanel->Layout();
	m_ListPanel->FitInside();
	return 1;
}

bool List::removeElement(ListElement* element) {
	m_Elements.erase(std::find(m_Elements.begin(), m_Elements.end(), element));
	return true;
}