// a2_4_completeSubtree
// Dallas Hart
//
// Finds the height of the largest complete subtree in a complete binary tree

#include <iostream>

#define MAX(a, b, c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct output
{
    int treeOutput = 0;      // Tracks the best complete subtree that the node is the root of
    int bestSubTreeSize = 0; // Tracks the best complete subtree size underneath & possibly including itself
};

struct tree
{
    std::size_t position = 0;
    tree *left = nullptr;
    tree *right = nullptr;
    output maxSubtree()
    {
        // As it is a complete tree, only need to check one branch
        if (left != nullptr)
        {
            output leftMaxSubTree = left->maxSubtree();
            output rightMaxSubTree = right->maxSubtree();
            // Largest subtree where tree is the root node
            int selfTreeBest = MIN(leftMaxSubTree.treeOutput, rightMaxSubTree.treeOutput) + 1;

            // Largest subtree at or underneath tree
            int bestSubtreeSize = MAX(leftMaxSubTree.bestSubTreeSize, rightMaxSubTree.bestSubTreeSize, selfTreeBest);
            return {selfTreeBest, bestSubtreeSize};
        }
        else
        {
            return {1, 1};
        }
    }
};

void takeInput(tree *takeInputOf)
{
    std::string input;
    do
    {
        std::cout << "Does position " << takeInputOf->position << " have children? (y/n): ";
        std::cin >> input;
        if (input == "y")
        {
            // Add children and take value of children
            takeInputOf->left = new tree({takeInputOf->position * 2, nullptr, nullptr});
            takeInputOf->right = new tree({takeInputOf->position * 2 + 1, nullptr, nullptr});
            takeInput(takeInputOf->left);
            takeInput(takeInputOf->right);
            return;
        }
    } while (input != "n");
}

int main()
{
    tree *inputTree = new tree({1, nullptr, nullptr});
    takeInput(inputTree);
    std::cout << "Height of the largest subtree: " << inputTree->maxSubtree().bestSubTreeSize << std::endl;
}

/* 
******s-iMac:Assignment code ******$ ./out
Does position 1 have children? (y/n): y
Does position 2 have children? (y/n): y
Does position 4 have children? (y/n): y
Does position 8 have children? (y/n): y
Does position 16 have children? (y/n): n
Does position 17 have children? (y/n): y
Does position 34 have children? (y/n): n
Does position 35 have children? (y/n): n
Does position 9 have children? (y/n): y
Does position 18 have children? (y/n): n
Does position 19 have children? (y/n): n
Does position 5 have children? (y/n): n
Does position 3 have children? (y/n): y
Does position 6 have children? (y/n): n
Does position 7 have children? (y/n): y
Does position 14 have children? (y/n): y
Does position 28 have children? (y/n): y
Does position 56 have children? (y/n): y
Does position 112 have children? (y/n): y
Does position 224 have children? (y/n): n
Does position 225 have children? (y/n): n
Does position 113 have children? (y/n): n
Does position 57 have children? (y/n): y
Does position 114 have children? (y/n): y
Does position 228 have children? (y/n): y
Does position 456 have children? (y/n): n
Does position 457 have children? (y/n): n
Does position 229 have children? (y/n): y
Does position 458 have children? (y/n): n
Does position 459 have children? (y/n): n
Does position 115 have children? (y/n): n
Does position 29 have children? (y/n): y
Does position 58 have children? (y/n): y
Does position 116 have children? (y/n): n
Does position 117 have children? (y/n): y
Does position 234 have children? (y/n): y
Does position 468 have children? (y/n): n
Does position 469 have children? (y/n): n
Does position 235 have children? (y/n): n
Does position 59 have children? (y/n): y
Does position 118 have children? (y/n): n
Does position 119 have children? (y/n): n
Does position 15 have children? (y/n): n
Height of the largest subtree: 4
******s-iMac:Assignment code ******$ ./out
Does position 1 have children? (y/n): y
Does position 2 have children? (y/n): y
Does position 4 have children? (y/n): y
Does position 8 have children? (y/n): n
Does position 9 have children? (y/n): n
Does position 5 have children? (y/n): y
Does position 10 have children? (y/n): n
Does position 11 have children? (y/n): n
Does position 3 have children? (y/n): n
Height of the largest subtree: 3
******s-iMac:Assignment code ******$ ./out
Does position 1 have children? (y/n): y
Does position 2 have children? (y/n): n
Does position 3 have children? (y/n): n
Height of the largest subtree: 2
*/