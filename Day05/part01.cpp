#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main()
{
    string StrCrates;
    ifstream MyReadFile("input.txt");

    // This array will have each stack of crates
    stack<char> *Stacks;
    int NumStacks = 0;

    string UnparsedCrates = "";
    bool ParsedCrates = false;

    while (getline(MyReadFile, StrCrates))
    {
        if (ParsedCrates)
        {
            // Crates have been parsed, parse instructions

            // Parse number of crates to move
            StrCrates.erase(0, 5);
            int DelimiterIndex = StrCrates.find(' ');
            int NumCrateToMove = stoi(StrCrates.substr(0, DelimiterIndex));
            StrCrates.erase(0, DelimiterIndex + 6);

            // Parse stack to move from
            DelimiterIndex = StrCrates.find(' ');
            int StackFrom = stoi(StrCrates.substr(0, DelimiterIndex)) - 1;
            StrCrates.erase(0, DelimiterIndex + 4);
            
            // Parse stack to move to
            int StackTo = stoi(StrCrates.substr(0, StrCrates.length())) - 1;

            // Perform stack changes
            for (int i = 0; i < NumCrateToMove; ++i)
            {
                const char Crate = Stacks[StackFrom].top();
                Stacks[StackFrom].pop();
                Stacks[StackTo].push(Crate);
            }
        }
        else
        {
            // Parse Crates

            // When an empty line is found, it means that crates have been parsed
            if (StrCrates.empty())
            {
                ParsedCrates = true;
            }
            else if (StrCrates.find('[') != -1)
            {
                // Store string of crates to parse later
                UnparsedCrates += StrCrates + ' ';
            }
            else
            {
                // Count number of stacks
                for (int i = 0; i < StrCrates.length(); ++i)
                {
                    if (StrCrates[i] != ' ')
                    {
                        NumStacks++;
                    }
                }

                cout << "Number of stacks: ";
                cout << NumStacks << endl;

                // Initialize array of stack
                Stacks = new stack<char>[NumStacks];

                int StackNumber = NumStacks - 1;

                // Move backwards through the crates string
                // and add them to each stack from the bottom up
                //
                // Jump 4 characters each time so it only reads indexes where crates will be
                for (int i = UnparsedCrates.length() - 1; i > 0; i -= 4)
                {
                    const char Crate = UnparsedCrates[i - 2];

                    // Ignore empty spaces and null terminator
                    if(Crate != ' ' && Crate != '\0')
                    {
                        Stacks[StackNumber].push(Crate);
                    }

                    // Iterate through each stack (backwards) as we parse the crates
                    StackNumber = StackNumber == 0 ? NumStacks - 1 : StackNumber - 1;
                }
            }
        }
    }

    // Print crates on top of the stacks
    string TopCrates = "";

    for (int i = 0; i < NumStacks; ++i)
    {
        TopCrates += Stacks[i].top();
    }

    cout << "Top crates: " + TopCrates << endl;

    MyReadFile.close();
    delete[] Stacks;
}