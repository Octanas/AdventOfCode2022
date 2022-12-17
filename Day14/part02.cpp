#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string StrRocks;
    ifstream MyReadFile("input.txt");

    // Cave grid
    // Cave width has been increased
    char Cave[1000][200] = {};
    // CaveMinX has been changed, to that the X coordinate 500 in the input
    // is actually index 500 on the array
    // This needs to be done because in this part, the sand spreads a lot more
    int CaveMinX = 0;
    int CaveMinY = 0;

    // Keep track of highest Y coordinate so we know
    // where the floor will be
    int HighestY = 0;

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

            if (CurrRockY > HighestY)
            {
                HighestY = CurrRockY;
            }

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

    int FloorY = HighestY + 2 - CaveMinY;

    // Move sand
    while (true)
    {
        int SandX = 500 - CaveMinX;
        int SandY = 0 - CaveMinY;

        while (true)
        {
            // Sand is on floor
            if (SandY == FloorY - 1)
            {
                // Sand settled at its current position
                Cave[SandX][SandY] = 'o';
                ++RestedUnitsOfSand;
                break;
            }

            char SquareBelow = Cave[SandX][SandY + 1];

            // Sand moved below
            if (SquareBelow != '#' && SquareBelow != 'o')
            {
                ++SandY;
                continue;
            }

            char SquareBelowLeft = Cave[SandX - 1][SandY + 1];

            // Sand moved below to the left
            if (SquareBelowLeft != '#' && SquareBelowLeft != 'o' && SandY != FloorY)
            {
                ++SandY;
                --SandX;
                continue;
            }
            
            char SquareBelowRight = Cave[SandX + 1][SandY + 1];

            // Sand moved below to the right
            if (SquareBelowRight != '#' && SquareBelowRight != 'o' && SandY != FloorY)
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

        // If sand stopped at the source, no more sand will come out
        if(SandX == 500 - CaveMinX && SandY == 0 - CaveMinY)
        {
            break;
        }
    }

    cout << RestedUnitsOfSand << endl;
}