#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;

char pole[24][19];// plansza do poruszania siê
int bohX;
int bohXpast;
int bohY;
int bohYpast;
char boh = 219;//do ³atwiejszego dostêpu do znaków ASCII
char drzewa = 177;
int gora = 119;//w
int dol = 115;//s
int lewo = 97;//a
int prawo = 100;//d
int klawisz;//zmienna u¿ywana wszêdzie tak w³aœciwie do pobierania naciskanego klawisza
int szerokosc = 24;//wymiary planszy
int wysokosc = 19;
bool wioska = 1;// boole do decydowania któr¹ z map wyœwietlaæ
bool las = 0;
bool loch = 0;
bool pus = 0;
char a = 176;
char e = 177;
char c = 178;
char poz = 205;
char pion = 186;
char lg = 201;
char ld = 200;
char pg = 187;
char pd = 188;

class Ekwipunek {// do zapisywania iloœci danych przedmiotów w ekwipunku
public:
	int i1;
	int i2;
	int i3;
	int i4;
	int i5;
	int i6;
};

class Hero {
public:
	int gold;
	int exp;
	int hp;
	int hpMax;
	int sila;
	int szybk;
	int zrecz;
	int magia;
	int pumie;
	int stamina;
	int staminaMax;
	Ekwipunek items = { 0,0,0,0,0,0 };
};

Hero hero = { 0,0,20,20,3,3,3,3,0,5,5 };

class Stwor {
public:
	int hp;
	int poziom;
	int slabosc;
};

Stwor ghost;
Stwor bear;

void idzdoxy(int x, int y)//usprawnia poruszanie siê po planszy
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

void dom() {// zaznacza na których polach znajduje siê dom
	for (int i = 3; i < 7; i++) {
		for (int j = 3; j < 6; j++) {
			pole[j][i] = 'd';
		}
	}
	pole[4][2] = 'd';
	pole[2][4] = 'd';
	pole[6][4] = 'd';
}
void interactDom() {// odpoczywanie w domku
	hero.hp = hero.hpMax;
	hero.stamina = hero.staminaMax;
}

void sklep() {
	for (int i = 4; i < 8; i++) {
		for (int j = 17; j < 22; j++) {
			pole[j][i] = 's';
		}
	}
	pole[19][2] = 's';
	pole[18][3] = 's';
	pole[19][3] = 's';
	pole[20][3] = 's';

}
void interactSklep() {// zakupy
	cout << "1- jablko(+3 hp)- 3 gold" << endl << "2- sok(+1 stamina)- 3 gold" << endl <<
		"3- hp potion(+10 hp)- 10 gold" << endl << "4- stamina potion(+5 stamina)- 15 gold" << endl
		<< "5- max hp potion(+5 maxhp)- 20 gold" << endl << "6- max stamina potion(+1 maxstamina)- 12 gold" << endl
		<< "q- wyjdz ze sklepu" << endl;
	for (;;)
	{
		klawisz = _getch();
		if (klawisz == '1') {
			if (hero.gold >= 3) {
				hero.items.i1++;
				hero.gold -= 3;
			}
		}
		if (klawisz == '2') {
			if (hero.gold >= 3) {
				hero.items.i2++;
				hero.gold -= 3;
			}
		}
		if (klawisz == '3') {
			if (hero.gold >= 10) {
				hero.items.i3++;
				hero.gold -= 10;
			}
		}
		if (klawisz == '4') {
			if (hero.gold >= 15) {
				hero.items.i4++;
				hero.gold -= 15;
			}
		}
		if (klawisz == '5') {
			if (hero.gold >= 20) {
				hero.items.i5++;
				hero.gold -= 20;
			}
		}
		if (klawisz == '6') {
			if (hero.gold >= 12) {
				hero.items.i6++;
				hero.gold -= 12;
			}
		}
		if (klawisz == 'q') {
			system("cls");
			break;
		}
	}
}

void wieza() {
	for (int i = 13; i < 17; i++) {
		for (int j = 3; j < 6; j++) {
			pole[j][i] = 'w';
		}
	}
	pole[2][12] = 'w';
	pole[4][12] = 'w';
	pole[6][12] = 'w';
	pole[2][13] = 'w';
	pole[6][13] = 'w';
}
void interactWieza() {//nauka
	cout << "1- sila" << endl << "2- szybkosc" << endl << "3- zrecznosc" << endl << "4- magia" << endl << "q- wyjdz z wiezy" << endl;
	for (;;) {
		klawisz = _getch();
		if (klawisz == '1') {
			if (hero.pumie >= 1) {
				hero.sila++;
				hero.pumie--;
			}
		}
		if (klawisz == '2') {
			if (hero.pumie >= 1) {
				hero.szybk++;
				hero.pumie--;
			}
		}
		if (klawisz == '3') {
			if (hero.pumie >= 1) {
				hero.zrecz++;
				hero.pumie--;
			}
		}
		if (klawisz == '4') {
			if (hero.pumie >= 1) {
				hero.magia++;
				hero.pumie--;
			}
		}
		if (klawisz == 'q') {
			system("cls");
			break;
		}
	}
}

void teleport() {//zaznacza gdzie znajduje siê teleport w wiosce
	for (int i = 13; i < 16; i++) {
		for (int j = 17; j < 21; j++) {
			pole[j][i] = 't';
		}
	}
	pole[18][12] = 't';
	pole[19][12] = 't';
	pole[18][16] = 't';
	pole[19][16] = 't';
}
void teleport2() {//zaznacza gdzie znajduj¹ siê portale w lesie
	for (int i = 15; i < 18; i++) {
		for (int j = 0; j < 4; j++) {
			pole[j][i] = 't';
		}
	}
	pole[1][14] = 't';
	pole[2][14] = 't';
	pole[1][18] = 't';
	pole[2][18] = 't';
	for (int i = 15; i < 18; i++) {
		for (int j = 20; j < 24; j++) {
			pole[j][i] = 't';
		}
	}
	pole[21][14] = 't';
	pole[22][14] = 't';
	pole[21][18] = 't';
	pole[22][18] = 't';
}

void interactX() {//losuje rzeczy ze skrzyni
	srand(time(NULL));
	int zloto = rand() % 15 + 3;
	hero.gold += zloto;
	cout << "Znaleziono " << zloto << " sztuk zlota" << endl;
	int prise = rand() % 5;
	if (prise == 0) {
		hero.items.i1++;
		cout << "Znaleziono jablko" << endl;
	}if (prise == 1) {
		hero.items.i2++;
		cout << "Znaleziono sok" << endl;
	}if (prise == 2) {
		hero.items.i3++;
		cout << "Znaleziono hp potion" << endl;
	}if (prise == 3) {
		hero.items.i4++;
		cout << "Znaleziono stamina potion" << endl;
	}if (prise == 4) {
		hero.items.i5++;
		cout << "Znaleziono max hp potion" << endl;
	}if (prise == 5) {
		hero.items.i6++;
		cout << "Znaleziono max stamina potion" << endl;
	}
	klawisz = _getch();// ¿eby komunikat nie znika³ od razu
	system("cls");
}

void walkaBear() {//funkcja walki z niedŸwiedziem

	if (bear.hp < 1) {// jeœli zabiliœmy potwora
		hero.exp += bear.poziom * 10;
		hero.pumie += 1;
		hero.gold += bear.poziom;
		pole[bohX][bohY] = 'p';
		system("cls");
		return;
	}
	if (hero.hp < 1) {// jeœli potwór zabi³ nas
		hero.hp = hero.hpMax;
		hero.stamina = hero.staminaMax;
		hero.gold = 0;
		hero.items = { 0,0,0,0,0,0 };
		wioska = 1;
		las = 0;
		system("cls");
		return;
	}



	cout << endl << endl;
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}cout << "          ";
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}
	cout << endl;
	for (int i = 0; i < 22; i++) {
		cout << boh;
	}
	cout << "      BEAR" << endl;
	for (int i = 0; i < 22; i++) {
		cout << boh;
	}cout << endl << "  ";
	for (int i = 0; i < 18; i++) {
		cout << boh;
	}
	cout << "        HP: " << bear.hp << endl << "  ";
	cout << boh << boh << boh << boh << "  " << boh << boh << boh << boh << boh << boh << "  " << boh << boh << boh << boh << endl << "  ";
	for (int i = 0; i < 8; i++) {
		cout << boh;
	}
	cout << "  ";
	for (int i = 0; i < 8; i++) {
		cout << boh;
	}
	cout << "        Poziom: " << bear.poziom << endl << "  ";
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}cout << "  " << boh << boh << "  ";
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}cout << endl << "  ";
	for (int i = 0; i < 18; i++) {
		cout << boh;
	}cout << "        Slabosc: ";
	if (bear.slabosc == 0) {
		cout << "Sila" << endl;
	}if (bear.slabosc == 1) {
		cout << "Szybkosc" << endl;
	}if (bear.slabosc == 2) {
		cout << "Zrecznosc" << endl;
	}if (bear.slabosc == 3) {
		cout << "Magia" << endl;
	}
	cout << endl << endl<< endl<<endl;
	cout.width(30);
	cout << left << "1. ATAK" << "2. ODWROT" << endl << endl;
	cout.width(30);
	cout << left << "3. ITEM" << "4. NIC (+1 stamina)" << endl << endl << endl;
	cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
		<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
		<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;



	klawisz = _getch();

	if (klawisz == '1') {// wybór ataku
		system("cls");
		cout << endl << endl;
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "          ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}
		cout << endl;
		for (int i = 0; i < 22; i++) {
			cout << boh;
		}
		cout << "      BEAR" << endl;
		for (int i = 0; i < 22; i++) {
			cout << boh;
		}cout << endl << "  ";
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}
		cout << "        HP: " << bear.hp << endl << "  ";
		cout << boh << boh << boh << boh << "  " << boh << boh << boh << boh << boh << boh << "  " << boh << boh << boh << boh << endl << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}
		cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}
		cout << "        Poziom: " << bear.poziom << endl << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "  " << boh << boh << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << endl << "  ";
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << "        Slabosc: ";
		if (bear.slabosc == 0) {
			cout << "Sila" << endl;
		}if (bear.slabosc == 1) {
			cout << "Szybkosc" << endl;
		}if (bear.slabosc == 2) {
			cout << "Zrecznosc" << endl;
		}if (bear.slabosc == 3) {
			cout << "Magia" << endl;
		}
		cout << endl << endl << endl << endl;
		cout.width(30);
		cout << left << "1. Sila" << "2. Szybkosc" << endl << endl;
		cout.width(30);
		cout << left << "3. Zrecznosc" << "4. Magia" << endl << endl;
		cout << "q-cofnij" << endl << endl << endl;
		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		klawisz = _getch();
		if (hero.stamina > 0) {
			if (klawisz == '1') {
				bear.hp -= hero.sila;
				if (bear.slabosc == 0) {// sprawdza czy wybraliœmy s³aboœæ potwora
					bear.hp -= hero.sila;
				}
			}else if (klawisz == '2') {
				bear.hp -= hero.szybk;
				if (bear.slabosc == 1) {
					bear.hp -= hero.szybk;
				}
			}else if (klawisz == '3') {
				bear.hp -= hero.zrecz;
				if (bear.slabosc == 2) {
					bear.hp -= hero.zrecz;
				}
			}else if (klawisz == '4') {
				bear.hp -= hero.magia;
				if (bear.slabosc == 3) {
					bear.hp -= hero.magia;
				}
			}
			hero.stamina--;
			if (bear.hp > 0) {
				hero.hp -= bear.poziom;
			}
		}
		system("cls");
		walkaBear();
	}
	else if (klawisz == '3') {// wybór itemów
		system("cls");
		cout << endl << endl;
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "          ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}
		cout << endl;
		for (int i = 0; i < 22; i++) {
			cout << boh;
		}
		cout << "      BEAR" << endl;
		for (int i = 0; i < 22; i++) {
			cout << boh;
		}cout << endl << "  ";
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}
		cout << "        HP: " << bear.hp << endl << "  ";
		cout << boh << boh << boh << boh << "  " << boh << boh << boh << boh << boh << boh << "  " << boh << boh << boh << boh << endl << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}
		cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}
		cout << "        Poziom: " << bear.poziom << endl << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "  " << boh << boh << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << endl << "  ";
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << "        Slabosc: ";
		if (bear.slabosc == 0) {
			cout << "Sila" << endl;
		}if (bear.slabosc == 1) {
			cout << "Szybkosc" << endl;
		}if (bear.slabosc == 2) {
			cout << "Zrecznosc" << endl;
		}if (bear.slabosc == 3) {
			cout << "Magia" << endl;
		}
		cout << endl << endl << endl << endl;
		cout << "1. Jablko (+3 hp)(" << hero.items.i1 << ")" << endl;
		cout << "2. Sok (+1 stamina)(" << hero.items.i2 << ")" << endl;
		cout << "3. HP potion (+10 hp)(" << hero.items.i3 << ")" << endl;
		cout << "4. Stamina potion (+5 stamina)(" << hero.items.i4 << ")" << endl;
		cout << "5. MAXHP potion (+5 maxhp)(" << hero.items.i5 << ")" << endl;
		cout << "6. MAXSTAMINA potion (+1 maxstamina)(" << hero.items.i6 << ")" << endl;
		cout << "q-cofnij" << endl << endl << endl;
		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;
		klawisz = _getch();
		if (klawisz == '1') {
			if (hero.items.i1 > 0) {
				hero.hp += 3;
				if (hero.hp > hero.hpMax) {
					hero.hp = hero.hpMax;
				}
				hero.items.i1--;
			}
			system("cls");
			walkaBear();
		}else if (klawisz == '2') {
			if (hero.items.i2 > 0) {
				hero.stamina++;
				if (hero.stamina > hero.staminaMax) {
					hero.stamina = hero.staminaMax;
				}
				hero.items.i2--;
			}
			system("cls");
			walkaBear();
		}else if (klawisz == '3') {
			if (hero.items.i3 > 0) {
				hero.hp += 10;
				if (hero.hp > hero.hpMax) {
					hero.hp = hero.hpMax;
				}
				hero.items.i3--;
			}
			system("cls");
			walkaBear();
		}else if (klawisz == '4') {
			if (hero.items.i4 > 0) {
				hero.stamina += 5;
				if (hero.stamina > hero.staminaMax) {
					hero.stamina = hero.staminaMax;
				}
				hero.items.i4--;
			}
			system("cls");
			walkaBear();
		}else if (klawisz == '5') {
			if (hero.items.i5 > 0) {
				hero.hp += 5;
				hero.items.i5--;
				hero.hpMax += 5;
			}
			system("cls");
			walkaBear();
		}else if (klawisz == '6') {
			if (hero.items.i6 > 0) {
				hero.staminaMax++;
				hero.stamina++;
				hero.items.i6--;
				
			}
			system("cls");
			walkaBear();
		}else if (klawisz == 'q') {
			system("cls");
			walkaBear();
		}
	}
	else if (klawisz == '2') {
		system("cls");
		return;
	}
	else if (klawisz == '4') {
		hero.hp -= bear.poziom;
		hero.stamina++;
		if (hero.stamina > hero.staminaMax) {
			hero.stamina = hero.staminaMax;
		}
		system("cls");
		walkaBear();
	}
}
void walkaGhost() {// wygl¹da podobnie jak walkaBear() tylko rysunek jest inny

	if (ghost.hp < 1) {
		hero.exp += ghost.poziom * 10;
		hero.pumie += 3;
		hero.gold += ghost.poziom;
		pole[bohX][bohY] = 'p';
		system("cls");
		return;
	}
	if (hero.hp < 1) {
		hero.hp = hero.hpMax;
		hero.stamina = hero.staminaMax;
		hero.gold = 0;
		hero.items = { 0,0,0,0,0,0 };
		wioska = 1;
		las = 0;
		system("cls");
		return;
	}



	cout << endl << endl << "      ";
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}
	cout << endl << "    ";
	for (int i = 0; i < 10; i++) {
		cout << boh;
	}
	cout << "          GHOST" << endl;
	cout << "  ";
	for (int i = 0; i < 14; i++) {
		cout << boh;
	}cout << endl;
	cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh;
	cout << "      HP: " << ghost.hp << endl;
	cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh << endl;
	for (int i = 0; i < 18; i++) {
		cout << boh;
	}cout << "      Poziom: " << ghost.poziom << endl;
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}cout << "  " << boh << boh << "  ";
	for (int i = 0; i < 6; i++) {
		cout << boh;
	}cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << boh;
	}cout << "  ";
	for (int i = 0; i < 8; i++) {
		cout << boh;
	}cout << "      Slabosc: ";
	if (ghost.slabosc == 0) {
		cout << "Sila" << endl;
	}if (ghost.slabosc == 1) {
		cout << "Szybkosc" << endl;
	}if (ghost.slabosc == 2) {
		cout << "Zrecznosc" << endl;
	}if (ghost.slabosc == 3) {
		cout << "Magia" << endl;
	}
	for (int i = 0; i < 18; i++) {
		cout << boh;
	}cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << boh << boh << "  ";
	}cout << boh << boh << endl;
	for (int i = 0; i < 4; i++) {
		cout << boh << boh << "  ";
	}cout << boh << boh << endl << endl;
	cout.width(30);
	cout << left << "1. ATAK" << "2. ODWROT" << endl << endl;
	cout.width(30);
	cout << left << "3. ITEM" << "4. NIC (+1 stamina)" << endl << endl << endl;
	cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
		<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
		<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;



	klawisz = _getch();


	if (klawisz == '1') {
		system("cls");
		cout << endl << endl << "      ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}
		cout << endl << "    ";
		for (int i = 0; i < 10; i++) {
			cout << boh;
		}
		cout << "          GHOST" << endl;
		cout << "  ";
		for (int i = 0; i < 14; i++) {
			cout << boh;
		}cout << endl;
		cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh;
		cout << "      HP: " << ghost.hp << endl;
		cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh << endl;
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << "      Poziom: " << ghost.poziom << endl;
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "  " << boh << boh << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << endl;
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}cout << "      Slabosc: ";
		if (ghost.slabosc == 0) {
			cout << "Sila" << endl;
		}if (ghost.slabosc == 1) {
			cout << "Szybkosc" << endl;
		}if (ghost.slabosc == 2) {
			cout << "Zrecznosc" << endl;
		}if (ghost.slabosc == 3) {
			cout << "Magia" << endl;
		}
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << endl;
		for (int i = 0; i < 4; i++) {
			cout << boh << boh << "  ";
		}cout << boh << boh << endl;
		for (int i = 0; i < 4; i++) {
			cout << boh << boh << "  ";
		}cout << boh << boh << endl << endl;
		cout.width(30);
		cout << left << "1. Sila" << "2. Szybkosc" << endl << endl;
		cout.width(30);
		cout << left << "3. Zrecznosc" << "4. Magia" << endl << endl;
		cout << "q-cofnij" << endl << endl << endl;
		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		klawisz = _getch();
		if (hero.stamina > 0) {
			if (klawisz == '1') {
				ghost.hp -= hero.sila;
				if (ghost.slabosc == 0) {
					ghost.hp -= hero.sila;
				}
			}if (klawisz == '2') {
				ghost.hp -= hero.szybk;
				if (ghost.slabosc == 1) {
					ghost.hp -= hero.szybk;
				}
			}if (klawisz == '3') {
				ghost.hp -= hero.zrecz;
				if (ghost.slabosc == 2) {
					ghost.hp -= hero.zrecz;
				}
			}if (klawisz == '4') {
				ghost.hp -= hero.magia;
				if (ghost.slabosc == 3) {
					ghost.hp -= hero.magia;
				}
			}
			hero.stamina--;
			if (ghost.hp > 0) {
				hero.hp -= ghost.poziom;
			}
		}
		system("cls");
		walkaGhost();
	}
	else if (klawisz == '3') {
		system("cls");
		cout << endl << endl << "      ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}
		cout << endl << "    ";
		for (int i = 0; i < 10; i++) {
			cout << boh;
		}
		cout << "          GHOST" << endl;
		cout << "  ";
		for (int i = 0; i < 14; i++) {
			cout << boh;
		}cout << endl;
		cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh;
		cout << "      HP: " << ghost.hp << endl;
		cout << boh << boh << boh << boh << "    " << boh << boh << "    " << boh << boh << boh << boh << endl;
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << "      Poziom: " << ghost.poziom << endl;
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << "  " << boh << boh << "  ";
		for (int i = 0; i < 6; i++) {
			cout << boh;
		}cout << endl;
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << boh;
		}cout << "      Slabosc: ";
		if (ghost.slabosc == 0) {
			cout << "Sila" << endl;
		}if (ghost.slabosc == 1) {
			cout << "Szybkosc" << endl;
		}if (ghost.slabosc == 2) {
			cout << "Zrecznosc" << endl;
		}if (ghost.slabosc == 3) {
			cout << "Magia" << endl;
		}
		for (int i = 0; i < 18; i++) {
			cout << boh;
		}cout << endl;
		for (int i = 0; i < 4; i++) {
			cout << boh << boh << "  ";
		}cout << boh << boh << endl;
		for (int i = 0; i < 4; i++) {
			cout << boh << boh << "  ";
		}cout << boh << boh << endl << endl;
		cout << "1. Jablko (+3 hp)(" << hero.items.i1 << ")" << endl;
		cout << "2. Sok (+1 stamina)(" << hero.items.i2 << ")" << endl;
		cout << "3. HP potion (+10 hp)(" << hero.items.i3 << ")" << endl;
		cout << "4. Stamina potion (+5 stamina)(" << hero.items.i4 << ")" << endl;
		cout << "5. MAXHP potion (+5 maxhp)(" << hero.items.i5 << ")" << endl;
		cout << "6. MAXSTAMINA potion (+1 maxstamina)(" << hero.items.i6 << ")" << endl << endl;
		cout << "q-cofnij" << endl << endl << endl;
		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;
		klawisz = _getch();
		if (klawisz == '1') {
			if (hero.items.i1 > 0) {
				hero.hp += 3;
				if (hero.hp > hero.hpMax) {
					hero.hp = hero.hpMax;
				}
				hero.items.i1--;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == '2') {
			if (hero.items.i2 > 0) {
				hero.stamina++;
				if (hero.stamina > hero.staminaMax) {
					hero.stamina = hero.staminaMax;
				}
				hero.items.i2--;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == '3') {
			if (hero.items.i3 > 0) {
				hero.hp += 10;
				if (hero.hp > hero.hpMax) {
					hero.hp = hero.hpMax;
				}
				hero.items.i3--;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == '4') {
			if (hero.items.i4 > 0) {
				hero.stamina += 5;
				if (hero.stamina > hero.staminaMax) {
					hero.stamina = hero.staminaMax;
				}
				hero.items.i4--;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == '5') {
			if (hero.items.i5 > 0) {
				hero.hp += 5;
				hero.items.i5--;
				hero.hpMax += 5;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == '6') {
			if (hero.items.i6 > 0) {
				hero.stamina++;
				hero.items.i6--;
				hero.staminaMax++;
			}
			system("cls");
			walkaGhost();
		}else if (klawisz == 'q') {
			system("cls");
			walkaGhost();
		}
	}
	else if (klawisz == '2') {
		system("cls");
		return;
	}
	else if (klawisz == '4') {
		hero.hp -= ghost.poziom;
		hero.stamina++;
		if (hero.stamina > hero.staminaMax) {
			hero.stamina = hero.staminaMax;
		}
		system("cls");
		walkaGhost();
	}
}

void mapWioska() {
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'p';
		}
	}

	bohX = 12;
	bohY = 10;
	pole[bohX][bohY] = 'b';

	HANDLE hOut;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//do kolorów

	for (;;) {

		bohXpast = bohX;
		bohYpast = bohY;

		idzdoxy(0, 0);

		// rysowanie wioski w tablicy
		for (int i = 3; i < 6; i++) {
			for (int j = 5; j < 7; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 17; i < 22; i++) {
			for (int j = 5; j < 8; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 18; i < 20; i++) {
			for (int j = 13; j < 16; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 3; i < 5; i++) {
			for (int j = 3; j < 6; j++) {
				pole[j][i] = 'c';
			}
		}
		pole[4][2] = 'c';
		pole[2][4] = 'c';
		pole[6][4] = 'c';
		for (int i = 3; i < 5; i++) {
			for (int j = 18; j < 21; j++) {
				pole[j][i] = 'c';
			}
		}
		pole[19][2] = 'c';
		pole[17][4] = 'c';
		pole[21][4] = 'c';
		for (int i = 13; i < 16; i++) {
			pole[17][i] = 'e';
			pole[20][i] = 'e';
		}
		for (int i = 18; i < 20; i++) {
			pole[i][12] = 'e';
			pole[i][16] = 'e';
		}
		for (int i = 13; i < 17; i++) {
			for (int j = 3; j < 6; j++) {
				pole[j][i] = 'e';
			}
		}
		pole[2][12] = 'e';
		pole[4][12] = 'e';
		pole[6][12] = 'e';
		pole[2][13] = 'e';
		pole[6][13] = 'e';
		pole[4][6] = 'e';
		pole[4][15] = 'a';
		pole[4][16] = 'a';

		for (int i = 6; i < 8; i++) {
			pole[18][i] = 'e';
			pole[20][i] = 'e';
		}




		// wypisywanie ramki i wioski
		cout << lg;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;// podwójne bo komórki s¹ dwa razy wy¿sze ni¿ szersze
		}
		cout << pg;
		for (int i = 0; i < wysokosc; i++)
		{
			cout << endl << pion;
			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i] == 'p')
				{
					cout << "  ";
				}
				if (pole[j][i] == 'c')
				{
					SetConsoleTextAttribute(hOut, 12);// kolorki dla urozmaicenia
					cout << c << c;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'a')
				{
					SetConsoleTextAttribute(hOut, 14);
					cout << a << a;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'e')
				{
					SetConsoleTextAttribute(hOut, 8);
					cout << e << e;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'b')
				{
					cout << boh << boh;
				}
			}
			cout << pion;
		}
		cout << endl;
		cout << ld;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pd;
		cout << endl << endl << endl;

		//zaznaczanie na mapie budynków
		dom();
		sklep();
		wieza();
		teleport();

		// statystyki
		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		Sleep(50);// opóŸnienie w wyœwietlaniu bo czemu nie

		if (_kbhit())// poruszanie siê i wykonywanie interakcji
		{
			klawisz = _getch();// ify tak na wszelki wypadek
			if (klawisz < 0)
			{
				klawisz -= _getch();
			}
			if (klawisz > 224)
			{
				klawisz += _getch();
			}

			if (klawisz == gora)// przesuwanie bohatera po planszy
			{
				bohY--;
			}
			if (klawisz == dol)
			{
				bohY++;
			}
			if (klawisz == lewo)
			{
				bohX--;
			}
			if (klawisz == prawo)
			{
				bohX++;
			}
			if (pole[bohX][bohY] != 'p') {// ¿eby nie mo¿na by³o wejœæ w budynek ani nic
				bohX = bohXpast;
				bohY = bohYpast;
			}
			//interakcje z budynkami
			if (pole[bohX + 1][bohY] == 'd' || pole[bohX - 1][bohY] == 'd' || pole[bohX][bohY + 1] == 'd' || pole[bohX][bohY - 1] == 'd') {
				cout << "Press 'f' to rest" << endl;
				if (klawisz == 'f') {
					interactDom();
				}
			}
			else if (pole[bohX + 1][bohY] == 's' || pole[bohX - 1][bohY] == 's' || pole[bohX][bohY + 1] == 's' || pole[bohX][bohY - 1] == 's') {
				cout << "Press 'f' to buy items" << endl;
				if (klawisz == 'f') {
					interactSklep();
				}
			}
			else if (pole[bohX + 1][bohY] == 'w' || pole[bohX - 1][bohY] == 'w' || pole[bohX][bohY + 1] == 'w' || pole[bohX][bohY - 1] == 'w') {
				cout << "Press 'f' to learn" << endl;
				if (klawisz == 'f') {
					interactWieza();
				}
			}
			else if (pole[bohX + 1][bohY] == 't' || pole[bohX - 1][bohY] == 't' || pole[bohX][bohY + 1] == 't' || pole[bohX][bohY - 1] == 't') {
				cout << "Press 'f' to teleport" << endl;
				if (klawisz == 'f') {
					cout << "1- las" << endl << "2- wioska" << endl;
					if (hero.exp >= 4000) {
						cout << "3- lochy" << endl;
					}
					if (hero.exp >= 8000) {
						cout << "4- pustynia" << endl;
					}
					klawisz = _getch();
					if (klawisz == '1') {
						system("cls");
						las = 1;
						wioska = 0;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '2') {
						if (bohX > 18 && bohY > 12) {
							hero.exp += 30;
						}
						system("cls");
						las = 0;
						wioska = 1;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '3' && hero.exp >= 4000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 1;
						pus = 0;
						return;
					}
					if (klawisz == '4' && hero.exp >= 8000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 0;
						pus = 1;
						return;
					}
				}
			}
			else {
				cout << "                          " << endl;// ¿eby wymazaæ komunikat bo inaczej zostaje, poniewa¿ nadpisanie tutaj nie dociera
			}
		}

		pole[bohXpast][bohYpast] = 'p';// ¿eby bohater nie zostawia³ œladu
		pole[bohX][bohY] = 'b';

	}
}

void mapLas() {// bardzo podobne do mapWioska() tylko ma wiêcej rysowania, bo trzeba stworzyæ labirynt i zaznaczyæ potwory i skarby
	// zaznaczamy ca³y obszar jako las
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'l';
		}
	}
	// i wycinamy œcie¿ki
	for (int i = 13; i < 19; i++) {
		pole[0][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[2][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[3][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[19][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[20][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[22][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[23][i] = 'p';
	}for (int i = 1; i < 19; i++) {
		pole[1][i] = 'p';
	}for (int i = 7; i < 19; i++) {
		pole[4][i] = 'p';
	}for (int i = 6; i < 19; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 8; i++) {
		pole[6][i] = 'p';
	}for (int i = 13; i < 18; i++) {
		pole[6][i] = 'p';
	}for (int i = 5; i < 11; i++) {
		pole[9][i] = 'p';
	}for (int i = 4; i < 8; i++) {
		pole[12][i] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[12][i] = 'p';
	}for (int i = 1; i < 8; i++) {
		pole[14][i] = 'p';
	}for (int i = 12; i < 17; i++) {
		pole[14][i] = 'p';
	}for (int i = 7; i < 11; i++) {
		pole[17][i] = 'p';
	}for (int i = 12; i < 15; i++) {
		pole[17][i] = 'p';
	}for (int i = 1; i < 4; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 5; i++) {
		pole[i][3] = 'p';
	}for (int i = 2; i < 6; i++) {
		pole[i][7] = 'p';
	}for (int i = 5; i < 21; i++) {
		pole[i][10] = 'p';
	}for (int i = 5; i < 10; i++) {
		pole[i][15] = 'p';
	}for (int i = 9; i < 12; i++) {
		pole[i][16] = 'p';
	}for (int i = 7; i < 10; i++) {
		pole[i][13] = 'p';
	}for (int i = 6; i < 11; i++) {
		pole[i][2] = 'p';
	}for (int i = 7; i < 9; i++) {
		pole[i][5] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[i][7] = 'p';
	}for (int i = 15; i < 21; i++) {
		pole[i][1] = 'p';
	}for (int i = 15; i < 18; i++) {
		pole[i][3] = 'p';
	}for (int i = 19; i < 21; i++) {
		pole[i][6] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][12] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][16] = 'p';
	}pole[15][11] = 'p';
	pole[18][14] = 'p';
	pole[13][4] = 'p';
	// zaznaczamy skarby
	pole[1][1] = 'x';
	pole[4][4] = 'x';
	pole[10][2] = 'x';
	pole[9][13] = 'x';
	pole[7][17] = 'x';
	pole[16][17] = 'x';
	pole[17][4] = 'x';
	pole[20][3] = 'x';
	pole[19][5] = 'x';
	//zaznaczamy duchy
	pole[1][5] = 'g';
	pole[2][3] = 'g';
	pole[6][3] = 'g';
	pole[7][13] = 'g';
	pole[6][16] = 'g';
	pole[14][13] = 'g';
	pole[16][1] = 'g';
	pole[16][3] = 'g';
	pole[19][1] = 'g';
	pole[21][8] = 'g';
	//zaznaczamy misie
	pole[4][7] = 'n';
	pole[12][7] = 'n';
	pole[10][10] = 'n';
	pole[19][10] = 'n';
	pole[12][14] = 'n';
	pole[17][14] = 'n';
	//pocz¹tkowe wspó³rzêdne bohatera:
	bohX = 0;
	bohY = 13;
	pole[bohX][bohY] = 'b';

	system("cls");
	//znowu do kolorków
	HANDLE hOut;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (;;) {

		bohXpast = bohX;
		bohYpast = bohY;

		idzdoxy(0, 0);


		// jeszcze portale
		for (int i = 1; i < 3; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 21; i < 23; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 15; i < 18; i++) {
			pole[0][i] = 'e';
			pole[3][i] = 'e';
		}
		for (int i = 1; i < 3; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}
		for (int i = 15; i < 18; i++) {
			pole[20][i] = 'e';
			pole[23][i] = 'e';
		}
		for (int i = 21; i < 23; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}


		// wypisywanie
		cout << lg;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz<<poz;
		}
		cout << pg;
		for (int i = 0; i < wysokosc; i++)
		{
			cout << endl << pion;
			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i] == 'p')
				{
					cout << "  ";
				}
				if (pole[j][i] == 'l')
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//znowu kolorki
					cout << drzewa << drzewa;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'x')
				{
					cout << "><";
				}
				if (pole[j][i] == 'n')
				{
					cout << "!!";
				}
				if (pole[j][i] == 'g')
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "!!";
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'a') {
					SetConsoleTextAttribute(hOut, 14);
					cout << a << a;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'e') {
					SetConsoleTextAttribute(hOut, 8);
					cout << e << e;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'b')
				{
					cout << boh << boh;
				}
			}
			cout << pion;
		}
		cout << endl;
		cout << ld;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz<<poz;
		}
		cout << pd;
		cout << endl << endl << endl;


		teleport2();


		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		Sleep(100);// d³u¿sza przerwa ni¿ w wiosce, bo wiêcej pikseli do narysowania i bardziej siê zacina

		if (_kbhit())
		{
			klawisz = _getch();
			if (klawisz < 0)
			{
				klawisz -= _getch();
			}
			if (klawisz > 224)
			{
				klawisz += _getch();
			}

			if (klawisz == gora)
			{
				bohY--;
			}
			if (klawisz == dol)
			{
				bohY++;
			}
			if (klawisz == lewo)
			{
				bohX--;
			}
			if (klawisz == prawo)
			{
				bohX++;
			}
			if (pole[bohX][bohY] == 'x') {// skarb otwieramy po wejœciu na niego
				interactX();
				pole[bohX][bohY] = 'p';// znika z mapy
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'g') {// na potworki te¿ trzeba wejœæ, ¿eby z nimi walczyæ
				system("cls");
				srand(time(NULL));
				ghost.hp = 20 + (hero.exp / 30);
				ghost.poziom = rand() % 5 + 5;//losowe wartoœci
				ghost.slabosc = rand() % 4;
				walkaGhost();
				if (wioska == 1) {// w razie przegranej wraca do wioski
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'n') {
				system("cls");
				srand(time(NULL));
				bear.hp = 10 + (hero.exp / 50);
				bear.poziom = rand() % 5 + 1;
				bear.slabosc = rand() % 4;
				walkaBear();
				if (wioska == 1) {
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] != 'p') {
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX + 1][bohY] == 't' || pole[bohX - 1][bohY] == 't' || pole[bohX][bohY + 1] == 't' || pole[bohX][bohY - 1] == 't') {
				cout << "Press 'f' to teleport" << endl;
				if (klawisz == 'f') {
					cout << "1- las" << endl << "2- wioska" << endl;
					if (hero.exp >= 4000) {
						cout << "3- lochy" << endl;
					}
					if (hero.exp >= 8000) {
						cout << "4- pustynia" << endl;
					}
					klawisz = _getch();
					if (klawisz == '1') {
						system("cls");
						las = 1;
						wioska = 0;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '2') {
						if (bohX > 18 && bohY > 12) {
							hero.exp += 30;
						}
						system("cls");
						las = 0;
						wioska = 1;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '3' && hero.exp >= 4000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 1;
						pus = 0;
						return;
					}
					if (klawisz == '4' && hero.exp >= 8000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 0;
						pus = 1;
						return;
					}
				}
			}
			else {
				cout << "                          " << endl;
			}
		}

		pole[bohXpast][bohYpast] = 'p';
		pole[bohX][bohY] = 'b';

	}
}

void mapLoch() {
	
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'l';
		}
	}
	// i wycinamy œcie¿ki
	for (int i = 13; i < 19; i++) {
		pole[0][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[2][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[3][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[19][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[20][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[22][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[23][i] = 'p';
	}for (int i = 1; i < 19; i++) {
		pole[1][i] = 'p';
	}for (int i = 7; i < 19; i++) {
		pole[4][i] = 'p';
	}for (int i = 6; i < 19; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 8; i++) {
		pole[6][i] = 'p';
	}for (int i = 13; i < 18; i++) {
		pole[6][i] = 'p';
	}for (int i = 5; i < 11; i++) {
		pole[9][i] = 'p';
	}for (int i = 4; i < 8; i++) {
		pole[12][i] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[12][i] = 'p';
	}for (int i = 1; i < 8; i++) {
		pole[14][i] = 'p';
	}for (int i = 12; i < 17; i++) {
		pole[14][i] = 'p';
	}for (int i = 7; i < 11; i++) {
		pole[17][i] = 'p';
	}for (int i = 12; i < 15; i++) {
		pole[17][i] = 'p';
	}for (int i = 1; i < 4; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 5; i++) {
		pole[i][3] = 'p';
	}for (int i = 2; i < 6; i++) {
		pole[i][7] = 'p';
	}for (int i = 5; i < 21; i++) {
		pole[i][10] = 'p';
	}for (int i = 5; i < 10; i++) {
		pole[i][15] = 'p';
	}for (int i = 9; i < 12; i++) {
		pole[i][16] = 'p';
	}for (int i = 7; i < 10; i++) {
		pole[i][13] = 'p';
	}for (int i = 6; i < 11; i++) {
		pole[i][2] = 'p';
	}for (int i = 7; i < 9; i++) {
		pole[i][5] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[i][7] = 'p';
	}for (int i = 15; i < 21; i++) {
		pole[i][1] = 'p';
	}for (int i = 15; i < 18; i++) {
		pole[i][3] = 'p';
	}for (int i = 19; i < 21; i++) {
		pole[i][6] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][12] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][16] = 'p';
	}pole[15][11] = 'p';
	pole[18][14] = 'p';
	pole[13][4] = 'p';
	// zaznaczamy skarby
	pole[1][1] = 'x';
	pole[4][4] = 'x';
	pole[10][2] = 'x';
	pole[9][13] = 'x';
	pole[7][17] = 'x';
	pole[16][17] = 'x';
	pole[17][4] = 'x';
	pole[20][3] = 'x';
	pole[19][5] = 'x';
	//zaznaczamy duchy
	pole[1][5] = 'g';
	pole[2][3] = 'g';
	pole[6][3] = 'g';
	pole[7][13] = 'g';
	pole[6][16] = 'g';
	pole[14][13] = 'g';
	pole[16][1] = 'g';
	pole[16][3] = 'g';
	pole[19][1] = 'g';
	pole[21][8] = 'g';
	//zaznaczamy misie
	pole[4][7] = 'n';
	pole[12][7] = 'n';
	pole[10][10] = 'n';
	pole[19][10] = 'n';
	pole[12][14] = 'n';
	pole[17][14] = 'n';
	//pocz¹tkowe wspó³rzêdne bohatera:
	bohX = 0;
	bohY = 13;
	pole[bohX][bohY] = 'b';

	system("cls");
	//znowu do kolorków
	HANDLE hOut;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (;;) {

		bohXpast = bohX;
		bohYpast = bohY;

		idzdoxy(0, 0);


		// jeszcze portale
		for (int i = 1; i < 3; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 21; i < 23; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 15; i < 18; i++) {
			pole[0][i] = 'e';
			pole[3][i] = 'e';
		}
		for (int i = 1; i < 3; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}
		for (int i = 15; i < 18; i++) {
			pole[20][i] = 'e';
			pole[23][i] = 'e';
		}
		for (int i = 21; i < 23; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}


		// wypisywanie
		cout << lg;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pg;
		for (int i = 0; i < wysokosc; i++)
		{
			cout << endl << pion;
			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i] == 'p')
				{
					cout << "  ";
				}
				if (pole[j][i] == 'l')
				{
					SetConsoleTextAttribute(hOut, 8);
					cout << drzewa << drzewa;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'x')
				{
					cout << "><";
				}
				if (pole[j][i] == 'n')
				{
					cout << "!!";
				}
				if (pole[j][i] == 'g')
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "!!";
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'a') {
					SetConsoleTextAttribute(hOut, 14);
					cout << a << a;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'e') {
					SetConsoleTextAttribute(hOut, 8);
					cout << e << e;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'b')
				{
					cout << boh << boh;
				}
			}
			cout << pion;
		}
		cout << endl;
		cout << ld;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pd;
		cout << endl << endl << endl;


		teleport2();


		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		Sleep(100);// d³u¿sza przerwa ni¿ w wiosce, bo wiêcej pikseli do narysowania i bardziej siê zacina

		if (_kbhit())
		{
			klawisz = _getch();
			if (klawisz < 0)
			{
				klawisz -= _getch();
			}
			if (klawisz > 224)
			{
				klawisz += _getch();
			}

			if (klawisz == gora)
			{
				bohY--;
			}
			if (klawisz == dol)
			{
				bohY++;
			}
			if (klawisz == lewo)
			{
				bohX--;
			}
			if (klawisz == prawo)
			{
				bohX++;
			}
			if (pole[bohX][bohY] == 'x') {// skarb otwieramy po wejœciu na niego
				interactX();
				pole[bohX][bohY] = 'p';// znika z mapy
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'g') {// na potworki te¿ trzeba wejœæ, ¿eby z nimi walczyæ
				system("cls");
				srand(time(NULL));
				ghost.hp = 20 + (hero.exp / 15);
				ghost.poziom = rand() % 5 + 16;//losowe wartoœci
				ghost.slabosc = rand() % 4;
				walkaGhost();
				if (wioska == 1) {// w razie przegranej wraca do wioski
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'n') {
				system("cls");
				srand(time(NULL));
				bear.hp = 10 + (hero.exp / 25);
				bear.poziom = rand() % 5 +11;
				bear.slabosc = rand() % 4;
				walkaBear();
				if (wioska == 1) {
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] != 'p') {
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX + 1][bohY] == 't' || pole[bohX - 1][bohY] == 't' || pole[bohX][bohY + 1] == 't' || pole[bohX][bohY - 1] == 't') {
				cout << "Press 'f' to teleport" << endl;
				if (klawisz == 'f') {
					cout << "1- las" << endl << "2- wioska" << endl;
					if (hero.exp >= 4000) {
						cout << "3- lochy" << endl;
					}
					if (hero.exp >= 8000) {
						cout << "4- pustynia" << endl;
					}
					klawisz = _getch();
					if (klawisz == '1') {
						system("cls");
						las = 1;
						wioska = 0;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '2') {
						if (bohX > 18 && bohY > 12) {
							hero.exp += 30;
						}
						system("cls");
						las = 0;
						wioska = 1;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '3' && hero.exp >= 4000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 1;
						pus = 0;
						return;
					}
					if (klawisz == '4' && hero.exp >= 8000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 0;
						pus = 1;
						return;
					}
				}
			}
			else {
				cout << "                          " << endl;
			}
		}

		pole[bohXpast][bohYpast] = 'p';
		pole[bohX][bohY] = 'b';

	}
}

void mapPustynia() {

	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'l';
		}
	}
	// i wycinamy œcie¿ki
	for (int i = 13; i < 19; i++) {
		pole[0][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[2][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[3][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[19][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[20][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[22][i] = 'p';
	}for (int i = 13; i < 19; i++) {
		pole[23][i] = 'p';
	}for (int i = 1; i < 19; i++) {
		pole[1][i] = 'p';
	}for (int i = 7; i < 19; i++) {
		pole[4][i] = 'p';
	}for (int i = 6; i < 19; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 8; i++) {
		pole[6][i] = 'p';
	}for (int i = 13; i < 18; i++) {
		pole[6][i] = 'p';
	}for (int i = 5; i < 11; i++) {
		pole[9][i] = 'p';
	}for (int i = 4; i < 8; i++) {
		pole[12][i] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[12][i] = 'p';
	}for (int i = 1; i < 8; i++) {
		pole[14][i] = 'p';
	}for (int i = 12; i < 17; i++) {
		pole[14][i] = 'p';
	}for (int i = 7; i < 11; i++) {
		pole[17][i] = 'p';
	}for (int i = 12; i < 15; i++) {
		pole[17][i] = 'p';
	}for (int i = 1; i < 4; i++) {
		pole[21][i] = 'p';
	}for (int i = 2; i < 5; i++) {
		pole[i][3] = 'p';
	}for (int i = 2; i < 6; i++) {
		pole[i][7] = 'p';
	}for (int i = 5; i < 21; i++) {
		pole[i][10] = 'p';
	}for (int i = 5; i < 10; i++) {
		pole[i][15] = 'p';
	}for (int i = 9; i < 12; i++) {
		pole[i][16] = 'p';
	}for (int i = 7; i < 10; i++) {
		pole[i][13] = 'p';
	}for (int i = 6; i < 11; i++) {
		pole[i][2] = 'p';
	}for (int i = 7; i < 9; i++) {
		pole[i][5] = 'p';
	}for (int i = 10; i < 17; i++) {
		pole[i][7] = 'p';
	}for (int i = 15; i < 21; i++) {
		pole[i][1] = 'p';
	}for (int i = 15; i < 18; i++) {
		pole[i][3] = 'p';
	}for (int i = 19; i < 21; i++) {
		pole[i][6] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][12] = 'p';
	}for (int i = 15; i < 17; i++) {
		pole[i][16] = 'p';
	}pole[15][11] = 'p';
	pole[18][14] = 'p';
	pole[13][4] = 'p';
	// zaznaczamy skarby
	pole[1][1] = 'x';
	pole[4][4] = 'x';
	pole[10][2] = 'x';
	pole[9][13] = 'x';
	pole[7][17] = 'x';
	pole[16][17] = 'x';
	pole[17][4] = 'x';
	pole[20][3] = 'x';
	pole[19][5] = 'x';
	//zaznaczamy duchy
	pole[1][5] = 'g';
	pole[2][3] = 'g';
	pole[6][3] = 'g';
	pole[7][13] = 'g';
	pole[6][16] = 'g';
	pole[14][13] = 'g';
	pole[16][1] = 'g';
	pole[16][3] = 'g';
	pole[19][1] = 'g';
	pole[21][8] = 'g';
	//zaznaczamy misie
	pole[4][7] = 'n';
	pole[12][7] = 'n';
	pole[10][10] = 'n';
	pole[19][10] = 'n';
	pole[12][14] = 'n';
	pole[17][14] = 'n';
	//pocz¹tkowe wspó³rzêdne bohatera:
	bohX = 0;
	bohY = 13;
	pole[bohX][bohY] = 'b';

	system("cls");
	//znowu do kolorków
	HANDLE hOut;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (;;) {

		bohXpast = bohX;
		bohYpast = bohY;

		idzdoxy(0, 0);


		// jeszcze portale
		for (int i = 1; i < 3; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 21; i < 23; i++) {
			for (int j = 15; j < 18; j++) {
				pole[i][j] = 'a';
			}
		}
		for (int i = 15; i < 18; i++) {
			pole[0][i] = 'e';
			pole[3][i] = 'e';
		}
		for (int i = 1; i < 3; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}
		for (int i = 15; i < 18; i++) {
			pole[20][i] = 'e';
			pole[23][i] = 'e';
		}
		for (int i = 21; i < 23; i++) {
			pole[i][14] = 'e';
			pole[i][18] = 'e';
		}


		// wypisywanie
		cout << lg;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pg;
		for (int i = 0; i < wysokosc; i++)
		{
			cout << endl << pion;
			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i] == 'p')
				{
					cout << "  ";
				}
				if (pole[j][i] == 'l')
				{
					SetConsoleTextAttribute(hOut, 14);
					cout << drzewa << drzewa;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'x')
				{
					cout << "><";
				}
				if (pole[j][i] == 'n')
				{
					cout << "!!";
				}
				if (pole[j][i] == 'g')
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "!!";
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'a') {
					SetConsoleTextAttribute(hOut, 14);
					cout << a << a;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'e') {
					SetConsoleTextAttribute(hOut, 8);
					cout << e << e;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				if (pole[j][i] == 'b')
				{
					cout << boh << boh;
				}
			}
			cout << pion;
		}
		cout << endl;
		cout << ld;
		for (int i = 0; i < szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pd;
		cout << endl << endl << endl;


		teleport2();


		cout << "GOLD: " << hero.gold << endl << "EXP: " << hero.exp << endl << "HP: " << hero.hp << "/" << hero.hpMax << endl
			<< "STAMINA: " << hero.stamina << "/" << hero.staminaMax << endl << "SILA: " << hero.sila << endl << "SZYBKOSC: " << hero.szybk << endl
			<< "ZRECZNOSC: " << hero.zrecz << endl << "MAGIA: " << hero.magia << endl << "PUNKTY UMIEJETNOSCI: " << hero.pumie << endl;

		Sleep(100);// d³u¿sza przerwa ni¿ w wiosce, bo wiêcej pikseli do narysowania i bardziej siê zacina

		if (_kbhit())
		{
			klawisz = _getch();
			if (klawisz < 0)
			{
				klawisz -= _getch();
			}
			if (klawisz > 224)
			{
				klawisz += _getch();
			}

			if (klawisz == gora)
			{
				bohY--;
			}
			if (klawisz == dol)
			{
				bohY++;
			}
			if (klawisz == lewo)
			{
				bohX--;
			}
			if (klawisz == prawo)
			{
				bohX++;
			}
			if (pole[bohX][bohY] == 'x') {// skarb otwieramy po wejœciu na niego
				interactX();
				pole[bohX][bohY] = 'p';// znika z mapy
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'g') {// na potworki te¿ trzeba wejœæ, ¿eby z nimi walczyæ
				system("cls");
				srand(time(NULL));
				ghost.hp = 20 + (hero.exp / 5);
				ghost.poziom = rand() % 5 + 26;//losowe wartoœci
				ghost.slabosc = rand() % 4;
				walkaGhost();
				if (wioska == 1) {// w razie przegranej wraca do wioski
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] == 'n') {
				system("cls");
				srand(time(NULL));
				bear.hp = 10 + (hero.exp / 15);
				bear.poziom = rand() % 5 + 21;
				bear.slabosc = rand() % 4;
				walkaBear();
				if (wioska == 1) {
					return;
				}
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX][bohY] != 'p') {
				bohX = bohXpast;
				bohY = bohYpast;
			}
			if (pole[bohX + 1][bohY] == 't' || pole[bohX - 1][bohY] == 't' || pole[bohX][bohY + 1] == 't' || pole[bohX][bohY - 1] == 't') {
				cout << "Press 'f' to teleport" << endl;
				if (klawisz == 'f') {
					cout << "1- las" << endl << "2- wioska" << endl;
					if (hero.exp >= 4000) {
						cout << "3- lochy" << endl;
					}
					if (hero.exp >= 8000) {
						cout << "4- pustynia" << endl;
					}
					klawisz = _getch();
					if (klawisz == '1') {
						system("cls");
						las = 1;
						wioska = 0;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '2') {
						if (bohX > 18 && bohY > 12) {
							hero.exp += 30;
						}
						system("cls");
						las = 0;
						wioska = 1;
						loch = 0;
						pus = 0;
						return;
					}
					if (klawisz == '3' && hero.exp >= 4000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 1;
						pus = 0;
						return;
					}
					if (klawisz == '4' && hero.exp >= 8000) {
						system("cls");
						las = 0;
						wioska = 0;
						loch = 0;
						pus = 1;
						return;
					}
				}
			}
			else {
				cout << "                          " << endl;
			}
		}

		pole[bohXpast][bohYpast] = 'p';
		pole[bohX][bohY] = 'b';

	}
}

int main() {
	for (;;) {// nieskoñczona pêtla, ¿eby gra nie mia³a koñca :)
		if (wioska == 1) {// sprawdza któr¹ mapê wyœwietlaæ
			mapWioska();
		}
		if (las == 1) {
			mapLas();
		}
		if (loch == 1) {
			mapLoch();
		}
		if (pus == 1) {
			mapPustynia();
		}
	}


	return 0;
}