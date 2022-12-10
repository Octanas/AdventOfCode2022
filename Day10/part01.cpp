#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrInstructions;
    ifstream MyReadFile("input.txt");

    // Register X and Cycle start with value 1
    int RegisterX = 1;
    int Cycle = 1;

    int InterestingSignalStrengths = 0;

    int ValueToAdd = 0;
    bool AddInstruction = false;

    do
    {
        if (AddInstruction)
        {
            // We are in the second cycle of the add instruction, add the value
            RegisterX += ValueToAdd;
            AddInstruction = false;
        }
        else
        {
            getline(MyReadFile, StrInstructions);

            if (StrInstructions != "noop")
            {
                // Read value to add to register in the next cycle
                string ValueStr = StrInstructions.substr(5);
                ValueToAdd = stoi(ValueStr);

                AddInstruction = true;
            }
        }

        ++Cycle;

        // If cycle if 20 or 60 or 100... etc, log the value and sum the signal strength
        if (Cycle % 40 == 20)
        {
            cout << "Cycle ";
            cout << Cycle;
            cout << ": ";
            cout << RegisterX << endl;

            InterestingSignalStrengths += RegisterX * Cycle;
        }

        // If cycle 220 is reached, we can stop
        if (Cycle == 220)
        {
            break;
        }

        // Cycle will repeat while there are instructions
    } while (AddInstruction || !MyReadFile.eof());

    MyReadFile.close();

    cout << endl;
    cout << InterestingSignalStrengths << endl;
}