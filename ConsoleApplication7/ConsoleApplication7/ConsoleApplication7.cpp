#include <iostream>
#include <vector>

using namespace std;

//p - position; chf - chess figure; kn - knight; pm - possible move; col - color; nl - number-letter
struct pos {
	int x;
	int y;
	const char* nl[8] {"a","b","c","d","e","f","g","h" };
};
struct chBoard{	
	vector <chf> chBoard;
	void record(chf f){
		chBoard.push_back(f);
	}
};
class chf {
public:
	chf(int x, int y, bool c) {
		p.x = x;
		p.y = y;
		col = c;
	}
	bool col;
	pos p;
	chBoard board;
	vector<pos> pm;
	void cpm() {
		for (int i = 0; i < pm.size(); i++) {
			cout << p.nl[pm.at(i).x-1] << pm.at(i).y << ";" << endl;
		}
	};
};
class Pawn : public chf {
public:
	Pawn(int x, int y, bool c) :chf(x, y, c) {};
	void fpm() {
		pos a;
		a.x = p.x;
		if (col) {
			a.y = p.y + 1;
			if (a.y < 9) pm.push_back(a);
			if (p.y == 2) {
				a.x = p.y + 2;
				pm.push_back(a);
			}
		}
		else {
			a.y = p.y - 1;
			if (a.y > 0) pm.push_back(a);
			if (p.y == 7) {
				a.x = p.y - 2;
				pm.push_back(a);
			}
		}
		for (int j = 0; j < board.chBoard.size(); j++) {
			for (int i = 0; i < pm.size(); i++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y) {
					pm.erase(pm.begin() + i);
				}
				for (int k = -1; k < 2; k += 2) {
					if (col) {
						if (pm.at(i).x + k == board.chBoard.at(j).p.x && col != board.chBoard.at(i).col && pm.at(i).y + 1 == board.chBoard.at(j).p.y) {
							a.x = p.x + k;
							a.y = p.y + 1;
							pm.push_back(a);
						}
						else {
							if (pm.at(i).x + k == board.chBoard.at(j).p.x && col != board.chBoard.at(i).col && pm.at(i).y - 1 == board.chBoard.at(j).p.y) {
								a.x = p.x + k;
								a.y = p.y - 1;
								pm.push_back(a);
							}
						}
					}
				}
			}
		}
	};
};
class Knight:public chf {
public:
	Knight(int x, int y, bool c) : chf(x, y, c) {};
	void fpm() {
		pos a;
		for (int i = -1; i < 2; i+=2) {
			for (int j = -1; j < 2; j+=2) {
				a.x = p.x + 1 * i;
				a.y = p.y + 2 * j;
				if (a.x > 0 && a.x < 9 && a.y > 0 && a.y < 9) pm.push_back(a);
				a.x = p.x + 2 * i;
				a.y = p.y + 1 * j;
				if (a.x > 0 && a.x < 9 && a.y > 0 && a.y < 9) pm.push_back(a);
			}
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < board.chBoard.size(); j++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y && col == board.chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
				}
			}
		}
	};
};
class Bishop : public chf {
public:
	Bishop(int x, int y, bool c) :chf(x, y, c) {};
	void fpm() {
		pos a;
		for (int i = 1; i < 9; i++) {
			a.x = p.x + i;
			a.y = p.y + i;
			if (a.x < 9 && a.y < 9) pm.push_back(a);
			a.x = p.x - i;
			a.y = p.y - i;
			if (a.x > 0 && a.y > 0) pm.push_back(a);
			a.x = p.x + i;
			a.y = p.y - i;
			if (a.x < 9 && a.y > 0) pm.push_back(a);
			a.x = p.x - i;
			a.y = p.y + i;
			if (a.x > 0 && a.y < 9) pm.push_back(a);
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < board.chBoard.size(); j++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y && col == board.chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
					if (pm.at(i).x < board.chBoard.at(j).p.x && pm.at(i).y < board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x && pm.at(ii).y > board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}else if (pm.at(i).x < board.chBoard.at(j).p.x && pm.at(i).y > board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x && pm.at(ii).y < board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}else if (pm.at(i).x > board.chBoard.at(j).p.x && pm.at(i).y > board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x && pm.at(ii).y < board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}else if (pm.at(i).x > board.chBoard.at(j).p.x && pm.at(i).y < board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x && pm.at(ii).y > board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
				}
			}
		}
	}
};
class Rook : public chf {
public:
	Rook(int x, int y, bool c) :chf(x, y, c) {};
	void fpm() {
		pos a;
		for (int i = 1; i < 9; i++) {
			a.x = 0 + i;
			a.y = p.y;
			if (a.x != p.x) pm.push_back(a);
			a.y = 0 + i;
			a.x = p.x;
			if (a.y != p.y) pm.push_back(a);
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < board.chBoard.size(); j++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y && col == board.chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
					if (pm.at(i).x < board.chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y > board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y < board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > board.chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y < board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y > board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
				}
			}
		}
	}
};
class Queen : public chf {
	Queen(int x, int y, bool c) : chf(x, y, c) {};
	void fpm() {
		pos a;
		for (int i = 1; i < 9; i++) {
			a.x = 0 + i;
			a.y = p.y;
			if (a.x != p.x) pm.push_back(a);
			a.y = 0 + i;
			a.x = p.x;
			if (a.y != p.y) pm.push_back(a);
		}
		for (int i = 1; i < 9; i++) {
			a.x = p.x + i;
			a.y = p.y + i;
			if (a.x < 9 && a.y < 9) pm.push_back(a);
			a.x = p.x - i;
			a.y = p.y - i;
			if (a.x > 0 && a.y > 0) pm.push_back(a);
			a.x = p.x + i;
			a.y = p.y - i;
			if (a.x < 9 && a.y > 0) pm.push_back(a);
			a.x = p.x - i;
			a.y = p.y + i;
			if (a.x > 0 && a.y < 9) pm.push_back(a);
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < board.chBoard.size(); j++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y && col == board.chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
					if (pm.at(i).x < board.chBoard.at(j).p.x && pm.at(i).y < board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x && pm.at(ii).y > board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x < board.chBoard.at(j).p.x && pm.at(i).y > board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x && pm.at(ii).y < board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > board.chBoard.at(j).p.x && pm.at(i).y > board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x && pm.at(ii).y < board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > board.chBoard.at(j).p.x && pm.at(i).y < board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x && pm.at(ii).y > board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x < board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y > board.chBoard.at(j).p.y && pm.at(i).x == board.chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y < board.chBoard.at(j).p.y && pm.at(i).x == board.chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y < board.chBoard.at(j).p.y && pm.at(i).x == board.chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y > board.chBoard.at(j).p.y && pm.at(i).x == board.chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
				}
			}
		}
	}
};
class King : public chf {
	King(int x, int y, bool c) : chf(x, y, c) {};
	void fpm() {
		pos a;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				a.x = p.x + i;
				a.y = p.y + j;
				if ( a.x != 0 && a.y != 0 ) pm.push_back(a);
			}
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < board.chBoard.size(); j++) {
				if (pm.at(i).x == board.chBoard.at(j).p.x && pm.at(i).y == board.chBoard.at(j).p.y && col == board.chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
				}
			}
		}
	}
};
int main() {

	Pawn pawn(4, 2, true);
	pawn.board.record(pawn);
	pawn.fpm();
	cout << "pawn:" << endl;
	pawn.cpm();
	Knight knight(2, 1,true);
	knight.fpm();
	cout << "knight:" << endl;
	knight.cpm();
	Bishop bishop(3, 1,true);
	bishop.fpm();
	cout << "bishop:" << endl;
	bishop.cpm();
	Rook rook(1, 1,true);
	rook.fpm();
	cout << "rook:" << endl;
	rook.cpm();
}