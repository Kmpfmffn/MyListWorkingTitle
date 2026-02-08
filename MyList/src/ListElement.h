#pragma once

#include <wx/wx.h>

class MainFrame;
class List;

enum Status {
	UNDONE = 0,
	DONE
};

class ListElement : public wxPanel
{
public:
	ListElement(List* list, wxString title, Status status = Status::UNDONE);

	void toggleStatus();
	void onToggleStatus(wxCommandEvent& evt);
private:
	wxButton* m_ToggleButton;

	List* m_List;
	wxString m_Title;
	Status m_Status;
};