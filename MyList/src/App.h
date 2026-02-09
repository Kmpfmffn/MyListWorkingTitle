#pragma once
#include <wx/wx.h>

#include "MainFrame.h"

class ListManager;

class App : public wxApp
{
public:
	bool OnInit() override;

	App();
	~App();
private:
	MainFrame* m_MainFrame;
};