#include <vector>﻿
#include <iostream>

using namespace std;

//p - position; chf - chess figure; kn - knight; pm - possible move; col - color; nl - number-letter
struct pos {
	int x;
	int y;
	char nl[8]{ 'a','b','c','d','e','f','g','h' };
};
class chf {
public:
	chf(int x, int y, bool c) {
		p.x = x;
		p.y = y;
		col = c;
	}
	vector <chf> chBoard;
	void record(chf f) {
		chBoard.push_back(f);
	}
	bool col;
	char tf[6]{ ' ', 'N', 'B', 'R', 'Q', 'K' };
	int tfi=0;
	//chfsBoard board;
	pos p;
	vector<pos> pm;
	void cpm() {
		for (int i = 0; i < pm.size(); i++) {
			cout <<tf[tfi]<< p.nl[p.x-1]<<p.y<<"-" << p.nl[pm.at(i).x - 1] << pm.at(i).y << ";" << endl;
		}
	};
};

class Pawn : public chf {
public:
	Pawn(int x, int y, bool c) :chf(x, y, c) { tfi = 0; };
	void fpm() {
		pos a;
		a.x = p.x;
		if (col) {
			a.y = p.y + 1;
			if (a.y < 9) pm.push_back(a);
			if (p.y == 2) {
				a.y = p.y + 2;
				pm.push_back(a);
			}
		}
		else {
			a.y = p.y - 1;
			if (a.y > 0) pm.push_back(a);
			if (p.y == 7) {
				a.y = p.y - 2;
				pm.push_back(a);
			}
		}
		for (int j = 0; j < chBoard.size(); j++) {
			for (int i = 0; i < pm.size(); i++) {
				if (pm.at(i).x ==chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
					pm.erase(pm.begin() + i);
				}
				for (int k = -1; k < 2; k += 2) {
					if (col) {
						if (pm.at(i).x + k == chBoard.at(j).p.x && col != chBoard.at(i).col && pm.at(i).y + 1 == chBoard.at(j).p.y) {
							a.x = p.x + k;
							a.y = p.y + 1;
							pm.push_back(a);
						}
					} else {
						if (pm.at(i).x + k == chBoard.at(j).p.x && col != chBoard.at(i).col && pm.at(i).y - 1 == chBoard.at(j).p.y) {
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
class Knight :public chf {
public:
	Knight(int x, int y, bool c) : chf(x, y, c) { tfi = 1; };
	void fpm() {
		pos a;
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				a.x = p.x + 1 * i;
				a.y = p.y + 2 * j;
				if (a.x > 0 && a.x < 9 && a.y > 0 && a.y < 9) pm.push_back(a);
				a.x = p.x + 2 * i;
				a.y = p.y + 1 * j;
				if (a.x > 0 && a.x < 9 && a.y > 0 && a.y < 9) pm.push_back(a);
			}
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < chBoard.size(); j++) {
				if (pm.at(i).x == chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y && col == chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
				}
			}
		}
	};
};
class Bishop : public chf {
public:
	Bishop(int x, int y, bool c) :chf(x, y, c) { tfi = 3; };
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
			for (int j = 0; j < chBoard.size(); j++) {
				if (pm.at(i).x == chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
					if(col == chBoard.at(i).col)pm.erase(pm.begin() + i);
					if (pm.at(i).x < chBoard.at(j).p.x && pm.at(i).y < chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x && pm.at(ii).y > chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x < chBoard.at(j).p.x && pm.at(i).y > chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x && pm.at(ii).y < chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x && pm.at(i).y > chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x && pm.at(ii).y < chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x && pm.at(i).y < chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x && pm.at(ii).y > chBoard.at(j).p.y) {
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
	Rook(int x, int y, bool c) :chf(x, y, c) { tfi = 4; };
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
			for (int j = 0; j < chBoard.size(); j++) {
				if (pm.at(i).x == chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
					if (col == chBoard.at(i).col)pm.erase(pm.begin() + i);
					if (pm.at(i).x < chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y > chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y < chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y < chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y > chBoard.at(j).p.y) {
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
	Queen(int x, int y, bool c) : chf(x, y, c) { tfi = 5; };
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
			for (int j = 0; j < chBoard.size(); j++) {
				if (pm.at(i).x == chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
					if (col == chBoard.at(i).col)pm.erase(pm.begin() + i);
					if (pm.at(i).x < chBoard.at(j).p.x && pm.at(i).y < chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x && pm.at(ii).y > chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x < chBoard.at(j).p.x && pm.at(i).y > chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x && pm.at(ii).y < chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x && pm.at(i).y > chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x && pm.at(ii).y < chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x && pm.at(i).y < chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x && pm.at(ii).y > chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x < chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x > chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y > chBoard.at(j).p.y && pm.at(i).x == chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y < chBoard.at(j).p.y && pm.at(i).x == chBoard.at(j).p.x) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).x > chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).x < chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y) {
								pm.erase(pm.begin() + i);
							}
						}
					}
					else if (pm.at(i).y < chBoard.at(j).p.y && pm.at(i).x == chBoard.at(j).p.x) {
						for (int ii = 0; ii < pm.size(); ii++) {
							if (pm.at(ii).y > chBoard.at(j).p.y && pm.at(i).x == chBoard.at(j).p.x) {
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
	King(int x, int y, bool c) : chf(x, y, c) { tfi = 6; };
	void fpm() {
		pos a;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				a.x = p.x + i;
				a.y = p.y + j;
				if (!(i == 0 && j == 0)) pm.push_back(a);
			}
		}
		for (int i = 0; i < pm.size(); i++) {
			for (int j = 0; j < chBoard.size(); j++) {
				if (pm.at(i).x == chBoard.at(j).p.x && pm.at(i).y == chBoard.at(j).p.y && col == chBoard.at(i).col) {
					pm.erase(pm.begin() + i);
				}
			}
		}
	}
};
int main() {
	Pawn pawn(4, 2, true);
	pawn.record(pawn);
	pawn.fpm();
	pawn.cpm();
	Knight knight(2, 1, true);
	knight.record(knight);
	knight.fpm();
	knight.cpm();
	Bishop bishop(3, 1, true);
	bishop.record(bishop);
	bishop.fpm();
	bishop.cpm();
	Rook rook(1, 1, true);
	rook.record(rook);
	rook.fpm();
	rook.cpm();

}