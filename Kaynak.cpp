#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#define PI 3.141592653
#define EU 2.718281828
using namespace std;
bool tccb(string *s);
bool islemYap(string* s);
bool parantezYap(string* s);
string strDegis(string s, int ilk, int son, string yeni);
string boslukSil(string s);
bool charIslem(char girdi, char onceki);
bool charVarMi(char ch, string kontrol);
bool girdiKontrol(string* girdi);
bool hesapla(string* s);
double faktoriyel(double sayi);
bool sayiAyarla(string *sayi);
int main()
{

cls:
	system("cls");
	cout << "^-HESAP MAKINESI-^" << endl << endl;
	bool makine = true, hatali = false;
	cout << endl << "     ISLEM LISTESI \n---------------------------------------------------\n     '+' -> TOPLAMA -> 2+3                        |\n"
		"     '-' -> CIKARMA -> 5-4                        |\n"
		"     '*' -> CARPMA -> 3*2                         |\n"
		"     '/' -> BOLME -> 4/2                          |\n"
		"     '^' -> KUVVET ALMA -> 2^(1+2)^2              |\n"
		"     '!' -> FAKTORIYEL -> (3+2)!                  |\n"
		"     'k' -> KAREKOK -> (234-232)k(132+12)         |\n"
		"     's' -> SINUS FONKSIYONU -> s(p-p/2)          |\n"
		"     'c' -> COSINUS FONKSIYONU -> c(p-p/2)        |\n"
		"     't' -> TANJANT FONKSIYONU -> t(p/2-p/4)      |\n"
		"     'ct' -> COTANJANT FONKSIYONU -> ct(p/2-p/4)  |\n"
		"     'l' -> LOGARITMA FONKSIYONU -> l((1+1),(8+8))|\n"
		"---------------------------------------------------\n\n\     SEMBOLLER\n---------------------------------------------------\n"
		"     '%' -> YUZDE -> %15 = 15/100                 |\n"
		"     'e' -> EULER SAYISI = 2.718218               |\n"
		"     'p' -> PI SAYISI = 3.141593                  |\n---------------------------------------------------" << endl << endl << "     Ekrani Temizlemek Icin 'cls' Yaziniz." << endl << endl << "     HESAPLAMA ISLEMI GIRDISI";
	cout << endl << "---------------------------------------------------" << endl;
	string girdi = "";
	while (1)
	{
		getline(cin, girdi);
		if (girdi == "cls")
			goto cls;
		if (hesapla(&girdi))
			cout << girdi << endl;
		else
			cout << "Hatali!" << endl;
	}
}





//0123456789+-*/^!ksctlep%.(),
bool hesapla(string* s)
{
	if (girdiKontrol(s) && islemYap(s))
		return 1;
	return 0;
}
bool islemYap(string* s)
{
	//islemyap
	if (!parantezYap(s))
		return 0;
	int smik = s->length();
	int oncekiIsaret = -1;
	string atanacak = "";
	for (int i = 0; i < smik; i++)
	{
		if (charVarMi((*s)[i], "+-*/"))
		{
			if (!((*s)[i] == '-' && i != 0 && (*s)[i - 1] == '('))
				oncekiIsaret = i;
			continue;
		}
		if ((*s)[i] == '^')
		{
			int bas, son;
			double taban, kuvvet;
			bas = oncekiIsaret + 1;
			if ((*s)[bas] == '(') {
				atanacak = s->substr(bas + 1, i - bas - 2);
				if (sayiAyarla(&atanacak))
					taban = stod(atanacak);
				else return 0;
			}
			else
			{
				atanacak = s->substr(bas, i - bas);
				if (sayiAyarla(&atanacak))
					taban = stod(atanacak);
				else return 0;
			}
			int parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
					parsay++;
				if ((*s)[j] == ')')
					parsay--;
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string skuvvet = s->substr(i + 1, j - i - 1);
					if (!islemYap(&skuvvet))
						return 0;
					kuvvet = stod(skuvvet);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string skuvvet = s->substr(i + 1, j - i);
					if (!islemYap(&skuvvet))
						return 0;
					kuvvet = stod(skuvvet);
					son = j;
					break;
				}
			}
			double sonuc = pow(taban, kuvvet);
			string atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, bas, son, ssonuc);
			smik = s->length();
			i = bas + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == '!')
		{
			int bas;
			bas = oncekiIsaret + 1;
			double ic;
			if ((*s)[bas] == '(')
			{
				atanacak = s->substr(bas + 1, i - bas - 2);
				if (!sayiAyarla(&atanacak))
					return 0;
				ic = stod(atanacak);
			}
			else
			{
				atanacak = s->substr(bas, i - bas);
				if (!sayiAyarla(&atanacak))
					return 0;
				ic = stod(atanacak);
			}
			double sonuc = faktoriyel(ic);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, bas, i, ssonuc);
			smik = s->length();
			i = bas + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 'k')
		{
			int bas = oncekiIsaret + 1, son;
			double kuvvet, ic;
			if ((*s)[bas] == '(') {
				atanacak = s->substr(bas + 1, i - bas - 2);
				if (!sayiAyarla(&atanacak))
					return 0;
				kuvvet = stod(atanacak);
			}
			else if (i != 0 && !charVarMi((*s)[i - 1], "+-*/"))
			{
				atanacak = s->substr(bas, i - bas);
				if (!sayiAyarla(&atanacak))
					return 0;
				kuvvet = stod(atanacak);
			}
			else
				kuvvet = 2;
			int parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string s_ic = s->substr(i + 1, j - i - 1);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string s_ic = s->substr(i + 1, j - i);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j;
					break;
				}

			}
			double sonuc = pow(ic, 1 / kuvvet);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, bas, son, ssonuc);
			smik = s->length();
			i = bas + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 's')
		{
			double ic;
			int son, parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string s_ic = s->substr(i + 1, j - i - 1);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string s_ic = s->substr(i + 1, j - i);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j;
					break;
				}

			}
			double sonuc = sin(ic);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, i, son, ssonuc);
			smik = s->length();
			int bas = i;
			i = i + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 'c')
		{
			bool cotMu = false;
			if ((*s)[i + 1] == 't')
				cotMu = true;
			double ic;
			int son, parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string s_ic;
					if (!cotMu)
						s_ic = s->substr(i + 1, j - i - 1);
					else
						s_ic = s->substr(i + 2, j - i - 2);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string s_ic;
					if (!cotMu)
						s_ic = s->substr(i + 1, j - i);
					else
						s_ic = s->substr(i + 2, j - i - 1);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j;
					break;
				}
			}
			double sonuc;
			if (!cotMu)
				sonuc = cos(ic);
			else
				sonuc = 1 / tan(ic);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, i, son, ssonuc);
			smik = s->length();
			int bas = i;
			i = i + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 't')
		{
			double ic;
			int son, parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string s_ic = s->substr(i + 1, j - i - 1);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string s_ic = s->substr(i + 1, j - i);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j;
					break;
				}

			}
			double sonuc = tan(ic);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, i, son, ssonuc);
			smik = s->length();
			int bas = i;
			i = i + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 'l')
		{
			double taban, ic;
			int son, parsay = 0, virgul;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
					if (parsay == 0)
					{
						string s_ic = s->substr(virgul + 1, j - virgul - 1);
						if (!islemYap(&s_ic))
							return 0;
						ic = stod(s_ic);
					}
				}
				if (parsay == 1 && (*s)[j] == ',')
				{
					virgul = j;
					string s_taban = s->substr(i + 2, j - i - 2);
					if (!islemYap(&s_taban))
						return 0;
					taban = stod(s_taban);
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					son = j;
					break;
				}

			}
			double sonuc = log(ic) / log(taban);
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, i, son, ssonuc);
			smik = s->length();
			int bas = i;
			i = i + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == 'e')
		{
			string s_e = to_string(EU);
			*s = strDegis(*s, i, i, s_e);
			smik = s->length();
			i = i + s_e.length();
			if (i == smik)
				break;
			continue;
		}
		if ((*s)[i] == 'p')
		{
			string s_p = to_string(PI);
			*s = strDegis(*s, i, i, s_p);
			smik = s->length();
			i = i + s_p.length();
			if (i == smik)
				break;
			continue;
		}
		if ((*s)[i] == '%')
		{
			double ic;
			int son, parsay = 0;
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '(')
				{
					parsay++;
				}
				if ((*s)[j] == ')')
				{
					parsay--;
				}
				if (parsay == 0 && charVarMi((*s)[j], "+-*/"))
				{
					string s_ic = s->substr(i + 1, j - i - 1);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					string s_ic = s->substr(i + 1, j - i);
					if (!islemYap(&s_ic))
						return 0;
					ic = stod(s_ic);
					son = j;
					break;
				}

			}
			double sonuc = ic / 100;
			atanacak = to_string(sonuc);
			if (!sayiAyarla(&atanacak))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + atanacak + ')' : atanacak;
			*s = strDegis(*s, i, son, ssonuc);
			smik = s->length();
			int bas = i;
			i = i + ssonuc.length() - 1;
			if (bas == 0 && i + 1 == smik && (*s)[0] == '(')
			{
				*s = s->substr(1, smik - 2);
				break;
			}
			continue;
		}

	}
	if (!tccb(s))
		return 0;
	if (!sayiAyarla(s))
		return 0;
	return 1;
}
bool tccb(string *s)
{
	//tccb
	if ((*s)[0] == '+')
		*s = s->substr(1);
	if ((*s)[0] == '-')
		*s = '0' + *s;
	int smik = s->length(), oncekiIsaret = -1;
	for (int i = 0; i < smik; i++)
	{
		if ((*s)[i] == '+' || ((*s)[i] == '-'&&i != 0 && (*s)[i - 1] != '('))
		{
			oncekiIsaret = i;
		}
		if ((*s)[i] == '*')
		{
			int son;
			string s1, s2;
			double ds1, ds2;
			s1 = s->substr(oncekiIsaret + 1, i - oncekiIsaret - 1);
			for (int j = i + 1; j < smik; j++)
			{
				if (charVarMi((*s)[j], "+-*/"))
				{
					s2 = s->substr(i + 1, j - i - 1);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					s2 = s->substr(i + 1, j - i);
					son = j;
					break;
				}
			}
			if (s1[0] == '(')
				s1 = s1.substr(1, s1.length() - 2);
			if (s2[0] == '(')
				s2 = s2.substr(1, s2.length() - 2);
			if (!sayiAyarla(&s1) || !sayiAyarla(&s2))
				return 0;
			ds1 = stod(s1);
			ds2 = stod(s2);
			double sonuc = ds1 * ds2;
			s1 = to_string(sonuc);
			if (!sayiAyarla(&s1))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + s1 + ')' : s1;
			*s = strDegis(*s, oncekiIsaret + 1, son, ssonuc);
			smik = s->length();
			i = oncekiIsaret + ssonuc.length() - 1;
			continue;
		}
		if ((*s)[i] == '/')
		{
			int son;
			string s1, s2;
			double ds1, ds2;
			s1 = s->substr(oncekiIsaret + 1, i - oncekiIsaret - 1);
			for (int j = i + 1; j < smik; j++)
			{
				if (charVarMi((*s)[j], "+-*/"))
				{
					s2 = s->substr(i + 1, j - i - 1);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					s2 = s->substr(i + 1, j - i);
					son = j;
					break;
				}
			}
			if (s1[0] == '(')
				s1 = s1.substr(1, s1.length() - 2);
			if (s2[0] == '(')
				s2 = s2.substr(1, s2.length() - 2);
			if (!sayiAyarla(&s1) || !sayiAyarla(&s2))
				return 0;
			ds1 = stod(s1);
			ds2 = stod(s2);
			double sonuc = ds1 / ds2;
			s1 = to_string(sonuc);
			if (!sayiAyarla(&s1))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + s1 + ')' : s1;
			*s = strDegis(*s, oncekiIsaret + 1, son, ssonuc);
			smik = s->length();
			i = oncekiIsaret + ssonuc.length() - 1;
			continue;
		}
	}
	for (int i = 0; i < smik; i++)
	{
		if ((*s)[i] == '+')
		{
			int son;
			string s1, s2;
			double ds1, ds2;
			s1 = s->substr(0, i);
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '+' || ((*s)[j] == '-' && (*s)[j - 1] != '('))
				{
					s2 = s->substr(i + 1, j - i - 1);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					s2 = s->substr(i + 1, j - i);
					son = j;
					break;
				}
			}
			if (s1[0] == '(')
				s1 = s1.substr(1, s1.length() - 2);
			if (s2[0] == '(')
				s2 = s2.substr(1, s2.length() - 2);
			if (!sayiAyarla(&s1) || !sayiAyarla(&s2))
				return 0;
			ds1 = stod(s1);
			ds2 = stod(s2);
			double sonuc = ds1 + ds2;
			s1 = to_string(sonuc);
			if (!sayiAyarla(&s1))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + s1 + ')' : s1;
			*s = strDegis(*s, 0, son, ssonuc);
			smik = s->length();
			i = ssonuc.length() - 1;
			if (i == smik - 1)
			{
				if ((*s)[0] == '(')
					*s = s->substr(1, s->length() - 2);
				break;
			}
			continue;
		}
		if ((*s)[i] == '-' && i != 0 && (*s)[i - 1] != '(')
		{
			int son;
			string s1, s2;
			double ds1, ds2;
			s1 = s->substr(0, i);
			for (int j = i + 1; j < smik; j++)
			{
				if ((*s)[j] == '+' || ((*s)[j] == '-' && (*s)[j - 1] != '('))
				{
					s2 = s->substr(i + 1, j - i - 1);
					son = j - 1;
					break;
				}
				if (j + 1 == smik)
				{
					s2 = s->substr(i + 1, j - i);
					son = j;
					break;
				}
			}
			if (s1[0] == '(')
				s1 = s1.substr(1, s1.length() - 2);
			if (s2[0] == '(')
				s2 = s2.substr(1, s2.length() - 2);
			if (!sayiAyarla(&s1) || !sayiAyarla(&s2))
				return 0;
			ds1 = stod(s1);
			ds2 = stod(s2);
			double sonuc = ds1 - ds2;
			s1 = to_string(sonuc);
			if (!sayiAyarla(&s1))
				return 0;
			string ssonuc = sonuc < 0 ? '(' + s1 + ')' : s1;
			*s = strDegis(*s, 0, son, ssonuc);
			smik = s->length();
			i = ssonuc.length() - 1;
			if (i == smik - 1)
			{
				if ((*s)[0] == '(')
					*s = s->substr(1, s->length() - 2);
				break;
			}
			continue;
		}
	}
	if (s->at(0) == '(')
		*s = s->substr(1, s->length() - 2);
	return 1;
}
// buradan aþaðýsý gayet düzgün çalýþmaktadýr.
bool parantezYap(string* s)
{
	//parantezyap
	int smik = s->length();
	int parsay = 0;
	{
		bool basveson = false;
		for (int i = 0; i < smik; i++)
		{
			if ((*s)[i] == '(') {
				if (i == 0)
					basveson = true;
				parsay++;
			}
			if ((*s)[i] == ')') {
				if (parsay == 0)
					return 0;
				if (i != smik - 1 && parsay == 1)
					basveson = false;
				parsay--;
			}
		}
		if (parsay != 0)
			return 0;
		if (basveson) {
			*s = s->substr(1, smik - 2);
			smik -= 2;
		}
	}
	int aPar = -1;
	//0123456789ep+-*/^!ksctl%.(),
	for (int i = 0; i < smik; i++)
	{
		if ((*s)[i] == '.')
		{
			for (int k = i + 1; k < smik; k++)
			{
				if (charVarMi((*s)[k], "+-*/^!k),") || k == smik - 1)
					break;
				else if ((*s)[k] == '.')
					return 0;
			}
		}
		if ((*s)[i] == ',')
			return 0;
		if ((*s)[i] == 'l')
		{
			int lparsay = 1;
			i += 2;
			bool virgul = false;
			while ((*s)[i] != ')' && lparsay != 0)
			{
				if ((*s)[i] == ',')
				{
					if ((virgul && lparsay == 1) || lparsay == 0)
						return 0;
					else if (lparsay == 1)
						virgul = true;
				}
				if ((*s)[i] == '(')
					lparsay++;
				if ((*s)[i] == ')') {
					lparsay--;
					if (i + 1 == smik)
						break;
				}
				i++;
			}
			i++;
		}
		if ((*s)[i] == '(')
		{
			if (parsay == 0)
				aPar = i;
			parsay++;
		}
		if ((*s)[i] == ')')
		{
			parsay--;
			if (parsay == 0)
			{
				string paric = s->substr(aPar + 1, i - aPar - 1);
				if (!islemYap(&paric))
					return 0;
				if (stod(paric) < 0)
				{
					paric = '(' + paric + ')';
				}
				else if (paric[0] == '+')
					paric = paric.substr(1);
				*s = strDegis(*s, aPar, i, paric);
				i = aPar + paric.length();
				smik = s->length();
				if (i == smik)
					i--;
			}
		}
	}

	return 1;
}
bool charIslem(char girdi, char onceki)
{
	//charislem
	bool sayi = false;
	bool osayi = false;
	if (charVarMi(girdi, "0123456789ep"))
		sayi = true;
	if (charVarMi(onceki, "0123456789ep"))
		osayi = true;
	if (sayi || charVarMi(girdi, "+-*/^!ksctl%.(),"))
	{
		if (sayi && charVarMi(onceki, "ep!l)"))
			return 0;
		if (girdi == '+'&&charVarMi(onceki, "+-*/^ksctl%."))
			return 0;
		if (girdi == '-'&&charVarMi(onceki, "+-*/^ksctl%."))
			return 0;
		if (girdi == '*'&&charVarMi(onceki, "+-*/^ksctl%.(,"))
			return 0;
		if (girdi == '/'&&charVarMi(onceki, "+-*/^ksctl%.(,"))
			return 0;
		if (girdi == '^'&&charVarMi(onceki, "+-*/^ksctl%.(,"))
			return 0;
		if (girdi == '!' && !osayi && !charVarMi(onceki, ")"))
			return 0;
		if (girdi == 'k' && !osayi && !charVarMi(onceki, "+-*/^ksct()!,"))
			return 0;
		if (girdi == 's' && !charVarMi(onceki, "+-*/(^ksct%,"))
			return 0;
		if (girdi == 'c' && !charVarMi(onceki, "+-*/(^ksct%,"))
			return 0;
		if (girdi == 't' && !charVarMi(onceki, "+-*/(^ksct%,"))
			return 0;
		if (girdi == 'l' && !charVarMi(onceki, "+-*/(^ksct%,"))
			return 0;
		if (girdi == '%' && (osayi || !charVarMi(onceki, "+-*/^ksct%(,")))
			return 0;
		if (girdi == '.' && (!osayi || charVarMi(onceki, "ep,")))
			return 0;
		if (girdi == '(' && (osayi || charVarMi(onceki, "!.)")))
			return 0;
		if (girdi == ')' && !osayi && !charVarMi(onceki, "!)"))
			return 0;
		if (girdi == ',' && !osayi && !charVarMi(onceki, "!)"))
			return 0;
		if (girdi == 'e' && (osayi || !charVarMi(onceki, "+-*/^ksct%(,")))
			return 0;
		if (girdi == 'p' && (osayi || !charVarMi(onceki, "+-*/^ksct%(,")))
			return 0;
	}
	else
		return 0;
	return 1;
}
string strDegis(string s, int ilk, int son, string yeni)
{
	return s.substr(0, ilk) + yeni + s.substr(son + 1);
}
string boslukSil(string s)
{
	int smik = s.length();
	string yeni = "";
	for (int i = 0; i < smik; i++)
	{
		if (s[i] != ' ')
			yeni += s[i];
	}
	return yeni;
}
bool charVarMi(char ch, string kontrol) {
	int konmik = kontrol.length();
	for (int i = 0; i < konmik; i++)
	{
		if (kontrol[i] == ch)
		{
			return 1;
		}
	}
	return 0;
}
bool girdiKontrol(string * girdi)
{
	if (*girdi != "")
	{
		*girdi = boslukSil(*girdi);
		int gmik = girdi->length();
		bool hatali = false;
		for (int i = 1; i < gmik; i++)
		{
			if (!charIslem((*girdi)[i], (*girdi)[i - 1]))
			{
				hatali = true;
				break;
			}
		}
		if (!hatali && !charVarMi((*girdi)[0], "*/^!.)") && !charVarMi((*girdi)[girdi->length() - 1], "+-*/^ksctl%.("))
			return 1;
	}
	return 0;
}
double faktoriyel(double sayi) {
	if (sayi == (int)sayi)
	{
		if (sayi == 2)
			return 2;
		else
			return sayi * faktoriyel(sayi - 1);
	}
	return tgamma(sayi + 1);
}
bool sayiAyarla(string* sayi)
{
	if ((*sayi).find_first_not_of("0123456789.-") != string::npos)
		return 0;
	int smik = sayi->length();
	for (int i = sayi->at(0) == '-' ? 1 : 0; i < smik; i++)
	{
		if (sayi->at(i) == '.')
		{
			if (i == 0 || i == smik - 1)
				return 0;
			for (int j = i + 1; j < smik; j++)
			{
				if (sayi->at(j) == '.')
					return 0;
				if (sayi->at(j) == '-')
					return 0;
			}
			if (i + 9 < smik)
				*sayi = sayi->substr(0, i + 10);
			return 1;
		}
		if (sayi->at(i) == '-')
			return 0;
	}
	return 1;
}