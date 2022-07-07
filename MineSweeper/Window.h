#pragma once
#include "wx/wx.h"
class Window : public wxFrame
{
private:
	int nFieldWidth = 10;
	int nfieldHeight = 10;
	wxButton** btn;
	int* nfield = nullptr;
	bool bFirstClick = true;


public:
	Window();
	~Window();
	void OnButtonClicked(wxCommandEvent& evt);

	
	wxDECLARE_EVENT_TABLE();
};

