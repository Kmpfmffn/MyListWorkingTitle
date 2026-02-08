#pragma once

#include <wx/wx.h>

#include "ListElement.h"

class MainFrame;

class List : public wxScrolledWindow
{
public:
	List(MainFrame* mainFrame, wxString title);

	MainFrame* getMainFrame() { return m_MainFrame; }
	wxBoxSizer* getListSizer() { return m_ListSizer; }

	bool addElement(wxString title, Status status = Status::UNDONE);
private:
	MainFrame* m_MainFrame;
	wxBoxSizer* m_ListSizer;
	wxStaticText* m_TitleLabel;

	wxString m_Title;
	std::vector<ListElement*> m_Elements;
};