#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrSections;
    ifstream MyReadFile("input.txt");

    int NumContainedSections = 0;

    while (getline(MyReadFile, StrSections))
    {
        int SeparatorIndex = StrSections.find(',');

        string FirstElf = StrSections.substr(0, SeparatorIndex);
        string SecondElf = StrSections.substr(SeparatorIndex + 1);

        // Get first and last sections of first elf
        int SectionSeparatorIndex = FirstElf.find('-');
        int FirstSectionFE = stoi(FirstElf.substr(0, SectionSeparatorIndex));
        int LastSectionFE = stoi(FirstElf.substr(SectionSeparatorIndex + 1));

        // Get first and last sections of second elf
        SectionSeparatorIndex = SecondElf.find('-');
        int FirstSectionSE = stoi(SecondElf.substr(0, SectionSeparatorIndex));
        int LastSectionSE = stoi(SecondElf.substr(SectionSeparatorIndex + 1));

        // Check if first section of first elf is between first and last of second elf
        // or if first section of the second elf is between first and last of first elf
        if(FirstSectionFE >= FirstSectionSE && FirstSectionFE <= LastSectionSE
            || FirstSectionSE >= FirstSectionFE && FirstSectionSE <= LastSectionFE)
        {
            ++NumContainedSections;
        }
    }

    MyReadFile.close();

    cout << NumContainedSections << endl;
}