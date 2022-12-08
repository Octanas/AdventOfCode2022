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

    // Initialize number of visible trees with the number of trees on the edge of the grid
    int NumVisibleTrees = GridColumns * 2 + (GridRows - 2) * 2;

    // Iterate through every tree not in the edges
    for (int Row = 1; Row < GridRows - 1; ++Row)
    {
        for (int Column = 1; Column < GridColumns - 1; ++Column)
        {
            int CurrentTree = TreeGrid[Row][Column];

            int HighestTreeLeft = 0;
            int HighestTreeTop = 0;
            int HighestTreeRight = 0;
            int HighestTreeBottom = 0;

            // Check the if there are trees as high as the current one to the left
            for (int RowLeft = 0; RowLeft < Row; ++RowLeft)
            {
                int Tree = TreeGrid[RowLeft][Column];

                if (Tree > HighestTreeLeft)
                {
                    HighestTreeLeft = Tree;

                    if (HighestTreeLeft >= CurrentTree)
                    {
                        break;
                    }
                }
            }

            // Check the if there are trees as high as the current one on top
            for (int ColumnTop = 0; ColumnTop < Column; ++ColumnTop)
            {
                int Tree = TreeGrid[Row][ColumnTop];

                if (Tree > HighestTreeTop)
                {
                    HighestTreeTop = Tree;

                    if (HighestTreeTop >= CurrentTree)
                    {
                        break;
                    }
                }
            }

            // Check the if there are trees as high as the current one to the right
            for (int RowRight = Row + 1; RowRight < GridRows; ++RowRight)
            {
                int Tree = TreeGrid[RowRight][Column];

                if (Tree > HighestTreeRight)
                {
                    HighestTreeRight = Tree;

                    if (HighestTreeRight >= CurrentTree)
                    {
                        break;
                    }
                }
            }

            // Check the if there are trees as high as the current one on the bottom
            for (int ColumnBottom = Column + 1; ColumnBottom < GridColumns; ++ColumnBottom)
            {
                int Tree = TreeGrid[Row][ColumnBottom];

                if (Tree > HighestTreeBottom)
                {
                    HighestTreeBottom = Tree;

                    if (HighestTreeBottom >= CurrentTree)
                    {
                        break;
                    }
                }
            }

            // If there are no tree as high as this one in any of the directions, this tree is visible
            if (HighestTreeLeft < CurrentTree || HighestTreeTop < CurrentTree || HighestTreeRight < CurrentTree || HighestTreeBottom < CurrentTree)
            {
                ++NumVisibleTrees;
            }
        }
    }

    cout << NumVisibleTrees << endl;

    // Free allocated memory
    for (int i = 0; i < NumRows; ++i)
    {
        delete[] TreeGrid[i];
    }
}