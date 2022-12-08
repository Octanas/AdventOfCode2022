#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    string StrTrees;
    ifstream MyReadFile("input.txt");

    // Grid is 99x99
    int GridRows = 99;
    int GridColumns = 99;

    int *TreeGrid[GridRows] = {};
    int NumRows = 0;

    // Parse tree grid
    while (getline(MyReadFile, StrTrees))
    {
        int RowSize = StrTrees.length();

        TreeGrid[NumRows] = new int[RowSize];

        for (int i = 0; i < RowSize; ++i)
        {
            TreeGrid[NumRows][i] = StrTrees[i];
        }

        ++NumRows;
    }

    MyReadFile.close();

    int HighestScenicScore = 0;

    // Iterate through every tree
    for (int Row = 0; Row < GridRows; ++Row)
    {
        for (int Column = 0; Column < GridColumns; ++Column)
        {
            int CurrentTree = TreeGrid[Row][Column];

            int NumTreesLeft = 0;
            int NumTreesTop = 0;
            int NumTreesRight = 0;
            int NumTreesBottom = 0;

            // Check how many trees are visible to the left of the current one
            for (int RowLeft = Row - 1; RowLeft >= 0; --RowLeft)
            {
                ++NumTreesLeft;

                int Tree = TreeGrid[RowLeft][Column];

                if (Tree >= CurrentTree)
                {
                    // This tree is as high as the current one,
                    // no more trees can be seen past this one
                    break;
                }
            }

            // Check how many trees are visible on the top of the current one
            for (int ColumnTop = Column - 1; ColumnTop >= 0; --ColumnTop)
            {
                ++NumTreesTop;

                int Tree = TreeGrid[Row][ColumnTop];

                if (Tree >= CurrentTree)
                {
                    // This tree is as high as the current one,
                    // no more trees can be seen past this one
                    break;
                }
            }

            // Check how many trees are visible to the right of the current one
            for (int RowRight = Row + 1; RowRight < GridRows; ++RowRight)
            {
                ++NumTreesRight;

                int Tree = TreeGrid[RowRight][Column];

                if (Tree >= CurrentTree)
                {
                    // This tree is as high as the current one,
                    // no more trees can be seen past this one
                    break;
                }
            }

            // Check how many trees are visible on the bottom of the current one
            for (int ColumnBottom = Column + 1; ColumnBottom < GridColumns; ++ColumnBottom)
            {
                ++NumTreesBottom;

                int Tree = TreeGrid[Row][ColumnBottom];

                if (Tree >= CurrentTree)
                {
                    // This tree is as high as the current one,
                    // no more trees can be seen past this one
                    break;
                }
            }

            // Calculate scenic score of the current tree
            int ScenicScore = NumTreesLeft * NumTreesTop * NumTreesRight * NumTreesBottom;

            if(ScenicScore > HighestScenicScore)
            {
                HighestScenicScore = ScenicScore;
            }
        }
    }

    cout << HighestScenicScore << endl;

    // Free allocated memory
    for (int i = 0; i < NumRows; ++i)
    {
        delete[] TreeGrid[i];
    }
}