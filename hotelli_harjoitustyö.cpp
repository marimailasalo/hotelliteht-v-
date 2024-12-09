//Mari Mailasalo
//hotelli lopputyö

#include <iostream>
#include <cstdlib> //satunnailukugeneraattori
#include <ctime>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct varaus
{
	int huone;
	int varausnumero;
	string varaajanNimi;
};

//tarkistaa funktion syötteen
int validNumero(const string& prompt)
{
	int numero;
	while (true)
	{
		cout << prompt;
		cin >> numero;
		if (cin.fail() || numero <= 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Virheellinen syöte, tarvitaan kokonaisluku. \n";
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return numero;
		}
	}
}

// tarkistaa huoneen varaustilanteen
bool tarkistaHuone(int huone, const vector<varaus>& varaukset)
{
	for (const auto& varaus : varaukset)
	{
		if (varaus.huone == huone)
		{
			return false; //huone on varattu 
		}
	}
	return true; // huone vapaa
}

// varausnumeron luomisen funktio
int teeVarausnro()
{
	return rand() % 90000 + 10000;
}

//varauksen hakeminen varausnumerolla
void haeVarauksianro(int varausnumero, const vector<varaus>& varaukset)
{
	for (const auto& varaus : varaukset)
	{
		if (varaus.varausnumero == varausnumero)
		{
			cout << "Varaus löytyi: Varaajan nimi: " << varaus.varaajanNimi << ", Huone on: " << varaus.huone << endl;
			return;
		}
	}
	cout << "Ei varausta tällä varausnumerolla. \n";
}

//varauksen haku nimellä
void haeVarauksianimi(const string& nimi, const vector <varaus>& varaukset)
{
	for (const auto& varaus : varaukset)
	{
		if (varaus.varaajanNimi == nimi)
		{
			cout << "Varaus löytyi: Varausnumeor: " << varaus.varausnumero << ", Huone on :" << varaus.huone << endl;
			return;
		}
	}
	cout << "Ei varausta tällä nimellä. \n";
}

int main()
{
	srand(time(0)); // satunnaislukueneraattori
	
	//arpoo huoneiden määrän
	int realhuonemaara = rand() % 41 + 30;

	// arvotaan hinta
	int realhuonehinta = rand() % 21 + 80;

	vector <int> huoneet(realhuonemaara); //lista huoneista
	vector<varaus> varaukset; //lista varauksista

	for (int i = 0; i < realhuonemaara; ++i)
	{
		huoneet[i] = i + 1;
	}

	string varaajanNimi; 
	int valinta;

	while (true)
	{
		cout << "1. Tee uusi varaus\n 2. Hae varausnumerolla\n 3: Hae nimella\n 4. lopeta\n valinta: ";
		valinta = validNumero("");

		if (valinta == 1)
		{
			int yot = validNumero("Montako yota haluat varata: ");
			int huone;
			bool vapaaHuone = false;

			//arvotaan vapaahuone
			while (!vapaaHuone)
			{
				huone = rand() % realhuonemaara + 1;
				if (tarkistaHuone(huone, varaukset))
				{
					vapaaHuone = true;
				}
			}

			cout << "Arvottu vappaa huone: " << huone << endl;

			cout << "Syoya varaajan nimi: ";
			getline(cin, varaajanNimi);

			int varausnumero = teeVarausnro();
			varaukset.push_back({ huone, varausnumero, varaajanNimi });

			int realhinta = yot * realhuonehinta;
			cout << "Varattu huone nro: " << huone << endl;
			cout << "Varausnumero: " << varausnumero << endl;
			cout << "Hinta yolta: " << realhuonehinta << "euroa\n";
			cout << "Kokonaishinta " << yot << " yosta: " << realhinta << " euroa\n";

		}

		else if (valinta == 2)
		{
			// haetaan varausnumerolla
			int varausnumero = validNumero("Anna varausumero: ");
			haeVarauksianro(varausnumero, varaukset);
		}
		
		else if (valinta == 3)
		{
			// haetaan nimellä
			cout << "Anna varaajan nimi: ";
			getline(cin, varaajanNimi);
			haeVarauksianimi(varaajanNimi, varaukset);
		}

		else if (valinta == 4)
		{
			// ohjelma lopetus
			cout << "Ohjelma sulkeutuu. \n";
			break;
		}
		else
		{
			cout << "Vriheellinen valinta. \n";
		}

	}

	return 0;
		
}