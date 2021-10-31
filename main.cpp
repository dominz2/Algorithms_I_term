/* For given two-dimensional M x N table shift all its
elements in spiral direction */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono;



/*
in function "create_table by using vector
template object "table" is created
*/

vector<vector<int>> create_table()
{
    int m=0, n=0;
    cout << "Enter M i N" <<endl;
    while (true)
    {
    cin >> m;
    cin >> n;
    if (m > 0 && n > 0)
        break;
    cout<<"Number of rows and columns have to be positive"<<endl;
    }
    vector<vector<int>> table(m, vector<int>(n));
    return table;
}

vector<vector<int>> read_table_from_txt()
{   string table_txt = "table.txt";
    ifstream in (table_txt);
    string line;

    int line_count = 0;
    while(getline(in, line))
        line_count++;

    in.clear();
    in.seekg(0);

    vector<vector<int>> table(line_count, vector<int>(0));
    int buffor;
    int i = 0;

    while(getline(in, line))
    {
        stringstream ss(line);

            while(ss >> buffor)
            table[i].push_back(buffor);
        i++;
    }
    return table;

}

void fill_table(vector<vector<int>> &table)
{
    int i, j;
    cout << "Do you prefer to fill table manually or randomly?" <<endl;
    cout << "Press 1 for manual option or 2 for automatic option" <<endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
            {
            for (j=0; j<table.size(); j++)
            {
                cout<<"enter elements: " << j <<"-th row"<<endl;
                for (i=0; i<table[j].size(); i++)
                {
                    cin>>table[j][i];
                }
            }
            break;
            }


        case 2:
            {
            srand((unsigned) time(0));
            for (j=0; j<table.size(); j++)
            {
                for (i=0; i<table[j].size(); i++)
                {
                table[j][i] = rand();
                }
            }
            break;
            }


    }


}

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







void print_table(vector<vector<int>> table)
{
    int i, j;
    for (j=0; j<table.size(); j++)
    {   cout<<endl;
        for (i=0; i<table[j].size(); i++)
        {
            cout<<table[j][i];
            cout<<" ";
        }
    }
}


void spiral_spin(vector<vector<int>> &table)
{
    int top = 0, bottom = table.size() - 1;
    int left = 0, right = table[0].size() - 1;
    int prev = table[0][0];

    while (true)
    {

        // change top row
        for (int i = left; i <= right; i++) {
            swap(table[top][i], prev);
        }

        top++;

        if (top > bottom) {
            break;
        }

        // change right column
        for (int i = top; i <= bottom; i++) {
            swap(table[i][right], prev);
        }

        right--;

        if (left > right) {
            break;
        }

        // change bottom row
        for (int i = right; i >= left; i--) {
            swap(table[bottom][i], prev);
        }

        bottom--;

        if (top > bottom) {
            break;
        }

        // change left column
        for (int i = bottom; i >= top; i--) {
            swap(table[i][left], prev);
        }

        left++;
    }

    // the first element of the matrix will be the last element replaced
    table[0][0] = prev;
}

//chcemy, ¿eby mo¿na by³o równie¿ wczytywaæ zapisany ju¿ txt do vector<vector<int>>

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

void tests (int tests_number)
{
    srand((unsigned) time(0));

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    duration<double> time;


    int i, j, k;
    int m=20;
    for (k=0; k<tests_number; k++)
    {
        vector<vector<int>> table(m, vector<int>(20));

            for (j=0; j<table.size(); j++)
            {
                for (i=0; i<table[j].size(); i++)
                {
                table[j][i] = rand();
                }
            }
        start = high_resolution_clock::now();
        spiral_spin(table);
        stop = high_resolution_clock::now();
        time = stop - start;
        cout<< setw(15) << time.count() << endl;


        m*=2;
    }
}


int main()
{
    tests(30);
    //vector<vector<int>> table;
    //initialize_table(table);
    //print_table(table);





    //spiral_spin(table);



    //cout<<endl;
    //cout<<"Table after spin";
    //print_table(table);
    //save_table_to_txt(table);



    return 0;
}
