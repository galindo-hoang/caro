#include "_Menu.h"

_Menu::_Menu() {
	Saved.clear();
	ifstream Read;
	Read.open("ListFile.txt");
	string Name = "", Date = "";
	File model;
	if (Read.is_open()) {
		while (!Read.eof()) {
			getline(Read, Name, '	');
			getline(Read, Date);
			if (Name == "" || Date == "") break;
			model.set(Name, Date);
			Saved.push_back(model);
		}
	}
	Read.close();
}


void _Menu::fixTXT() {
	ofstream write;
	write.open("ListFile.txt", ios::out);
	for (unsigned int i = 0; i < Saved.size(); ++i) {
		write << Saved[i].getName() << "	" << Saved[i].getDate() << endl;
	}
	write.close();
}

_Menu::~_Menu() {
	ofstream write;
	write.open("ListFile.txt", ios::out);
	for (unsigned int i = 0; i < Saved.size(); ++i) {
		write << Saved[i].getName() << "	" << Saved[i].getDate() << endl;
	}
	write.close();
	Saved.clear();
}

void _Menu::show_file(int start_x, int start_y, int current) {
	for (unsigned int i = 0; i < Saved.size(); ++i) {
		_Common::textcolor(11 + BackRound_menu * 16);
		_Common::gotoxy(start_x, start_y + i * 2);
		if (current == (start_y + i * 2)) {
			_Common::textcolor(4 + BackRound_menu * 16);
		}
		cout << "- " << Saved[i].getName() << "  " << Saved[i].getDate();
	}
	_Common::gotoxy(start_x, current);
}

void _Menu::add_to_list(string name, string time) {
	File model;
	model.set(name, time);
	for (unsigned int i = 0; i < Saved.size(); ++i) {
		if (Saved[i].getName() == name) {
			Saved[i] = model;
			return;
		}
	}
	Saved.push_back(model);
}

