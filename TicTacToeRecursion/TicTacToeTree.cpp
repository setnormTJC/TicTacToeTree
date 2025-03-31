#include <array>
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>

// Using vector of vectors to represent the Tic-Tac-Toe board
using TTTgameboard = std::vector<std::vector<char>>;

/*
 * Function to print multiple boards on the same row
 * @param boards -> vector of game boards to be printed
 * @param offset -> offset for centering or spacing (if needed)
 */
auto printBoardRow(const std::vector<TTTgameboard>& boards, const int offset)
{
    // Print each row of each board
    for (int row = 0; row < 3; ++row)
    {
        // For each board in the row, print the current row of the board
        for (const auto& board : boards)
        {
            std::cout << std::setw(offset);
            std::cout << std::setfill(' ');
            for (int col = 0; col < 3; ++col)
                std::cout << board[row][col] << " ";
        }
        std::cout << "\n";
    }
}

/* Generate level one children boards where 'X' will be placed at different positions */
std::vector<TTTgameboard> getLevelOneChildrenBoards(const TTTgameboard& parentBoard)
{
    constexpr int numberOfChildren = 9;
    std::vector<TTTgameboard> levelOneChildrenBoards(numberOfChildren);

    // Generate boards with 'X' placed at different positions
    int currentChildNumber = 0;
    for (int row = 0; row < parentBoard.size(); ++row)
    {
        for (int col = 0; col < parentBoard.at(0).size(); ++col)
        {
            levelOneChildrenBoards.at(currentChildNumber) = parentBoard;
            levelOneChildrenBoards.at(currentChildNumber).at(row).at(col) = 'X';

            currentChildNumber++;
        }
    }

    return levelOneChildrenBoards;
}


void demoTreeOfDepthOne()
{
    /* The empty starting board: */
    TTTgameboard emptyStartingBoard =
    {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    constexpr int roughlyTerminalWidth = 90;
    printBoardRow({ emptyStartingBoard }, roughlyTerminalWidth / 2); // Roughly center the parent (root)

    auto levelOneChildrenBoards = getLevelOneChildrenBoards(emptyStartingBoard);

    // Print all child boards in a single row
    constexpr int spaceBetweenBoards = 6;  //will need to play with this depending on terminal settings...
    std::cout << "\n\n\n";
    printBoardRow(levelOneChildrenBoards, spaceBetweenBoards);

}


struct GameTreeNode
{
    TTTgameboard currentGameBoard;
    std::vector<std::unique_ptr<GameTreeNode>> childrenBoardLinks;
};

int main()
{
    /* The empty starting board: */
    TTTgameboard emptyStartingBoard =
    {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    auto pRoot = std::make_unique<GameTreeNode>();
    pRoot->currentGameBoard = emptyStartingBoard;

    printBoardRow({ emptyStartingBoard }, 40); //print the starting board 


    auto levelOneChildren = getLevelOneChildrenBoards(emptyStartingBoard);
    std::cout << "\n\n\n";
    printBoardRow(levelOneChildren, 6); //prints all of the possible first moves 


    /*Insert children into the tree*/
    for (const auto& levelOneChild : levelOneChildren)
    {
        auto pLevelOneChild = std::make_unique<GameTreeNode>();
        pLevelOneChild->currentGameBoard = levelOneChild;

        pRoot->childrenBoardLinks.push_back(std::move(pLevelOneChild));
    }

    std::cout << "\n\nEnter the child number you want to see: \n";
    int desiredChildNumber; 
    std::cin >> desiredChildNumber; 

    auto desiredChildBoard = pRoot->childrenBoardLinks.at(desiredChildNumber).get()->currentGameBoard; 

    std::cout << "\n\n";
    printBoardRow({ desiredChildBoard }, 0);

    return 0;
}
