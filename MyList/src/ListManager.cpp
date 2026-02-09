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


	m_CurrentList = m_Lists[0];
	m_CurrentList->Show();
}

ListManager::~ListManager() {
	saveToFile();
}


/* Save file format
#VERSION(version)
LIST(title)
ELEM(title,status)
[...]
ELEM(title,status)
LIST(title)
[...]
*/
void ListManager::saveToFile() {
	std::ofstream file(m_Path.ToStdString());

	file << "#VERSION(0.0.1)" << std::endl;
	for (auto list : m_Lists) {
		file << "LIST(" << list->getTitle().c_str() << ")" << std::endl;
		for (auto element : list->getElements()) {
			file << "ELEM(" << element->getTitle() << "," << (element->getStatus() == Status::UNDONE ? "0" : "1") << ")" << std::endl;
		}
	}
	file.close();
}