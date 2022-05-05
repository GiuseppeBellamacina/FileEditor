#include <iostream>
#include <fstream>
#include <limits>
#define YES 'Y'
using namespace std;

// funzione per far finire il programma
bool end(){
	system("pause");
	system("cls");
	char ans;
	cout << "Vuoi fare altro? (Y) (N)\t";
	cin >> ans;
	while (cin.fail()){
		cerr << "Scrivi Y se vuoi fare altro altrimenti N" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vuoi fare altro? (Y) (N)\t";
		cin >> ans;
	}
	if(toupper(ans) == YES)
		return true;
	else return false;
}

// funzione che verifica se il file è vuoto
bool isEmpty(fstream& file){
    if (file.peek() == fstream::traits_type::eof()){
    	file.clear();
    	return 0;
	} return 1;
}

// funzione di lettura
void read(fstream& file){
	short n;
	cout << "Quante righe vuoi leggere?\t";
	cin >> n;
	while (cin.fail() || n<0){
		cerr << "Errore, immetti il numero di righe" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Quante righe vuoi leggere?\t";
		cin >> n;
	}
	string s;
	if(n==0){ // così trascrive tutto ciò che c'è sul file
		while(file.good()){
			getline(file,s);
			if(file.eof()) break;
			if(file.fail()){
				cerr << "Errore durante lettura su file" << endl;
				break;
			}
			if(!file.eof())
				cout << s << endl;
		}
		return;	
	}
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
	string s;
	short a = 0;
	cout << "Scrivi quello che vuoi, inserisci END quando hai finito" << endl;
	while(getline(cin,s)){
		if(s == "END")
			break;
		file << s;
		if(isEmpty(file)){
			file << endl;	
		}
		if(file.fail()){
			cerr << "Errore durante la scrittura su file" << endl;
			break;
		}
	}
}

// funzione per scegliere che fare col file
bool func(fstream& file){
	char s;
	cout << "Vuoi leggere (1) o scrivere (2) sul file? \t";
	cin >> s;
	while (cin.fail() || (s!='1' && s!='2')){
		cerr << "Devi scrivere 1 per leggere da file o 2 per scriverci sopra" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vuoi leggere (1) o scrivere (2) sul file? \t";
		cin >> s;
	}
	if(s == '1') return true;
	else return false;
}

// funzione che crea o seleziona il file nella cartella del .cpp
bool fileSelect(fstream& file){ // occhio alla &
	string name;
	cout << "Inserisci nome file (specificando l'estensione): ";
	cin >> name;
	file.open(name, fstream::out | fstream::app | fstream::in); // se il file non esiste lo crea
	if(!file){ // se non riesce a crearlo allora...
		cerr << "Errore nella creazione del file";
		return 0;
	}
	if(func(file)){
		read(file);
		file.close();
	}
	else{
		write(file);
		file.close();	
	}
	return end();
}

int main(){
	fstream file;
	bool pg = true;
	while(pg){
		pg = fileSelect(file);
	}
	return 0;
}
