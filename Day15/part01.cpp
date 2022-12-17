#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct Sensor
{
    int X;
    int Y;
    int BeaconX;
    int BeaconY;
    int ClosestBeaconDistance;

    Sensor()
        : X(0), Y(0), BeaconX(0), BeaconY(0), ClosestBeaconDistance(0)
    {
    }

    Sensor(int InX, int InY, int InBeaconX, int InBeaconY, int InClosestBeaconDistance)
        : X(InX), Y(InY), BeaconX(InBeaconX), BeaconY(InBeaconY), ClosestBeaconDistance(InClosestBeaconDistance)
    {
    }
};

int main()
{
    string StrSensors;
    ifstream MyReadFile("input.txt");

    Sensor Sensors[27] = {};
    int NumSensors = 0;

    // Parse sensors
    while (getline(MyReadFile, StrSensors))
    {
        // Erase prefix and parse sensor X coordinate
        StrSensors.erase(StrSensors.begin(), StrSensors.begin() + 12);
        int DelimiterIndex = StrSensors.find(',');
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

        int X = stoi(StrX);
        int Y = stoi(StrY);
        int BeaconX = stoi(StrBeaconX);
        int BeaconY = stoi(StrBeaconY);

        // Add sensor to list
        Sensors[NumSensors].X = X;
        Sensors[NumSensors].Y = Y;
        Sensors[NumSensors].BeaconX = BeaconX;
        Sensors[NumSensors].BeaconY = BeaconY;
        Sensors[NumSensors].ClosestBeaconDistance = abs(X - BeaconX) + abs(Y - BeaconY);

        ++NumSensors;
    }

    MyReadFile.close();

    int RowToCheck = 2000000;
    set<int> CheckedCoordinatesX;

    // Check coordinates covered by sensors
    for (int SensorIndex = 0; SensorIndex < NumSensors; ++SensorIndex)
    {
        Sensor &CurrSensor = Sensors[SensorIndex];

        int DistanceY = abs(RowToCheck - CurrSensor.Y);

        int MaxDistanceX = CurrSensor.ClosestBeaconDistance - DistanceY;

        // Get maximum offset of X based on the range of the sensors and the distance to the Y coordinate
        if (MaxDistanceX >= 0)
        {
            CheckedCoordinatesX.insert(CurrSensor.X);

            for (int OffsetX = 1; OffsetX <= abs(MaxDistanceX); ++OffsetX)
            {
                CheckedCoordinatesX.insert(CurrSensor.X - OffsetX);
                CheckedCoordinatesX.insert(CurrSensor.X + OffsetX);
            }
        }
    }

    // Remove squares that already have beacons
    for (int SensorIndex = 0; SensorIndex < NumSensors; ++SensorIndex)
    {
        Sensor &CurrSensor = Sensors[SensorIndex];

        if (CurrSensor.BeaconY == RowToCheck)
        {
            CheckedCoordinatesX.erase(CurrSensor.BeaconX);
        }
    }

    cout << CheckedCoordinatesX.size() << endl;
}