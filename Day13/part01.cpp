#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Get items from list string ("[...]"")
vector<string> GetListItems(string InList)
{
    // Remove list brackets
    InList.erase(InList.begin());
    InList.erase(InList.end() - 1);

    vector<string> Items;

    string CurrItem = "";
    int ListsInside = 0;

    for (int i = 0; i < InList.size(); ++i)
    {
        char PacketChar = InList[i];

        if (PacketChar == ',' && ListsInside == 0)
        {
            Items.push_back(CurrItem);
            CurrItem = "";
        }
        else
        {
            // Keep track of how many lists it is inside of
            if (PacketChar == '[')
            {
                ++ListsInside;
            }
            else if (PacketChar == ']')
            {
                --ListsInside;
            }

            CurrItem += PacketChar;
        }
    }

    if (CurrItem != "")
    {
        Items.push_back(CurrItem);
    }

    return Items;
}

/**
 * Compare packets.
 * Returns:
 * - negative number if left is smaller than right
 * - positive number if left is larger than right
 * - zero if they are equal
 */
int ComparePackets(string InPacketLeft, string InPacketRight)
{
    if (InPacketLeft[0] != '[' && InPacketRight[0] != '[')
    {
        // If both packets are number, compare directly
        int NumLeft = stoi(InPacketLeft);
        int NumRight = stoi(InPacketRight);

        return NumLeft - NumRight;
    }
    else
    {
        // If they aren't both numbers, transform any that aren't into lists
        if (InPacketLeft[0] != '[')
        {
            InPacketLeft = "[" + InPacketLeft + ']';
        }

        if (InPacketRight[0] != '[')
        {
            InPacketRight = "[" + InPacketRight + ']';
        }
    }

    vector<string> PacketLeftItems = GetListItems(InPacketLeft);
    vector<string> PacketRightItems = GetListItems(InPacketRight);

    int LeftIndex = 0;
    int RightIndex = 0;

    // Compare items in both lists
    while (LeftIndex < PacketLeftItems.size() && RightIndex < PacketRightItems.size())
    {
        int ComparisonResult = ComparePackets(PacketLeftItems[LeftIndex], PacketRightItems[RightIndex]);

        // If items are not the same, return difference
        if (ComparisonResult != 0)
        {
            return ComparisonResult;
        }

        ++LeftIndex;
        ++RightIndex;
    }

    // Return number of items difference
    return (PacketLeftItems.size() - LeftIndex) - (PacketRightItems.size() - RightIndex);
}

int main()
{
    ifstream MyReadFile("input.txt");

    int PairIndex = 1;
    int SumPairsRightOrder = 0;

    while (!MyReadFile.eof())
    {
        // Read pair of packets
        string PacketLeft;
        getline(MyReadFile, PacketLeft);
        string PacketRight;
        getline(MyReadFile, PacketRight);

        if (ComparePackets(PacketLeft, PacketRight) < 0)
        {
            // If first packet is smaller than the second, add the pair index to the sum
            SumPairsRightOrder += PairIndex;
        }

        // Read empty line
        string DiscardStr;
        getline(MyReadFile, DiscardStr);

        ++PairIndex;
    }

    MyReadFile.close();

    cout << SumPairsRightOrder << endl;
}