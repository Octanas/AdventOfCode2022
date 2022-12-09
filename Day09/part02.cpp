#include <iostream>
#include <fstream>

using namespace std;

struct Location
{
    int X;
    int Y;

    Location(const int InX = 0, const int InY = 0)
        : X(InX), Y(InY)
    {
    }

    bool operator==(const Location &InOtherLocation) const
    {
        return this->X == InOtherLocation.X && this->Y == InOtherLocation.Y;
    }
};

int main()
{
    string StrMotions;
    ifstream MyReadFile("input.txt");

    // This array will hold each location already visited by the tail
    Location VisitedLocations[10000] = {};

    // Start with 1 visited location at (0,0)
    int NumVisitedLocations = 1;

    // Rope has 10 knots, all starting at (0,0)
    Location Rope[10];

    // Parse motions
    while (getline(MyReadFile, StrMotions))
    {
        // Get motion direction
        char DirectionChar = StrMotions[0];

        bool HorizontalMovement = DirectionChar == 'R' || DirectionChar == 'L';

        // Get motion steps
        string StepsStr = StrMotions.substr(2);
        int Steps = stoi(StepsStr);

        for (int i = 0; i < Steps; ++i)
        {
            // Move head
            if (HorizontalMovement)
            {
                Rope[0].X = Rope[0].X + (DirectionChar == 'R' ? 1 : -1);
            }
            else
            {
                Rope[0].Y = Rope[0].Y + (DirectionChar == 'U' ? 1 : -1);
            }

            bool TailMoved = false;

            // Move all aother knots
            for (int RopeIndex = 1; RopeIndex < 10; ++RopeIndex)
            {
                // Check distance of subsequent knots
                int DiffX = Rope[RopeIndex - 1].X - Rope[RopeIndex].X;
                int DiffY = Rope[RopeIndex - 1].Y - Rope[RopeIndex].Y;

                // Move knot it is too far away from previous knot
                // Diff? / abs(Diff?) is equal to 1 or -1, depending on the desired direction of the movement
                if (abs(DiffX) > 1)
                {
                    if (abs(DiffY) > 0)
                    {
                        // Move diagonal
                        Rope[RopeIndex].Y += DiffY / abs(DiffY);
                    }

                    Rope[RopeIndex].X += DiffX / abs(DiffX);

                    if (RopeIndex == 9)
                    {
                        TailMoved = true;
                    }
                }
                else if (abs(DiffY) > 1)
                {
                    if (abs(DiffX) > 0)
                    {
                        // Move diagonal
                        Rope[RopeIndex].X += DiffX / abs(DiffX);
                    }

                    Rope[RopeIndex].Y += DiffY / abs(DiffY);

                    if (RopeIndex == 9)
                    {
                        TailMoved = true;
                    }
                }
            }

            // If tail moved, check if new location has been visited
            if (TailMoved)
            {
                bool VisitedLoc = false;

                // Check if location has been visited
                for (int j = 0; j < NumVisitedLocations; ++j)
                {
                    if (VisitedLocations[j] == Rope[9])
                    {
                        VisitedLoc = true;
                        break;
                    }
                }

                if (!VisitedLoc)
                {
                    // Add unvisited location to array
                    VisitedLocations[NumVisitedLocations].X = Rope[9].X;
                    VisitedLocations[NumVisitedLocations].Y = Rope[9].Y;
                    ++NumVisitedLocations;
                }
            }
        }
    }

    MyReadFile.close();

    cout << NumVisitedLocations << endl;
}