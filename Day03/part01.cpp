#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrSack;
    ifstream MyReadFile("input.txt");

    int TotalPriority = 0;

    while (getline(MyReadFile, StrSack))
    {
        int NumItems = StrSack.length();
        int NumItemsPerCompartment = NumItems / 2;

        // This array will hold the items repeated in both halfs
        // Will only contain one instance of each type
        char RepeatedItems[NumItemsPerCompartment] = {};
        int NumRepeatedItems = 0;

        // Compare items in the first half with the items on the second half
        for (int i = 0; i < NumItemsPerCompartment; ++i)
        {
            for (int j = NumItemsPerCompartment; j < NumItems; ++j)
            {
                if(StrSack[i] == StrSack[j])
                {
                    // Check if item was already registered as repeated
                    // Don't place same item more than once
                    bool NotYetFound = true;

                    for (int k = 0; k < NumRepeatedItems; ++k)
                    {
                        if(StrSack[i] == RepeatedItems[k])
                        {
                            NotYetFound = false;
                            break;
                        }
                    }

                    if(NotYetFound)
                    {
                        RepeatedItems[NumRepeatedItems++] = StrSack[i];
                        break;
                    }
                }
            }
        }

        // Sum priorities of repeated items
        for (int i = 0; i < NumRepeatedItems; ++i)
        {
            int CharValue = (int)RepeatedItems[i];
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
    }

    MyReadFile.close();

    cout << TotalPriority << endl;
}