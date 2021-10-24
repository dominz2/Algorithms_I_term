/* For given two-dimensional M x N table shift all its
elements in spiral direction */

#include <iostream>
#include <vector>

using namespace std;


/*
in function "create_table by using vector
template object "table" is created
*/
vector<vector<int>> create_table()
{
    int m, n;
    cout << "Enter M i N" <<endl;
    cin >> m;
    cin >> n;
    vector<vector<int>> table(m, vector<int>(n));
    return table;
}

vector<vector<int>> fill_table(vector<vector<int>> table)
{
    int i, j;
    for (j=0; j<table.size(); j++)
    {
        cout<<"enter elements: " << j <<"-th row"<<endl;
        for (i=0; i<table[j].size(); i++)
        {
            cin>>table[j][i];
        }
    }
return table;
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


int main()
{
    vector<vector<int>> table;
    table = create_table();
    table = fill_table(table);
    print_table(table);
    return 0;
}
