#include "App.h"
#include "ListManager.h"

//#include "../resource.h"

#ifdef __WXMSW__
	#include <windows.h>
	#include <wx/msw/private.h> // for wxGetInstance()
#endif


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	m_MainFrame = new MainFrame();
	//mainFrame->SetIcon(wxICON(appicon));

	//// Set Icons to the window and task bar
	//#ifdef __WXMSW__
	//	wxIconBundle icons;
	//	HICON hIcon = (HICON)::LoadImage(wxGetInstance(), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	//	if (hIcon) {
	//		wxIcon icon;
	//		icon.CreateFromHICON(hIcon); // convert native HICON to wxIcon
	//		icons.AddIcon(icon);         // add to bundle
	//		mainFrame->SetIcons(icons);  // set both small/large icons
	//	}
	//#endif // __WXMSW__



	m_MainFrame->Center();
	m_MainFrame->Show(true);
	return true;
}


App::App() {
}
App::~App() {
}