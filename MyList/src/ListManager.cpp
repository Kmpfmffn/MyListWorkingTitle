#include "ListManager.h"

#include <filesystem>
#include <fstream>

ListManager::ListManager(MainFrame* mainFrame, wxString savePath)
	: m_MainFrame(mainFrame),
	  m_Path(savePath)
{
	// Save file loading or creation
	if (std::filesystem::exists(savePath.ToStdString())) {
		m_MainFrame->SetStatusText("File exists. Loading from file...");

		std::ifstream file(savePath.ToStdString());
		std::string line;
		std::string title;
		Status status;
		try {
			while (std::getline(file, line)) {
				if (line.find("LIST(") != std::string::npos) {
					title = line.substr(5, line.length() - 6);
					m_Lists.push_back(new List(m_MainFrame, title));
				}
				else if (line.find("ELEM(") != std::string::npos) {
					title = line.substr(5, line.find(",") - 5);
					status = static_cast<Status>(std::stoi(line.substr(line.find(",") + 1, 1)));
					m_Lists[m_Lists.size()-1]->addElement(title, status);
				}
			}
			file.close();
		}
		catch (...) {
			// TODO: add logging
			// LOG("Error occured loading save from file. Line was: " + line);
		}
	}
	else {
		m_MainFrame->SetStatusText("File doesnt exist: " + savePath + ". Creating new file...");
		std::ofstream file(savePath.ToStdString());
	}
	// Save file loading or creation



	m_Lists.push_back(new List(m_MainFrame, "list0"));
	m_Lists.push_back(new List(m_MainFrame, "list1"));

	m_CurrentList = m_Lists[0];
	m_CurrentList->Show();
}

void ListManager::saveToFile() {

}