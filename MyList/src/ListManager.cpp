#include "ListManager.h"

ListManager::ListManager(MainFrame* mainFrame)
	: m_MainFrame(mainFrame)
{
	m_Lists.push_back(new List(m_MainFrame, "list0"));
	m_Lists.push_back(new List(m_MainFrame, "list1"));

	m_CurrentList = m_Lists[0];
	m_CurrentList->Show();
}


int ListManager::LoadFromFile(std::string path) {
	m_Path = path;

	return 1;
}
