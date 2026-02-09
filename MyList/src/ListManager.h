#pragma once

#include "List.h"
#include "MainFrame.h"

#include <string>
#include <vector>

class MainFrame;

class ListManager
{
public:
	ListManager(MainFrame* mainFrame, wxString savePath);
	~ListManager();

	List* getCurrentList() { return m_CurrentList; }

	void saveToFile();
private:
	MainFrame* m_MainFrame;

	List* m_CurrentList;

	wxString m_Path;
	std::vector<List*> m_Lists;
};

