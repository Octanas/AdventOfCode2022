#include <iostream>
#include <fstream>

using namespace std;

// To solve this, store the sequence of read chars, until the desired length is reached.
// Before adding a new character, check if it is already present in the sequence.
// If the new character is already in the sequence, delete the first characters of the sequence until there are no more repetitions.
// To do this, just delete until the instance of the repeated character, inclusively.
//
// Example:
// Sequence: qwr
// New character: w
// Resulting sequence (with repetition): qwrw
// What happens: Remove the first two characters
// Resulting sequence (without repetition): rw
//
// This will repeat everytime there is a character repetion.
// When the sequence reaches the desired length, it will do so without any repeating characters.

int main()
{
    string StrCrates;
    ifstream MyReadFile("input.txt");

    // Desired sequence length to be reached
    int DesiredSequenceLength = 14;

    // This array will hold current sequence of chars
    char Marker[DesiredSequenceLength] = {};
    int MarkerLength = 0;

    // The current character number
    int CharNum = 0;
    char C;

    // Read a character at a time
    while (!MyReadFile.eof())
    {
        char C = MyReadFile.get();
        CharNum++;

        // Check if the current character is already in the sequence
        for (int i = 0; i < MarkerLength; ++i)
        {
            if (C == Marker[i])
            {
                // If the current character is already in the sequence,
                // delete the first characters until the instance of the repeated character.
                for (int j = 0; j < i + 1; ++j)
                {
                    for (int k = 0; k < MarkerLength - 1; ++k)
                    {
                        Marker[k] = Marker[k + 1];
                    }

                    MarkerLength--;
                }

                break;
            }
        }

        // Add current character to sequence
        Marker[MarkerLength++] = C;

        // If sequence has reached desired length, stop reading input
        if (MarkerLength == DesiredSequenceLength)
        {
            break;
        }
    }

    // Print the number of the last character in the sequence
    cout << CharNum << endl;

    MyReadFile.close();
}