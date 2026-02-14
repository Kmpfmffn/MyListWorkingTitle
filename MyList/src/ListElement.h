#pragma once

#include <wx/wx.h>

class MainFrame;
class ListManager;
class List;

enum Status {
	UNDONE = 0,
	DONE
};

class ListElement : public wxPanel
{
public:
	ListElement(List* list, wxString title, Status status = Status::UNDONE);

	wxString getTitle() { return m_Title; }
	Status getStatus() { return m_Status; }

	void toggleStatus();
	void changeTitle(wxString title);

	void onToggleStatus(wxCommandEvent& evt);
	void onClickPanel(wxCommandEvent& evt);
	void onDelete(wxCommandEvent& evt);
private:
	wxButton* m_ToggleButton;
	wxStaticText* m_TitleST;

	List* m_List;
	wxString m_Title;
	Status m_Status;
};