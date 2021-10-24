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



int main()
{
    vector<vector<int>> table;
    table = create_table();
    cout<<table[0][0]<<endl;
    return 0;
}
