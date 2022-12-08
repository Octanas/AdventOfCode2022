#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

// Graph node struct that will represent a folder or a file
struct Node
{
public:
    // Folders and files inside folder
    vector<Node *> Children;

    // Size of folder or file
    int Size;

    // Name of the folder or file
    string Name;

    Node(string InName, int InSize)
        : Children(), Size(InSize), Name(InName)
    {
    }
};

// Recursively gets the sum of the size of the children of a folder
int UpdateFolderSize(Node *Root)
{
    for (int i = 0; i < Root->Children.size(); ++i)
    {
        Root->Size += UpdateFolderSize(Root->Children[i]);
    }

    return Root->Size;
}

// Recursively gets the sum of the size of the folders with at most 100000 bytes of size
// Sum the size of the curret folder (if it has at most 100000)
// to the sum of size of its child folders (the ones that have at most 100000)
int GetSizeSum(Node *Root)
{
    int SizeSum = 0;

    if (Root->Children.size() > 0)
    {
        SizeSum = Root->Size <= 100000 ? Root->Size : 0;

        for (int i = 0; i < Root->Children.size(); ++i)
        {
            SizeSum += GetSizeSum(Root->Children[i]);
        }
    }

    return SizeSum;
}

int main()
{
    string StrConsole;
    ifstream MyReadFile("input.txt");

    // Root of the file system
    Node *Head = new Node("/", 0);

    // This stack will contain the history of accessed folders,
    // so we know where to go back to when the 'cd ..' command is called.
    // Top of stack will be the current folder
    stack<Node *> CallStack;

    bool ListingDirectory = false;

    // Parse commands and build file tree
    while (getline(MyReadFile, StrConsole))
    {
        if (StrConsole == "$ ls")
        {
            // Probably unnecessary parsing 'ls' commands,
            // but will keep for completeness sake
            ListingDirectory = true;
        }
        else if (StrConsole.substr(0, 5) == "$ cd ")
        {
            ListingDirectory = false;

            string Dir = StrConsole.substr(5);

            if (Dir == "/")
            {
                // Go back to root.
                // Empty stack and push root node
                while (!CallStack.empty())
                {
                    CallStack.pop();
                }

                CallStack.push(Head);
            }
            else if (Dir == "..")
            {
                // Go to parent folder of current folder.
                // Pop the current folder of the stack
                CallStack.pop();
            }
            else
            {
                // Enter specific folder
                // Search for folder in children of current folder and push it to the stack
                Node *CurrentFolder = CallStack.top();

                for (int i = 0; i < CurrentFolder->Children.size(); ++i)
                {
                    if (CurrentFolder->Children[i]->Name == Dir)
                    {
                        CallStack.push(CurrentFolder->Children[i]);
                        break;
                    }
                }
            }
        }
        else if (ListingDirectory)
        {
            // Add new directories or files to the file tree, under the current folder (top of stack)
            if (StrConsole.substr(0, 4) == "dir ")
            {
                string FolderName = StrConsole.substr(4);

                Node *CurrentFolder = CallStack.top();
                CurrentFolder->Children.push_back(new Node(FolderName, 0));
            }
            else
            {
                int SeparatorIndex = StrConsole.find(' ');

                string SizeString = StrConsole.substr(0, SeparatorIndex);
                int Size = stoi(SizeString);

                string FileName = StrConsole.substr(SeparatorIndex + 1);

                Node *CurrentFolder = CallStack.top();
                CurrentFolder->Children.push_back(new Node(FileName, Size));
            }
        }
    }

    MyReadFile.close();

    // Calculate size of each folder in the tree, according to its children
    UpdateFolderSize(Head);

    // Get the sum of the size of all folders with at most 100000 bytes of size
    int SizeSum = GetSizeSum(Head);
    cout << SizeSum << endl;
}