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
    string StrPackets;
    ifstream MyReadFile("input.txt");

    string DividerPacketOne = "[[2]]";
    string DividerPacketTwo = "[[6]]";

    vector<string> Packets;

    // Parse packets
    while (getline(MyReadFile, StrPackets))
    {
        if (StrPackets != "")
        {
            Packets.push_back(StrPackets);
        }
    }

    MyReadFile.close();

    // Add divider packets
    Packets.push_back(DividerPacketOne);
    Packets.push_back(DividerPacketTwo);

    // Order Packet List with Bubble Sort
    bool Swapped = true;
    int NumPackets = Packets.size();

    while(Swapped)
    {
        Swapped = false;

        for (int i = 1; i < NumPackets; ++i)
        {
            if(ComparePackets(Packets[i - 1], Packets[i]) > 0)
            {
                string AuxPacket = Packets[i - 1];
                Packets[i - 1] = Packets[i];
                Packets[i] = AuxPacket;

                Swapped = true;
            }
        }
    }

    int DecoderKey = 1;

    // Search for divider packets
    for (int i = 0; i < Packets.size(); ++i)
    {
        if(Packets[i] == DividerPacketOne || Packets[i] == DividerPacketTwo)
        {
            // Update decoder key
            DecoderKey *= (i + 1);
        }
    }

    cout << DecoderKey << endl;
}