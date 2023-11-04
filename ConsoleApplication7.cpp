#include <iostream>
#include <vector>

using namespace std;

//p - position; chf - chess figure; kn - knight; pm - possible move; col - color; nl - number-letter
struct pos {
	int x;
	int y;
	const char* nl[8] {"a","b","c","d","e","f","g","h" };
};
class chf {
public:
	/*chf(int x, int y, bool c) {
		p.x = x;
		p.y = y;
		col = c;
	}*/
	bool col;
	pos p;
	vector<pos> pm;
	void cpm() {
		for (int i = 0; i < pm.size(); i++) {
			cout << p.nl[pm.at(i).x-1] << pm.at(i).y << ";" << endl;
		}
	};
};
class pawn {
public:
	chf f;
	pawn(int x, int y, bool c) {
		f.p.x = x;
		f.p.y = y;
		f.col = c;
	}
	void fpm() {
		pos a;
		a.x = f.p.x;
		if(f.col){
			a.y = f.p.y + 1;
			if (a.y < 9) f.pm.push_back(a);
			if (f.p.y == 2) {
			a.x = f.p.y + 2;
			f.pm.push_back(a);
			}
		} else {
			a.y = f.p.y - 1;
			if (a.y > 0) f.pm.push_back(a);
			if (f.p.y == 7) {
				a.x = f.p.y - 2;
				f.pm.push_back(a);
			}
		}
		
	}
};
class knight {
public:
	chf f;
	knight(int x, int y) {
		f.p.x = x;
		f.p.y = y;
	}
	void fpm() {
		pos a;
		for (int i = -1; i < 2; i+=2) {
			for (int j = -1; j < 2; j+=2) {
				a.x = f.p.x + 1 * i;
				a.y = f.p.y + 2 * j;
				if (a.x > 0 || a.x < 9 || a.y > 0 || a.y < 9) f.pm.push_back(a);
				a.x = f.p.x + 2 * i;
				a.y = f.p.y + 1 * j;
				if (a.x > 0 || a.x < 9 || a.y > 0 || a.y < 9) f.pm.push_back(a);
			}
		}
	};
};
class bishop {
public:
	chf f;
	bishop(int x, int y) {
		f.p.x = x;
		f.p.y = y;
	}
	void fpm() {
		pos a;
		for (int i = 1; i < 9; i++) {
			a.x = f.p.x + i;
			a.y = f.p.y + i;
			if (a.x < 9 && a.y < 9) f.pm.push_back(a);
			a.x = f.p.x - i;
			a.y = f.p.y - i;
			if (a.x > 0 && a.y > 0) f.pm.push_back(a);
			a.x = f.p.x + i;
			a.y = f.p.y - i;
			if (a.x < 9 && a.y < 9) f.pm.push_back(a);
			a.x = f.p.x - i;
			a.y = f.p.y + i;
			if (a.x > 0 && a.y > 0) f.pm.push_back(a);
		}
	}
};
class rook {
public:
	chf f;
	rook(int x, int y) {
		f.p.x = x;
		f.p.y = y;
	}
	void fpm() {
		pos a;
		for (int i = 1; i < 9; i++) {
			a.x = 0 + i;
			a.y = f.p.y;
			if (a.x != f.p.x) f.pm.push_back(a);
			a.y = 0 + i;
			a.x = f.p.x;
			if (a.y != f.p.y) f.pm.push_back(a);
		}
	}
};
int main() {
	int x1, y1;
	cin >> x1 >> y1;
	pawn pn(x1, y1, true);
	pn.fpm();
	cout << "pawn:" << endl;
	pn.f.cpm();
	knight kn(x1,y1);
	kn.fpm();
	cout << "knight:" << endl;
	kn.f.cpm();
	bishop bsh(x1, y1);
	bsh.fpm();
	cout << "bishop:" << endl;
	bsh.f.cpm();
	rook rk(x1, y1);
	rk.fpm();
	cout << "rook:" << endl;
	rk.f.cpm();
}