#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

struct Sensor
{
    long X;
    long Y;
    long BeaconX;
    long BeaconY;
    long ClosestBeaconDistance;

    Sensor()
        : X(0), Y(0), BeaconX(0), BeaconY(0), ClosestBeaconDistance(0)
    {
    }

    Sensor(long InX, long InY, long InBeaconX, long InBeaconY, long InClosestBeaconDistance)
        : X(InX), Y(InY), BeaconX(InBeaconX), BeaconY(InBeaconY), ClosestBeaconDistance(InClosestBeaconDistance)
    {
    }
};

struct Bounds
{
    long MinX;
    long MaxX;

    Bounds()
        : MinX(0), MaxX(4000000)
    {
    }

    Bounds(int InMinX, int InMaxX)
        : MinX(InMinX), MaxX(InMaxX)
    {
    }
};

int main()
{
    string StrSensors;
    ifstream MyReadFile("input.txt");

    Sensor Sensors[27] = {};
    long NumSensors = 0;

    // Parse sensors
    while (getline(MyReadFile, StrSensors))
    {
        // Erase prefix and parse sensor X coordinate
        StrSensors.erase(StrSensors.begin(), StrSensors.begin() + 12);
        long DelimiterIndex = StrSensors.find(',');
        string StrX = StrSensors.substr(0, DelimiterIndex);

        // Erase prefix and parse sensor Y coordinate
        StrSensors.erase(StrSensors.begin(), StrSensors.begin() + DelimiterIndex + 4);
        DelimiterIndex = StrSensors.find(':');
        string StrY = StrSensors.substr(0, DelimiterIndex);

        // Erase prefix and parse closest beacon X coordinate
        StrSensors.erase(StrSensors.begin(), StrSensors.begin() + DelimiterIndex + 25);
        DelimiterIndex = StrSensors.find(',');
        string StrBeaconX = StrSensors.substr(0, DelimiterIndex);

        // Erase prefix and parse closest beacon Y coordinate
        StrSensors.erase(StrSensors.begin(), StrSensors.begin() + DelimiterIndex + 4);
        string StrBeaconY = StrSensors;

        long X = stoi(StrX);
        long Y = stoi(StrY);
        long BeaconX = stoi(StrBeaconX);
        long BeaconY = stoi(StrBeaconY);

        // Add sensor to list
        Sensors[NumSensors].X = X;
        Sensors[NumSensors].Y = Y;
        Sensors[NumSensors].BeaconX = BeaconX;
        Sensors[NumSensors].BeaconY = BeaconY;
        Sensors[NumSensors].ClosestBeaconDistance = abs(X - BeaconX) + abs(Y - BeaconY);

        ++NumSensors;
    }

    MyReadFile.close();

    long CoordMin = 0;
    long CoordMax = 4000000;
    long TuningFrequency = 0;

    // X and Y can be no lower than CoordMin and no higher than CoordMax.
    for (long RowToCheck = CoordMin; RowToCheck <= CoordMax; ++RowToCheck)
    {
        cout << "Checking row " << to_string(RowToCheck) << endl;

        vector<Bounds> ValidBounds;
        ValidBounds.push_back(Bounds(CoordMin, CoordMax));

        // Check coordinates covered by sensors
        for (long SensorIndex = 0; SensorIndex < NumSensors; ++SensorIndex)
        {
            Sensor &CurrSensor = Sensors[SensorIndex];

            // Get distance from sensor X coordenate to bounds in this row
            long DistanceY = abs(RowToCheck - CurrSensor.Y);
            long MaxDistanceX = CurrSensor.ClosestBeaconDistance - DistanceY;

            if (MaxDistanceX >= 0)
            {
                // Get bounds of the range of the sensor in this row
                long MinX = CurrSensor.X - MaxDistanceX;
                long MaxX = CurrSensor.X + MaxDistanceX;

                // Remove covered range from valid bounds
                for (int BoundIndex = 0; BoundIndex < ValidBounds.size(); ++BoundIndex)
                {
                    Bounds &CurrBounds = ValidBounds[BoundIndex];

                    if (MinX <= CurrBounds.MinX && CurrBounds.MaxX <= MaxX)
                    {
                        // Covered range overlaps these bounds entirely.
                        // Delete bounds
                        ValidBounds.erase(ValidBounds.begin() + BoundIndex);
                        --BoundIndex;
                    }
                    else if (CurrBounds.MinX < MinX && MaxX < CurrBounds.MaxX)
                    {
                        // Covered range is contained inside these bounds.
                        // Separate bounds in two pairs
                        Bounds LowerBounds(CurrBounds.MinX, MinX - 1);
                        Bounds UpperBounds(MaxX + 1, CurrBounds.MaxX);

                        ValidBounds.erase(ValidBounds.begin() + BoundIndex);
                        ValidBounds.insert(ValidBounds.begin() + BoundIndex, LowerBounds);
                        ValidBounds.insert(ValidBounds.begin() + BoundIndex + 1, UpperBounds);
                        ++BoundIndex;
                    }
                    else if (CurrBounds.MinX < MinX && MinX <= CurrBounds.MaxX)
                    {
                        // Covered range overlaps partly with these bounds from upper bound.
                        // Adjust bounds.
                        Bounds LowerBounds(CurrBounds.MinX, MinX - 1);

                        ValidBounds.erase(ValidBounds.begin() + BoundIndex);
                        ValidBounds.insert(ValidBounds.begin() + BoundIndex, LowerBounds);
                    }
                    else if (CurrBounds.MinX <= MaxX && MaxX < CurrBounds.MaxX)
                    {
                        // Covered range overlaps partly with these bounds from lower bound.
                        // Adjust bounds.
                        Bounds UpperBounds(MaxX + 1, CurrBounds.MaxX);

                        ValidBounds.erase(ValidBounds.begin() + BoundIndex);
                        ValidBounds.insert(ValidBounds.begin() + BoundIndex, UpperBounds);
                    }
                }
            }
        }

        // If number of valid bounds is not 0,
        // that means coordinates not covered by any sensor were found.
        // Distress beacon will be in those coordinates.
        if (ValidBounds.size() != 0)
        {
            Bounds &CurrBounds = ValidBounds[0];

            if (CurrBounds.MinX == CurrBounds.MaxX)
            {
                cout << "Found at (" << to_string(CurrBounds.MinX) << "," << to_string(RowToCheck) << ")" << endl;
                TuningFrequency = CurrBounds.MinX * 4000000 + RowToCheck;
                break;
            }
        }
    }

    cout << TuningFrequency << endl;
}