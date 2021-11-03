#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>


using namespace std;
using namespace std::chrono;


// Funkcja zwracająca tabelę utworzoną przy  pomocy szablonu klasy
// Użytkownik wprowadza rozmiar tablicy z klawiatury


vector<vector<int>> create_table()
{
    int m = 0, n = 0;
    cout << "Enter M i N" << endl;
    while (true)
    {
        cin >> m;
        cin >> n;
        if (m > 0 && n > 0)
            break;

        cout << "Number of rows and columns have to be positive" << endl;
    }

    vector<vector<int>> table(m, vector<int>(n));
    return table;
}

// Funkcja wczytująca tablice z pliku txt i zwracająca ją jako obiekt klasy vector

vector<vector<int>> read_table_from_txt()
{
    string table_txt = "table.txt";
    ifstream in(table_txt);
    string line;

    // Funkcja liczy liczbę wierszy, a następnie wskaźnik ustawiany jest ponownie na początek pliku

    int line_count = 0;
    while (getline(in, line))
        line_count++;

    in.clear();
    in.seekg(0);

    // Przy tworzeniu obiektu, którym jest nasza tablica musimy zadeklarować jej wymiary
    // Liczbę wierszy przekazuje zmienna line_count. Liczbę kolumn deklarujemy początkowo jako 0

    vector<vector<int>> table(line_count, vector<int>(0));
    int buffor;
    int i = 0;

    while (getline(in, line))
    {
        // Linie pliku są odczytywane jako stringi
        // Tworzymy strumień, który będzie mógł przekazać te linie do zmiennej typu int
        // Następnie korzystamy z metody klasy vector i dopisujujemy, do każdego wiersza tablicy linię z pliku txt

        stringstream ss(line);
        while(ss >> buffor)
            table[i].push_back(buffor);

        i++;
    }
    return table;
}

// Funkcja do wypełniania tablicy przez użytkownika albo losowo
// Funkcja działa bezpośrednio na obiekcie tablica,
// ponieważ przekazany został do niej jej adres pamięci

void fill_table(vector<vector<int>> &table)
{
    int i, j;
    cout << "Do you prefer to fill table manually or randomly?" << endl;
    cout << "Press 1 for manual option or 2 for automatic option" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        {
        for (j=0; j < table.size(); j++)
            {
                cout <<"enter elements: " << j <<"-th row"<< endl;
                for (i = 0; i < table[j].size(); i++)
                {
                    cin >> table[j][i];
                }
            }
        break;

    case 2:
        {
        srand((unsigned) time(0));
        for (j = 0; j < table.size(); j++)
        {
            for (i = 0; i < table[j].size(); i++)
            {
            table[j][i] = rand();
            }
        }
        break;
        }
    }
}

// Funkcja dająca możliwość wyboru inicjalizacji tablicy

void initialize_table(vector<vector<int>> &table)
{
    cout << "Do you want to create table or read it from a txt file?" << endl;
    cout << "Press 1 for create or 2 for read" << endl;
    int choice;
    cin >> choice;
    switch(choice)
    {
    case 1:
        table = create_table();
        fill_table(table);
        break;

    case 2:
        table = read_table_from_txt();
        break;
    }
}


// Funkcja do wypisywania elementów tablicy

void print_table(vector<vector<int>> table)
{
    int i, j;
    for (j =0 ; j < table.size(); j++)
    {   cout << endl;
        for (i = 0; i < table[j].size(); i++)
        {
            cout << table[j][i];
            cout << " ";
        }
    }
}

// Funkcja wykonująca spiralny obrót elementami tablicy o jeden indeks w kierunku ruchu zegara
// Środkowy element staje się pierwszym

void spiral_spin(vector<vector<int>> &table)
{
    // Zmienne przechowujące skrajne indeksy elementów tablicy
    int top = 0, bottom = table.size() - 1;
    int left = 0, right = table[0].size() - 1;

    // zmienna przechowująca zamieniany element tablicy
    int prev = table[0][0];

    while (true)
    {

        // Przestawienie elementów górnego wiersza
        for (int i = left; i <= right; i++) {
            swap(table[top][i], prev);
        }
        // Nie będziemy zajmować się już górnym wierszem dlatego zwiększamy indeks zmiennej top o 1
        // Idziemy w dół tablicy
        top++;

        // Jeżeli zmiany zachodziły w ostatnim niezmienionym wierszu przerywamy działanie funkcji
        if (top > bottom) {
            break;
        }

        // Zamiana elementów prawej kolumny
        for (int i = top; i <= bottom; i++) {
            swap(table[i][right], prev);
        }

        right--;

        if (left > right) {
            break;
        }

        // Zamiana elementów dolnego wiersza
        for (int i = right; i >= left; i--) {
            swap(table[bottom][i], prev);
        }

        bottom--;

        if (top > bottom) {
            break;
        }

        // Zamiana elementów lewej kolumny
        for (int i = bottom; i >= top; i--) {
            swap(table[i][left], prev);
        }

        left++;
    }

    // Pierwszym elementem tablicy będzie ostatni zamieniony element
    table[0][0] = prev;
}

//Funkcja zapisująca do pliku txt utworzoną tablicę

void save_table_to_txt (vector<vector<int>> &table)
{
    int i, j;
    ofstream table_txt;
    table_txt.open("table.txt");
    for (j = 0; j < table.size(); j++)
    {

        for(i = 0; i < table[0].size(); i++)
        {
            table_txt << table[j][i] << " ";
        }
    table_txt << endl;
    }
    table_txt.close();
}

// Funkcja przeprowadzająca testy czasu działania funkcji "spiral_spin" dla różnych wymiarów tablicy

void tests (int tests_number)
{
    ofstream test_results_txt;
    test_results_txt.open("test_results_txt.txt");
    srand((unsigned) time(0));

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    duration<double> time;

    int i, j, k;
    int m = 20;
    int n = 20;
    for (k = 0; k < tests_number; k++)
    {
        vector<vector<int>> table(m, vector<int>(n));

            for (j = 0; j < table.size(); j++)
            {
                for (i = 0; i < table[j].size(); i++)
                {
                table[j][i] = rand();
                }
            }
        start = high_resolution_clock::now();
        spiral_spin(table);
        stop = high_resolution_clock::now();
        time = stop - start;


        // Zapisywanie wyników do pliku txt
        test_results_txt << "Execute time        " << setw(15) << time.count();
        test_results_txt << "     Number of elements      " << m * n << endl;

        //dwukrotne zwiększanie liczby wierszy
        m *=2;
    }
    test_results_txt.close();
}


int main()
{
    //tests(19);
    vector<vector<int>> table;
    initialize_table(table);
    print_table(table);
    spiral_spin(table);
    cout << endl;
    cout << "Table after spin" << endl;
    print_table(table);
    //save_table_to_txt(table);
    return 0;
}
