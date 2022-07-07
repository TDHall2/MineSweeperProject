#include "cApp.h"
#include "Window.h"
wxIMPLEMENT_APP(cApp);

bool cApp::OnInit() {
	window = new Window();
	window->Show();
	return true;
}
