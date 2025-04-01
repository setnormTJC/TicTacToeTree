// Work I did a few months ago.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"TicTacToe.h"
#include"Tree.h"


#include <iostream>

int main()
{
	TicTacToe ttt; 

	TicTacToeTree tttTree(ttt.boardData);

	//std::cout << tttTree.rootNode << "\n";

	constexpr int desiredDepth = 5; 

	tttTree.generateGameTreeRecursively(
		tttTree.rootNode,
		ttt.boardData,
		0,
		5);

	std::cout << "\n\nNumber of nodes in tree with depth =  " << desiredDepth << " = "
		<< tttTree.totalNodeCount << "\n";

	std::cout << "\n\nChild at \"left\", \"left\" :\n";
	auto pLeftLeft = tttTree.rootNode.childrenLinks.at(0)->childrenLinks.at(0);

	std::cout << *(pLeftLeft) << "\n"; //Note the dereferencing operator

	//tttTree.BFSPrintTree(); 
}

