#include "Window.h"
wxBEGIN_EVENT_TABLE(Window, wxFrame)
  EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

Window::Window() : wxFrame(nullptr, 10001, "SWE!!!!!!", wxPoint(200, 200), wxSize(500, 500)) {
	btn = new wxButton * [nFieldWidth * nfieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nfieldHeight, 0, 0);

	nfield = new int[nFieldWidth * nfieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nfieldHeight; y++) {
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Window::OnButtonClicked, this);
			nfield[y * nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
	
}

Window:: ~Window() {
	delete[]btn;
}
void Window::OnButtonClicked(wxCommandEvent& evt) {

	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int mines = 30;
		while(mines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nfieldHeight;

			if (nfield[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				nfield[ry * nFieldWidth + rx] = -1;
				mines--;
			}


		}
		bFirstClick = false;
	}
	btn[y * nFieldWidth + x]->Enable(false);

	if (nfield[y * nFieldWidth + x] == -1) {
		wxMessageBox("BOOOOOOM!! - GAME OVER : (");
			bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++) {
			for (int y = 0; y < nfieldHeight; y++) {
				nfield[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}

		}
	}
	else {
		int mine_count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < nFieldWidth && y + j < nfieldHeight) {
					if (nfield[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}
		}

		if (mine_count > 0) {
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}
	
	
	evt.Skip();

}