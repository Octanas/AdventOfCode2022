#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    /**
     * A - Rock
     * B - Paper
     * C - Scissors
     *
     * X - Rock (1 point)
     * Y - Paper (2 points)
     * Z - Scissors (3 points)
     *
     * Wins:
     * A Y
     * B Z
     * C X
     */

    // Combinations resulting in a draw
    map<char, char> Draws = {{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}};
    // Combinations resulting in a win
    map<char, char> Wins = {{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};

    string StrRound;
    ifstream MyReadFile("input.txt");

    int TotalScore = 0;

    while (getline(MyReadFile, StrRound))
    {
        char OpponentPlay = StrRound[0];
        char MyPlay = StrRound[2];

        // Get initial round score based on chosen shape
        int RoundScore = MyPlay == 'X' ? 1 : (MyPlay == 'Y' ? 2 : 3);

        // A draw gives 3 points
        if (Draws[OpponentPlay] == MyPlay)
        {
            RoundScore += 3;
        }
        // A win gives 6 points
        else if (Wins[OpponentPlay] == MyPlay)
        {
            RoundScore += 6;
        }

        TotalScore += RoundScore;
    }

    MyReadFile.close();

    cout << TotalScore << endl;
}