#pragma once

#include <wx/wx.h>
#include <wx/popupwin.h>

class ListManager;

// The mainFrame containing the entire content of the window
class MainFrame : public wxFrame
{
public:
	MainFrame();

	void onKeyPress(wxKeyEvent& evt);
	void onMenuNewElement();

	wxPanel* getMainPanel() { return m_MainPanel; }
	wxBoxSizer* getMainSizer() { return m_MainSizer; }
private:
	wxPanel* m_MainPanel;
	wxBoxSizer* m_MainSizer;

	ListManager* m_ListManager;
};

