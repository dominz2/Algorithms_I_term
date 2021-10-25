/* For given two-dimensional M x N table shift all its
elements in spiral direction */

#include <iostream>
#include <vector>

using namespace std;


/*
in function "create_table by using vector
template object "table" is created
*/


void create_table(vector<vector<int>> &table)
{
    int m=0, n=0;
    cout << "Enter M i N" <<endl;
    while (m==0 || n==0)
    {
    cin >> m;
    cin >> n;
    if (m==0 || n==0)
        {
            cout<<"Number of rows and columns have to be positive"<<endl;
        }
    }

    vector<vector<int>> table1(m, vector<int>(n));
    table = table1;
}


void fill_table(vector<vector<int>> &table)
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


int main()
{
    vector<vector<int>> table;
    create_table(table);
    fill_table(table);
    print_table(table);
    spiral_spin(table);
    cout<<endl;
    cout<<"Table after spin";
    print_table(table);
    return 0;
}
