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

    int ValueToAdd = 0;
    bool AddInstruction = false;

    do
    {
        // Print pixel of current cycle
        int Pixel = (Cycle - 1) % 40;

        cout << (Pixel >= RegisterX - 1 && Pixel <= RegisterX + 1 ? '#' : '.');

        // If cycle if 40 or 80 or 120... etc, begin new line
        if (Cycle % 40 == 0)
        {
            cout << endl;
        }

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

        // Cycle will repeat while there are instructions
    } while (AddInstruction || !MyReadFile.eof());

    MyReadFile.close();

    cout << endl;
}