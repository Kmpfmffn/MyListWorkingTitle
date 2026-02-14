#pragma once

#include <wx/wx.h>

#include "ListElement.h"

class MainFrame;
class ListManager;

class List : public wxPanel
{
public:
	List(MainFrame* mainFrame, wxString title);

	MainFrame* getMainFrame() { return m_MainFrame; }
	wxScrolledWindow* getListPanel() { return m_ListPanel; }
	wxBoxSizer* getListSizer() { return m_ListSizer; }
	wxString getTitle() { return m_Title; }
	std::vector<ListElement*> getElements() { return m_Elements; }

	void onClickListTitle(wxCommandEvent& evt);

	void changeTitle(wxString title);

	bool addElement(wxString title, Status status = Status::UNDONE);
	bool removeElement(ListElement* element);
private:
	MainFrame* m_MainFrame;
	wxScrolledWindow* m_ListPanel;
	wxBoxSizer* m_ListSizer;
	wxStaticText* m_TitleLabel;

	wxString m_Title;
	std::vector<ListElement*> m_Elements;
};