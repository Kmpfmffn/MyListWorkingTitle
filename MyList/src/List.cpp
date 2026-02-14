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
	m_TitleLabel->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction) &List::onClickListTitle, NULL, this);
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

void List::onClickListTitle(wxCommandEvent& evt) {
	wxDialog* dialog = new wxDialog(this, wxID_ANY, "Edit List Title");
	dialog->SetMinSize(wxSize(300, -1));
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	// Title staticText
	wxStaticText* titleST = new wxStaticText(dialog, wxID_ANY, "Title: ");
	dialogSizer->Add(titleST, wxSizerFlags(1).Expand());

	// Title textCtrl
	wxTextCtrl* titleTC = new wxTextCtrl(dialog, wxID_ANY, m_Title, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	titleTC->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent& evt) {
		changeTitle(titleTC->GetValue());
		dialog->Destroy();
		});
	dialogSizer->Add(titleTC, wxSizerFlags(1).Expand());

	// Button panel and sizer
	wxPanel* buttonPanel = new wxPanel(dialog);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	// Cancel button
	wxButton* btnCancel = new wxButton(buttonPanel, wxID_ANY, "Cancel");
	buttonSizer->Add(btnCancel, wxSizerFlags(1).Expand());

	// Change(commit) button
	wxButton* btnChange = new wxButton(buttonPanel, wxID_ANY, "Change");
	buttonSizer->Add(btnChange, wxSizerFlags(1).Expand());

	buttonPanel->SetSizer(buttonSizer);
	dialogSizer->Add(buttonPanel, wxSizerFlags(1).Expand().Border(wxALL, 5));

	dialog->SetSizerAndFit(dialogSizer);
	dialog->CenterOnParent();
	dialog->ShowModal();
}

void List::changeTitle(wxString title) {
	m_Title = title;
	m_TitleLabel->SetLabel(title);
	Update();
	Layout();
	m_MainFrame->getListManager()->saveToFile();
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