#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrCalories;
    ifstream MyReadFile("input.txt");

    // Array will hold the three highest calorie counts
    int HighestCalories[3] = {0, 0, 0};
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
            // Array is always sorted from highest to lowest
            // So if new value is higher than the last, it should replace it
            if (HighestCalories[2] < CurrentCalories)
            {
                HighestCalories[2] = CurrentCalories;

                // Sort array
                for (int i = 0; i < 3; ++i)
                {
                    for (int j = i + 1; j < 3; ++j)
                    {
                        if (HighestCalories[j] > HighestCalories[i])
                        {
                            int TempCalories = HighestCalories[j];
                            HighestCalories[j] = HighestCalories[i];
                            HighestCalories[i] = TempCalories;
                        }
                    }
                }
            }

            CurrentCalories = 0;
        }
    }

    MyReadFile.close();

    int TotalCalories = 0;

    // Sum the total of the three highest
    for (int i = 0; i < 3; ++i)
    {
        TotalCalories += HighestCalories[i];
    }

    cout << TotalCalories << endl;
}