#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrCalories;
    ifstream MyReadFile("input.txt");

    int HighestCalories = 0;
    int CurrentCalories = 0;

    while (MyReadFile.peek() != EOF)
    {
        getline(MyReadFile, StrCalories);

        // If line is not empty, it has number
        // Parse and add to CurrentCalories
        if (!StrCalories.empty())
        {
            int Calories = stoi(StrCalories);

            CurrentCalories += Calories;
        }

        // If line is empty or file has ended, then all calories of current elf have been added
        if (StrCalories.empty() || MyReadFile.peek() == EOF)
        {
            // Check if new max calories value was reached
            if (HighestCalories < CurrentCalories)
            {
                HighestCalories = CurrentCalories;
            }

            CurrentCalories = 0;
        }
    }

    MyReadFile.close();

    cout << HighestCalories << endl;
}