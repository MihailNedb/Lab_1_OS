#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../common/employee.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Usage: Reporter <input_file> <output_file> <hourly_rate>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    double hourlyRate = stod(argv[3]);

    ifstream inFile(inputFile, ios::binary);
    if (!inFile)
    {
        cout << "Cannot open input file: " << inputFile << endl;
        return 1;
    }

    ofstream outFile(outputFile);
    if (!outFile)
    {
        cout << "Cannot create output file: " << outputFile << endl;
        return 1;
    }

    outFile << "Report for file " << inputFile << endl;
    outFile << "Employee ID    Employee Name    Hours    Salary" << endl;

    employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(employee)))
    {
        double salary = emp.hours * hourlyRate;
        outFile << emp.num << "               "
            << emp.name << "               "
            << fixed << setprecision(2) << emp.hours << "      "
            << fixed << setprecision(2) << salary << endl;
    }

    inFile.close();
    outFile.close();
    cout << "Report " << outputFile << " created successfully." << endl;

    return 0;
}