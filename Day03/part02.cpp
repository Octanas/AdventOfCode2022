#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream MyReadFile("input.txt");

    int TotalPriority = 0;

    while (MyReadFile.peek() != EOF)
    {
        char RepeatedItem = ' ';

        // Read three lines in a row
        string SackOne;
        getline(MyReadFile, SackOne);
        string SackTwo;
        getline(MyReadFile, SackTwo);
        string SackThree;
        getline(MyReadFile, SackThree);

        // If the same item is found in all lines, store it and stop searching
        for (int i = 0; i < SackOne.length(); ++i)
        {
            for (int j = 0; j < SackTwo.length(); ++j)
            {
                if (SackOne[i] == SackTwo[j])
                {
                    bool Found = false;

                    for (int k = 0; k < SackThree.length(); ++k)
                    {
                        if (SackOne[i] == SackThree[k])
                        {
                            Found = true;
                            RepeatedItem = SackOne[i];
                            break;
                        }
                    }

                    if (RepeatedItem != ' ')
                    {
                        break;
                    }
                }
            }

            if (RepeatedItem != ' ')
            {
                break;
            }
        }

        // Sum priority of repeated item
        int CharValue = (int)RepeatedItem;
        if (CharValue >= 97)
        {
            // Lowercase letters start at 97
            // Subtract 96 so that 'a' is 1, 'b' is 2, etc.
            TotalPriority += CharValue - 96;
        }
        else
        {
            // Lowercase letters start at 65
            // Subtract 38 so that 'A' is 27, 'B' is 28, etc.
            TotalPriority += CharValue - 38;
        }
    }

    MyReadFile.close();

    cout << TotalPriority << endl;
}