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

    // Start with 1 visited location at (0, 0)
    int NumVisitedLocations = 1;

    // Head and tail start at (0 ,0)
    Location HeadLoc;
    Location TailLoc;

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
                HeadLoc.X = HeadLoc.X + (DirectionChar == 'R' ? 1 : -1);
            }
            else
            {
                HeadLoc.Y = HeadLoc.Y + (DirectionChar == 'U' ? 1 : -1);
            }

            // Check distance of tail to heads
            int DiffX = HeadLoc.X - TailLoc.X;
            int DiffY = HeadLoc.Y - TailLoc.Y;

            bool Moved = false;

            // Move tail it is too far away from head
            // Diff? / abs(Diff?) is equal to 1 or -1, depending on the desired direction of the movement 
            if (abs(DiffX) > 1)
            {
                if (abs(DiffY) > 0)
                {
                    // Move diagonal
                    TailLoc.Y += DiffY / abs(DiffY);
                }

                TailLoc.X += DiffX / abs(DiffX);

                Moved = true;
            }
            else if (abs(DiffY) > 1)
            {
                if (abs(DiffX) > 0)
                {
                    // Move diagonal
                    TailLoc.X += DiffX / abs(DiffX);
                }

                TailLoc.Y += DiffY / abs(DiffY);

                Moved = true;
            }

            // If tail moved, check if new location has been visited
            if (Moved)
            {
                bool VisitedLoc = false;

                // Check if location has been visited
                for (int j = 0; j < NumVisitedLocations; ++j)
                {
                    if (VisitedLocations[j] == TailLoc)
                    {
                        VisitedLoc = true;
                        break;
                    }
                }

                if (!VisitedLoc)
                {
                    // Add unvisited location to array
                    VisitedLocations[NumVisitedLocations].X = TailLoc.X;
                    VisitedLocations[NumVisitedLocations].Y = TailLoc.Y;
                    ++NumVisitedLocations;
                }
            }
        }
    }

    MyReadFile.close();

    cout << NumVisitedLocations << endl;
}