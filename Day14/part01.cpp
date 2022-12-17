#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrRocks;
    ifstream MyReadFile("input.txt");

    // Cave grid
    char Cave[200][200] = {};
    int CaveMinX = 400;
    int CaveMinY = 0;

    // Parse cave
    while (getline(MyReadFile, StrRocks))
    {
        bool ParsedRocks = false;
        int PrevRockX = -1;
        int PrevRockY = -1;

        while (!ParsedRocks)
        {
            int SeparatorIndex = StrRocks.find(" -> ");

            string Rock = StrRocks;

            if (SeparatorIndex == -1)
            {
                ParsedRocks = true;
            }
            else
            {
                Rock = StrRocks.substr(0, SeparatorIndex);
                StrRocks.erase(0, SeparatorIndex + 4);
            }

            int CoordinateSeparatorIndex = Rock.find(',');

            string StrX = Rock.substr(0, CoordinateSeparatorIndex);
            string StrY = Rock.substr(CoordinateSeparatorIndex + 1);

            int CurrRockX = stoi(StrX);
            int CurrRockY = stoi(StrY);

            // Add rocks from previous point to current point
            if (PrevRockX != -1 && PrevRockY != -1)
            {
                int IncreaseX = CurrRockX - PrevRockX > 0;
                int IncreaseY = CurrRockY - PrevRockY > 0;

                int X = PrevRockX;

                while (IncreaseX && X <= CurrRockX || !IncreaseX && X >= CurrRockX)
                {
                    int Y = PrevRockY;

                    while (IncreaseY && Y <= CurrRockY || !IncreaseY && Y >= CurrRockY)
                    {
                        Cave[X - CaveMinX][Y - CaveMinY] = '#';

                        if (IncreaseY)
                        {
                            ++Y;
                        }
                        else
                        {
                            --Y;
                        }
                    }

                    if (IncreaseX)
                    {
                        ++X;
                    }
                    else
                    {
                        --X;
                    }
                }
            }

            PrevRockX = CurrRockX;
            PrevRockY = CurrRockY;
        }
    }

    MyReadFile.close();

    int RestedUnitsOfSand = 0;
    bool IntoAbyss = false;

    // Move sand
    while (!IntoAbyss)
    {
        int SandX = 500 - CaveMinX;
        int SandY = 0 - CaveMinY;

        while (true)
        {
            // Sand is out of bounds below
            if (SandY + 1 >= 200)
            {
                IntoAbyss = true;
                break;
            }

            char SquareBelow = Cave[SandX][SandY + 1];

            // Sand moved below
            if (SquareBelow != '#' && SquareBelow != 'o')
            {
                ++SandY;
                continue;
            }

            // Sand is out of bounds to the left
            if (SandX - 1 < 0)
            {
                IntoAbyss = true;
                break;
            }

            char SquareBelowLeft = Cave[SandX - 1][SandY + 1];

            // Sand moved below to the left
            if (SquareBelowLeft != '#' && SquareBelowLeft != 'o')
            {
                ++SandY;
                --SandX;
                continue;
            }

            // Sand is out of bounds to the right
            if (SandX + 1 >= 200)
            {
                IntoAbyss = true;
                break;
            }

            char SquareBelowRight = Cave[SandX + 1][SandY + 1];

            // Sand moved below to the right
            if (SquareBelowRight != '#' && SquareBelowRight != 'o')
            {
                ++SandY;
                ++SandX;
                continue;
            }

            // Sand settled at its current position
            Cave[SandX][SandY] = 'o';
            ++RestedUnitsOfSand;
            break;
        }
    }

    cout << RestedUnitsOfSand << endl;
}