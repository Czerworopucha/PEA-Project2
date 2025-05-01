#include <iostream>
#include "Matrix.h"
#include "SimAnnealing.h"
#include "ReadPathFromFile.h"
using namespace std;

int main() {

    auto *matrixPointer = new Matrix();
    int choice;
    int stopTime = 0;
    int cool = 0;

    do {
        cout << endl;
        cout << "==== MAIN MENU ====" << endl;
        cout << "1.Wczytaj dane z pliku" << endl;
        cout << "2.Podaj kryterium zatrzymania" << endl;
        cout << "3.Wybor sasiedztwa dla Tabu Search - BRAK" << endl; // opis ponizej
        cout << "4.Tabu Search - BRAK" << endl; // algorytm nie został zaimplementowany, jednak jego funkcje zostały w menu,
                                                // ponieważ było robione na początku programu według wymagań co do jego zawartości
        cout << "5.Wybor wspolczynnika chlodzenia dla Symulowanego Wyzarzania" << endl;
        cout << "6.Symulowane Wyzarzanie" << endl;
        //cout << "7.Zapis rozwiazania do pliku .txt" << endl; // jednak nie istnieje jako osobna opcja - wykonuje sie sam po zakończeniu algorytmu
        cout << "7.Wczytaj rozwiazanie z pliku" << endl;
        //cout << "8.Testy" << endl; //zakomentowane do normalnego użytkowania programu, dane i wyniki zapisywane są do plików
        cout << "Wybor :" << endl;
        cin >> choice;


        switch (choice) {
            case 1: {
                string filename;
                //Wczytywanie z pliku do dorobienia w klasie Matrix
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                matrixPointer->LoadMatrixFromFile(filename);
                //matrixPointer->DisplayMatrix();
                break;
            }

            case 2: {
                cout << "Wybierz czas po jakim czasie algorytm ma sie zatrzymac [s]: " << endl;
                cout << "1. 120" << endl;
                cout << "2. 240" << endl;
                cout << "3. 360" << endl;
                cin >> stopTime;
                break;
            }

            case 3: {
                cout << "Blad - brak funkcjonalnosci";
                break;
            }

            case 4: {
                cout << "Blad - brak funkcjonalnosci";
                break;
            }

            case 5: {
                cout << "Wybierz wspolczynnik chlodzenia dla algorytmu SW: " << endl;
                cout << "1. 0.999" << endl;
                cout << "2. 0.99935" << endl;
                cout << "3. 0.9995" << endl;
                cout << "4. 0.9994" << endl;
                cin >> cool;
                break;
            }

            case 6: {
                auto SWalgorithm = new SimAnnealing(matrixPointer, stopTime);
                SWalgorithm->coolingChoice(cool);
                SWalgorithm->RunSimAnnealing();
                SWalgorithm->DisplayResults();
                SWalgorithm->saveToFile();
                break;
            }
            /*
            case 7: {
                break;
            }
            */
            case 7: {
                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                auto rff = new ReadPathFromFile(matrixPointer);
                rff->readFromFile(filename);
                rff->calculateDistance();
                rff->display();
                break;
            }
            case 8:{
                /*
                cout << "Running tests for 55" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/ftv55.atsp/ftv55.atsp");

                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm = new SimAnnealing(matrixPointer, 1);
                    SWalgorithm->coolingChoice(1);
                    SWalgorithm->RunSimAnnealing();
                    SWalgorithm->DisplayResults();
                    SWalgorithm->tests();
                }
                for (int i = 0; i < 10; i++) {
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm = new SimAnnealing(matrixPointer, 1);
                    SWalgorithm->coolingChoice(2);
                    SWalgorithm->RunSimAnnealing();
                    SWalgorithm->DisplayResults();
                    SWalgorithm->tests();
                }
                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm = new SimAnnealing(matrixPointer, 1);
                    SWalgorithm->coolingChoice(3);
                    SWalgorithm->RunSimAnnealing();
                    SWalgorithm->DisplayResults();
                    SWalgorithm->tests();
                }
                */
                /*
                cout << "Running tests for 170" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/ftv170.atsp/ftv170.atsp");

                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm2 = new SimAnnealing(matrixPointer, 2);
                    SWalgorithm2->coolingChoice(1);
                    SWalgorithm2->RunSimAnnealing();
                    SWalgorithm2->DisplayResults();
                    SWalgorithm2->tests();
                }


                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm2 = new SimAnnealing(matrixPointer, 2);
                    SWalgorithm2->coolingChoice(2);
                    SWalgorithm2->RunSimAnnealing();
                    SWalgorithm2->DisplayResults();
                    SWalgorithm2->tests();
                }

                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm2 = new SimAnnealing(matrixPointer, 2);
                    SWalgorithm2->coolingChoice(3);
                    SWalgorithm2->RunSimAnnealing();
                    SWalgorithm2->DisplayResults();
                    SWalgorithm2->tests();
                }
                */
                /*
                cout << "Running tests for 358" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/rbg358.atsp/rbg358.atsp");
                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm3 = new SimAnnealing(matrixPointer, 3);
                    SWalgorithm3->coolingChoice(1);
                    SWalgorithm3->RunSimAnnealing();
                    SWalgorithm3->DisplayResults();
                    SWalgorithm3->tests();
                }
                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm3 = new SimAnnealing(matrixPointer, 3);
                    SWalgorithm3->coolingChoice(2);
                    SWalgorithm3->RunSimAnnealing();
                    SWalgorithm3->DisplayResults();
                    SWalgorithm3->tests();
                }
                for (int i = 0; i < 10; i++){
                    cout << "running " << i << "..." << endl;
                    auto SWalgorithm3 = new SimAnnealing(matrixPointer, 3);
                    SWalgorithm3->coolingChoice(3);
                    SWalgorithm3->RunSimAnnealing();
                    SWalgorithm3->DisplayResults();
                    SWalgorithm3->tests();
                }
                */
                break;
            }
        }
    }while(choice != 0);

    return 0;
}
