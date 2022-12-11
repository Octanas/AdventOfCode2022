#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

enum OperationType
{
    Add = 0,
    Multiply = 1
};

struct Monkey
{
    vector<int> Items;

    OperationType Operation;
    // -1 value for these two variables means 'old' value
    int OperationFirstValue;
    int OperationSecondValue;

    int TestDivisible;
    int TestIfTrue;
    int TestIfFalse;

    int ItemsInspected;
};

int main()
{
    string StrMonkeys;
    ifstream MyReadFile("input.txt");

    Monkey Monkeys[8];
    int NumMonkeys = 0;

    // Parse monkeys
    while (getline(MyReadFile, StrMonkeys))
    {
        if (StrMonkeys.substr(0, 6) == "Monkey")
        {
            ++NumMonkeys;
        }
        else
        {
            Monkey *CurrentMonkey = &Monkeys[NumMonkeys - 1];

            if (StrMonkeys.substr(0, 17) == "  Starting items:")
            {
                string StrItems = StrMonkeys.substr(18);

                int SeparatorIndex = StrItems.find(',');

                while (SeparatorIndex != -1)
                {
                    int Item = stoi(StrItems.substr(0, SeparatorIndex));
                    CurrentMonkey->Items.push_back(Item);

                    StrItems.erase(0, SeparatorIndex + 2);

                    SeparatorIndex = StrItems.find(',');
                }

                int Item = stoi(StrItems);

                CurrentMonkey->Items.push_back(Item);
                CurrentMonkey->ItemsInspected = 0;
            }
            else if (StrMonkeys.substr(0, 12) == "  Operation:")
            {
                string StrOperation = StrMonkeys.substr(19);

                int SeparatorIndex = StrOperation.find('+');

                if (SeparatorIndex != -1)
                {
                    CurrentMonkey->Operation = OperationType::Add;
                }
                else
                {
                    CurrentMonkey->Operation = OperationType::Multiply;
                    SeparatorIndex = StrOperation.find('*');
                }

                string StrFirstValue = StrOperation.substr(0, SeparatorIndex - 1);
                string StrSecondValue = StrOperation.substr(SeparatorIndex + 2);

                CurrentMonkey->OperationFirstValue = StrFirstValue == "old" ? -1 : stoi(StrFirstValue);
                CurrentMonkey->OperationSecondValue = StrSecondValue == "old" ? -1 : stoi(StrSecondValue);
            }
            else if (StrMonkeys.substr(0, 7) == "  Test:")
            {
                int LastSeparatorIndex = StrMonkeys.find_last_of(' ');

                string StrTestDivisible = StrMonkeys.substr(LastSeparatorIndex + 1);

                CurrentMonkey->TestDivisible = stoi(StrTestDivisible);
            }
            else if (StrMonkeys.substr(0, 12) == "    If true:")
            {
                int LastSeparatorIndex = StrMonkeys.find_last_of(' ');

                string StrTestTrue = StrMonkeys.substr(LastSeparatorIndex + 1);

                CurrentMonkey->TestIfTrue = stoi(StrTestTrue);
            }
            else if (StrMonkeys.substr(0, 13) == "    If false:")
            {
                int LastSeparatorIndex = StrMonkeys.find_last_of(' ');

                string StrTestFalse = StrMonkeys.substr(LastSeparatorIndex + 1);

                CurrentMonkey->TestIfFalse = stoi(StrTestFalse);
            }
        }
    }

    MyReadFile.close();

    // Process Rounds
    for (int Round = 1; Round <= 20; ++Round)
    {
        for (int MonkeyIndex = 0; MonkeyIndex < NumMonkeys; ++MonkeyIndex)
        {
            Monkey *CurrentMonkey = &Monkeys[MonkeyIndex];

            // Inspect every item in the list
            while (CurrentMonkey->Items.size() > 0)
            {
                int Item = CurrentMonkey->Items[0];
                CurrentMonkey->Items.erase(CurrentMonkey->Items.begin());

                // Perform operation on worry level
                if (CurrentMonkey->Operation == OperationType::Add)
                {
                    Item = (CurrentMonkey->OperationFirstValue == -1 ? Item : CurrentMonkey->OperationFirstValue) + (CurrentMonkey->OperationSecondValue == -1 ? Item : CurrentMonkey->OperationSecondValue);
                }
                else
                {
                    Item = (CurrentMonkey->OperationFirstValue == -1 ? Item : CurrentMonkey->OperationFirstValue) * (CurrentMonkey->OperationSecondValue == -1 ? Item : CurrentMonkey->OperationSecondValue);
                }

                // Process relief
                Item = floor(Item / 3.0);

                // Check which monkey will receive the item and add it to its array of items to be inspected
                Monkey *Receiver = &Monkeys[Item % CurrentMonkey->TestDivisible == 0 ? CurrentMonkey->TestIfTrue : CurrentMonkey->TestIfFalse];

                Receiver->Items.push_back(Item);

                CurrentMonkey->ItemsInspected++;
            }
        }
    }

    // Find the two monkeys with higher number of items inspected
    int HighestItemsInspected[2] = {0, 0};

    for (int MonkeyIndex = 0; MonkeyIndex < NumMonkeys; ++MonkeyIndex)
    {
        int CurrItemsInspected = Monkeys[MonkeyIndex].ItemsInspected;
        
        if (CurrItemsInspected > HighestItemsInspected[1])
        {
            HighestItemsInspected[1] = CurrItemsInspected;

            if(HighestItemsInspected[1] > HighestItemsInspected[0])
            {
                int TempItem = HighestItemsInspected[0];
                HighestItemsInspected[0] = HighestItemsInspected[1];
                HighestItemsInspected[1] = TempItem;
            }
        }
    }

    int MonkeyBusinessLevel = HighestItemsInspected[0] * HighestItemsInspected[1];

    cout << MonkeyBusinessLevel << endl;
}