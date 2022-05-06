#include <iostream>
#include <fstream>
#include <limits>
#define YES 'Y'
using namespace std;

// funzione per far finire il programma
bool end(){
	cout << endl;
	system("pause");
	system("cls");
	char ans;
	cout << "Vuoi fare altro?" << endl;
	cout << "(Y) Si" << endl;
	cout << "(N) No" << endl;
	cout << "--> ";
	cin >> ans;
	while (cin.fail()){
		cerr << "Scrivi Y se vuoi fare altro altrimenti N" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vuoi fare altro?" << endl;
		cout << "(Y) Si" << endl;
		cout << "(N) No" << endl;
		cout << "--> ";
		cin >> ans;
	}
	system("cls");
	if(toupper(ans) == YES)
		return true; // così il programma riparte
	else return false; // così il programma si ferma
}

// funzione per sovrascrivere un secondo file
void fileTransfer(fstream& fileA){
	fstream fileB;
	string s;
	cout << "Inserisci nome programma di destinazione: " << endl;
	cout << "--> ";
	cin >> s;
	fileB.open(s, fstream::out | fstream::trunc); // trunc serve a cancellare le eventuali robe già nel file e sovrascriverle
	if(!fileB){
		cerr << "Errore nella creazione del file" << endl;
		return;
	}
	while(fileA.good()){
		getline(fileA,s);
		fileB << s << endl;
		if(fileB.fail()){
			cerr << "Errore durante la scrittura su file" << endl;
			break;
		}
	}
	fileB.close();
	cout << "Operazione completata" << endl;
}

// funzione di lettura
void read(fstream& file){
	short n;
	cout << endl << "Quante righe vuoi leggere? (scrivi 0 per stampare tutto il file)" << endl;
	cout << "--> ";
	cin >> n;
	while (cin.fail() || n<0){
		cerr << "Errore, immetti il numero di righe" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Quante righe vuoi leggere? (scrivi 0 per stampare tutto il file)" << endl;
		cout << "--> ";
		cin >> n;
	}
	cout << endl << "CONTENUTO FILE:" << endl << endl;
	string s;
	if(n==0){ // così trascrive tutto ciò che c'è sul file
		while(file.good()){
			getline(file,s);
			if(file.eof()) break;
			if(file.fail()){
				cerr << "Errore durante lettura su file" << endl;
				break;
			}
			if(!file.eof()) // va avanti fino all'EOF, a quel punto non stampa nient'altro
				cout << s << endl;
		}
		return;	
	}
	// questo serve a leggere solo le prime n righe del file
	for(int i=0; i<n && file.good(); i++){
		getline(file,s);
		if(file.eof()) break;
		if(file.fail()){
				cerr << "Errore durante lettura su file" << endl;
				break;
		}
		if(!file.eof())
			cout << s << endl;
	}
}

// funzione di scrittura
void write(fstream& file){
	string s = "";
	bool init = true;
	cout << endl << "Scrivi quello che vuoi, inserisci END quando hai finito" << endl;
	while(getline(cin,s)){
		if(s == "END")
			break;
		cout << "--> ";
		if(init){ // sta roba serve a non fargli mettere degli endl a caso all'inizio
			file << s;
			init = false;
		}
		else file << s << endl;
		if(file.fail()){
			cerr << "Errore durante la scrittura su file" << endl;
			break;
		}
	}
}

// funzione per scegliere che fare col file
void func(fstream& file){
	int s;
	cout << endl << "Cosa vuoi fare?" << endl;
	cout << "(1) Leggere da file" << endl;
	cout << "(2) Scrivere su file" << endl;
	cout << "(3) Sovrascrive il contenuto del file su un altro file" << endl;
	cout << "--> ";
	cin >> s;
	while (cin.fail() || (s!=1 && s!=2 && s!=3)){
		cerr << "Devi scrivere 1, 2 o 3 per selezionare la funzione" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Cosa vuoi fare?" << endl;
		cout << "(1) Leggere da file" << endl;
		cout << "(2) Scrivere su file" << endl;
		cout << "(3) Sovrascrive il contenuto del file su un altro file" << endl;
		cout << "--> ";
		cin >> s;
	}
	switch(s){
		case 1: read(file); break;
		case 2: write(file); break;
		case 3: fileTransfer(file);
	}
}

// funzione che crea o seleziona il file nella cartella del .cpp
bool fileSelect(fstream& file){ // occhio alla &
	string name;
	cout << "Inserisci nome file (specificando l'estensione): " << endl;
	cout << "--> ";
	cin >> name;
	file.open(name, fstream::out | fstream::app | fstream::in); // se il file non esiste lo crea
	if(!file){ // se non riesce a crearlo allora...
		cerr << "Errore nella creazione del file" << endl;
		return 0;
	}
	func(file);
	file.close();
	return end();
}

int main(){
	fstream file;
	bool pg = true;
	while(pg){ // il programma riparte eventualmente fino a quando pg è false
		pg = fileSelect(file);
	}
	return 0;
}
