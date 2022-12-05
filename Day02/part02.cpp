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
     * X - Lose
     * Y - Draw
     * Z - Win
     *
     * Rock (1 point)
     * Paper (2 points)
     * Scissors (3 points)
     * 
     * Wins:
     * A Paper
     * B Scissors
     * C Rock
     */

    // Points of shape to be played when losing
    map<char, int> Losses = {{'A', 3}, {'B', 1}, {'C', 2}};
    // Points of shape to be played when drawing
    map<char, int> Draws = {{'A', 1}, {'B', 2}, {'C', 3}};
    // Points of shape to be played when winning
    map<char, int> Wins = {{'A', 2}, {'B', 3}, {'C', 1}};

    string StrRound;
    ifstream MyReadFile("input.txt");

    int TotalScore = 0;

    while (getline(MyReadFile, StrRound))
    {
        char OpponentPlay = StrRound[0];
        char Outcome = StrRound[2];

        int RoundScore = 0;

        // Loss
        if(Outcome == 'X')
        {
            // 0 points plus shape points
            RoundScore += Losses[OpponentPlay];
        }
        // Draw
        else if(Outcome == 'Y')
        {
            // 3 points plus shape points
            RoundScore += 3 + Draws[OpponentPlay];
        }
        // Win
        else
        {
            // 6 points plus shape points
            RoundScore += 6 + Wins[OpponentPlay];
        }

        TotalScore += RoundScore;
    }

    MyReadFile.close();

    cout << TotalScore << endl;
}