#include <iostream>
#include <fstream>                  // Datei lesen/schreiben einbinden
#include "CBild.h"
#include "NBild.h"
#include <random>                   // Zufallszahlen

using namespace std;

const int Breite2 = 303;               // Hilfsmatrix zum Kodieren in das CBild-Format
const int Hoehe2 = 89;
int Matrix2[Breite2][Hoehe2];

const int Neu_Breite = 606;             // Matrizen mit doppelter Breite und Hoehe
const int Neu_Hoehe = 178;
int Neu_Matrix[Neu_Breite][Neu_Hoehe];
int KeyMatrix[Breite2][Hoehe2];



// Methoden


void CBild::Kodieren() {                            // Kodiert die Ausgangsdatei in eine Matrix aus den Bloecken A und B

    // Einlesen der Textdatei, die kodiert werden soll
    cout << "Hinweis: Eine Datei Namens 'beispielbild_1.txt' wird importiert. Sie muss im build-Ordner sein." << endl;
    std::string dateiname = "beispielbild_1.txt";
    std::ifstream quelle(dateiname);

        int Matrix2[Breite2][Hoehe2];
        if (!quelle) {
            std::cerr << "Error!" << std::endl;
        }
        else {

            h=0;
            while (quelle) {
                string line;
                getline(quelle, line);

                for (int n=0; n<Breite2; n++) {
                    char TempChar = line[n];
                    int TempInt = (int)TempChar;
                    TempInt -= 48;
                    Matrix2[n][h] = TempInt;
                }
                h++;
                for (int x = 0; x < Breite2; x++) {          // Reparieren der 0.Zeile, die aus unerklaerlichen Gruenden
                    if (Matrix2[x][0] != 1) {                // seltsame Werte ueber getline erhaelt
                        Matrix2[x][0] = 1;
                    }
                }
            }
        }


        // Kodieren in Bloecke A und B
        for (int y = 0; y < Hoehe2; y++) {              // Bloecke A und B generieren
            for (int x = 0; x < Breite2; x++){
                if (Matrix2[x][y] == 0) {
                    Neu_Matrix[2*x][2*y] = 1;
                    Neu_Matrix[2*x+1][2*y] = 0;
                    Neu_Matrix[2*x][2*y+1] = 0;
                    Neu_Matrix[2*x+1][2*y+1] = 1;
                }
                else if (Matrix2[x][y] == 1) {
                    Neu_Matrix[2*x][2*y] = 0;
                    Neu_Matrix[2*x+1][2*y] = 1;
                    Neu_Matrix[2*x][2*y+1] = 1;
                    Neu_Matrix[2*x+1][2*y+1] = 0;
                }
                else {
                    cout << "Fehler" << endl;
                }
            }
            }


        // Moeglichkeit der Speicherung als .txt oder .ppm

        cout << "Soll die Kodierung als .txt gespeichert werden? Bitte mit (J)a oder (N)ein antworten" << endl;
        string Antwort;
        cin >> Antwort;
        cout << endl;

        int counter = 0;
        int Zeichenanzahl = Neu_Hoehe * Neu_Breite;
        int Zahlenliste[Zeichenanzahl];
        for (int y = 0; y < Neu_Hoehe; y++) {
            for (int x = 0; x < Neu_Breite; x++) {
            Zahlenliste[counter] = Neu_Matrix[x][y];
            counter++;
            }
        }

        if (Antwort == "J") {

            ofstream Output ("blocktext1.txt");                     // Erstellung der .txt
            int Nummer = 0;
            for (int y = 0; y < Neu_Hoehe; y++) {
                if (y != 0) {
                    Output << endl;
                }
                for (int x = 0; x < Neu_Breite; x++) {
                  Output << Zahlenliste[Nummer];
                  Nummer++;
                }
            }
            Output.close();
        }

        else if (Antwort == "N") {
            cout << endl << "Dann wird jetzt eine Bilddatei im .ppm-Format erstellt" << endl;

        ofstream img ("blockdatei1.ppm");                           // Erstellung der .ppm
        img << "P3" << endl;
        img << Neu_Breite << " " << Neu_Hoehe << endl;              // Breite und Hoehe definieren
        img << "255" << endl;                                       // Anzahl der Farbanteile definieren

        for (int y = 0; y < Neu_Hoehe; y++) {
            for (int x = 0; x < Neu_Breite; x++){

                if (Neu_Matrix[x][y] == 1) {
                        int r = 255;
                        int g = 255;
                        int b = 255;
                        img << r << " " << g << " " << b << endl;
                }
                else if (Neu_Matrix[x][y] == 0) {
                        int r = 0;
                        int g = 0;
                        int b = 0;
                        img << r << " " << g << " " << b << endl;
                }
                else {
                    int r = 255;
                    int g = 255;
                    int b = 255;
                    img << r << " " << g << " " << b << endl;
                }
            }
        }
        cout << endl << "Bild wurde erstellt!" << endl;
        }

        else {
            cout << "Das war leider keine gueltige Eingabe. Nichts wird passieren.";
        }
}



void CBild::Verschluesseln() {                                      // aus beispieltext_1.txt und key.txt wird eine
                                                                    // verschluesselte Datei erstellt (mit doppelter Laenge und doppelter Breite)

    //Regeln für beispieltext_1.txt MAL randombild_1.txt
    // 0 MAL 0 = 1
    // 0 MAL 1 = 0
    // 1 MAL 0 = 0
    // 1 MAL 1 = 1
    // bedenke: 0 ist schwarz, 1 ist weiß


    // Einlesen des zu verschluesselndes Bildes in Array 'Matrix2'
    std::string dateiname = "beispielbild_1.txt";
    std::ifstream quelle(dateiname);


        int Matrix2[Breite2][Hoehe2];
        if (!quelle) {
            std::cerr << "Error!" << std::endl;
        }
        else {

            h=0;
            while (quelle) {
                string line;
                getline(quelle, line);

                for (int n = 0; n < Breite2; n++) {
                    char TempChar = line[n];
                    int TempInt = (int)TempChar;
                    TempInt -= 48;
                    Matrix2[n][h] = TempInt;
                }
                h++;
                for (int x = 0; x < Breite2; x++) {          // Reparieren der 0.Zeile, die aus unerklaerlichen Gruenden
                    if (Matrix2[x][0] != 1) {                // seltsame Werte ueber getline erhaelt
                        Matrix2[x][0] = 1;
                    }
                }
            }
        }

        cout << "Urbild wurde erstellt!" << endl;


        // Erstellung Schluessel (Random-Bild)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

            int KeyMatrix[Breite2][Hoehe2];                     // Zuerst erzeugen eines Arrays (KeyMatrix)

                    for (int n = 0; n < Hoehe2; n++) {
                        for (int h = 0; h < Breite2; h++) {
                        KeyMatrix[h][n] = dis(gen);
                        cout << KeyMatrix[h][n];
                    }
                }

                    // Speicherung des Schluessels als .txt
                    int counter = 0;
                    int Zeichenanzahl = Hoehe2 * Breite2;
                    int Zahlenliste[Zeichenanzahl];
                    for (int y = 0; y < Hoehe2; y++) {
                        for (int x = 0; x < Breite2; x++) {
                        Zahlenliste[counter] = KeyMatrix[x][y];
                        counter++;

                        ofstream Output ("key_1.txt");                  // HINWEIS: Ab hier kann man auskommentieren, damit es schneller geht...
                        int Nummer = 0;
                        for (int y = 0; y < Hoehe2; y++) {
                            if (y != 0) {
                                Output << endl;
                            }
                            for (int x = 0; x < Breite2; x++) {
                                Output << Zahlenliste[Nummer];
                                Nummer++;
                            }
                        }                                               // ...bis hierher
                        }
                    }

                        cout << endl << "Schluessel wurde erstellt!" << endl;


            // Verschluesselungsalgorithmus

            for (int y = 0; y < Hoehe2; y++) {                  // Verschluesselung durch "Multiplikation"; Ergebnis ist ein Objekt von NBild
                for (int x = 0; x < Breite2; x++){              // (doppelt so großes Bild)
                    if (Matrix2[x][y] == KeyMatrix[x][y]) {
                        Neu_Matrix[2*x][2*y] = 0;
                        Neu_Matrix[2*x+1][2*y] = 1;
                        Neu_Matrix[2*x][2*y+1] = 1;
                        Neu_Matrix[2*x+1][2*y+1] = 0;
                    }
                    else if (Matrix2[x][y] != KeyMatrix[x][y]) {
                        Neu_Matrix[2*x][2*y] = 1;
                        Neu_Matrix[2*x+1][2*y] = 0;
                        Neu_Matrix[2*x][2*y+1] = 0;
                        Neu_Matrix[2*x+1][2*y+1] = 1;
                    }
                }
                }


            // Speicherung der verschluesselten Datei als .txt
            int counter2 = 0;
            int Zeichenanzahl2 = Neu_Hoehe * Neu_Breite;
            int Zahlenliste2[Zeichenanzahl2];
            for (int y = 0; y < Neu_Hoehe; y++) {
                for (int x = 0; x < Neu_Breite; x++) {
                Zahlenliste2[counter2] = Neu_Matrix[x][y];
                counter2++;

                ofstream Output ("secret_1.txt");
                int Nummer = 0;
                for (int y = 0; y < Neu_Hoehe; y++) {
                    if (y != 0) {
                        Output << endl;
                    }
                    for (int x = 0; x < Neu_Breite; x++) {
                        Output << Zahlenliste2[Nummer];
                        Nummer++;
                    }
                }
                }

            cout << endl << endl << "Datei wurde verschluesselt" << endl << endl;
}
}



void CBild::Entschluesseln() {                          // aus der verschluesselten Datei und dem Key wird wieder
                                                        // die Ausgangsdatei, so dass das Wort wieder lesbar sein sollte


    // Importieren von Schluessel und verschluesselter Datei ('secret_1.txt')

    cout << endl << endl << "Es werden jetzt der Schluessel unter dem Namen 'key_1.txt' und die ";
    cout << "verschluesselte Datei unter dem Namen 'secret_1.txt' eingelesen. Bitte achten Sie auf genau diese Benennung!";


    std::string dateiname = "key_1.txt";
    std::ifstream quelle(dateiname);
        int KeyMatrix[Breite2][Hoehe2];
        if (!quelle) {
            std::cerr << "Error!" << std::endl;
        }
        else {

            h=0;
            while (quelle) {
                string line;
                getline(quelle, line);

                for (int n=0; n<Breite2; n++) {
                    char TempChar = line[n];
                    int TempInt = (int)TempChar;
                    TempInt -= 48;
                    KeyMatrix[n][h] = TempInt;
                }
                h++;
            }
            }
        cout << endl << "Key erfolgreich eingelesen!" << endl << endl;

        std::string dateiname2 = "secret_1.txt";
        std::ifstream quelle2(dateiname2);
            int Neu_Matrix[Neu_Breite][Neu_Hoehe];
            if (!quelle2) {
                std::cerr << "Error!" << std::endl;
            }
            else {

                h=0;
                while (quelle2) {
                    string line;
                    getline(quelle2, line);

                    for (int n=0; n<Neu_Breite; n++) {
                        char TempChar = line[n];
                        int TempInt = (int)TempChar;
                        TempInt -= 48;
                        Neu_Matrix[n][h] = TempInt;
                    }
                    h++;
                }
                }
        cout << endl << endl << "Beide Dateien wurden eingelesen." << endl;


    // Entschluesselungsalgorithmus
    int Matrix2[303][89];
    for (int y = 0; y < Hoehe2; y++) {
        for (int x = 0; x < Breite2; x++){
            if      (KeyMatrix[x][y] == 0 && Neu_Matrix[2*x][2*y] == 0 && Neu_Matrix[2*x+1][2*y] == 1 && Neu_Matrix[2*x][2*y+1] == 1 && Neu_Matrix[2*x+1][2*y+1] == 0) {
                Matrix2[x][y] = 0;
            }
            else if (KeyMatrix[x][y] == 1 && Neu_Matrix[2*x][2*y] == 1 && Neu_Matrix[2*x+1][2*y] == 0 && Neu_Matrix[2*x][2*y+1] == 0 && Neu_Matrix[2*x+1][2*y+1] == 1) {
                Matrix2[x][y] = 0;
            }
            else if (KeyMatrix[x][y] == 0 && Neu_Matrix[2*x][2*y] == 1 && Neu_Matrix[2*x+1][2*y] == 0 && Neu_Matrix[2*x][2*y+1] == 0 && Neu_Matrix[2*x+1][2*y+1] == 1) {
                Matrix2[x][y] = 1;
            }
            else if (KeyMatrix[x][y] == 1 && Neu_Matrix[2*x][2*y] == 0 && Neu_Matrix[2*x+1][2*y] == 1 && Neu_Matrix[2*x][2*y+1] == 1 && Neu_Matrix[2*x+1][2*y+1] == 0) {
                Matrix2[x][y] = 1;
            }
        }
        }

    // Speicherung der entschluesselten Datei als .txt
    int counter3 = 0;
    int Zeichenanzahl3 = Hoehe2 * Breite2;
    int Zahlenliste3[Zeichenanzahl3];
    for (int y = 0; y < Hoehe2; y++) {
        for (int x = 0; x < Breite2; x++) {
        Zahlenliste3[counter3] = Matrix2[x][y];
        counter3++;

        ofstream Output ("secret_revealed.txt");
        int Nummer = 0;
        for (int y = 0; y < Hoehe2; y++) {
            if (y != 0) {
                Output << endl;
            }
            for (int x = 0; x < Breite2; x++) {
                Output << Zahlenliste3[Nummer];
                Nummer++;
            }
        }
        }
    }
    cout << endl << endl << "Datei wurde entschluesselt und man sollte wieder das Wort lesen koennen." << endl << endl;
    system("secret_revealed.txt");

}

