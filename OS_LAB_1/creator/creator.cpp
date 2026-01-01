#include <iostream>
#include <fstream>
#include <string>
#include "../common/employee.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: Creator <filename> <record_count>" << endl;
        return 1;
    }

    string filename = argv[1];
    int recordCount = stoi(argv[2]);

    ofstream outFile(filename, ios::binary);
    if (!outFile)
    {
        cout << "Cannot create file: " << filename << endl;
        return 1;
    }

    cout << "Enter " << recordCount << " employee records:" << endl;

    for (int i = 0; i < recordCount; ++i)
    {
        employee emp;

        cout << "Record " << (i + 1) << ":" << endl;
        cout << "  Number: ";
        cin >> emp.num;
        cout << "  Name: ";
        cin >> emp.name;
        cout << "  Hours: ";
        cin >> emp.hours;

        outFile.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    outFile.close();
    cout << "File " << filename << " created successfully with " << recordCount << " records." << endl;

    return 0;
}