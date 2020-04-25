// CrazyTrain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct S
{
    int code;
    int count; 
};


struct TreeNode
{
    int value;
    TreeNode * parent;
    TreeNode * left;
    TreeNode * right;
};



bool wayToSort(const S & s1, const S & s2)
{ return s1.count < s2.count; }

int main(int argc, char * argv[])
{
    string txt;
    if (argc == 1)
       std::cin >> txt;
    else
        txt = argv[1];

    std::vector<S> s(256);
    for (int j = 0; j < 256; j++) { s[j].code = j; s[j].count = 0; }
    for (size_t c = 0; c < txt.length(); c++)
    {
        int idx = txt[c];
        s[idx].count++;
    }
    //std::sort(s.begin(), s.end(), wayToSort);

    std::vector<TreeNode*> nodes;
    for (int idx=0; idx<256; idx++)
    {
        if (s[idx].count > 0)
        {
            TreeNode * n = new TreeNode;
            n->left = nullptr;
            n->right = nullptr;
            n->parent = nullptr;
            n->value = s[idx].count;
            nodes.push_back(n);
        }
    }

    while (nodes.size() > 1)
    {
        int left = 0;
        int right = 1;

        for (int idx=2; idx<nodes.size(); idx++)
        {
            if ((nodes[idx]->value < nodes[left]->value) ||
                (nodes[idx]->value < nodes[right]->value))
            {
                if (nodes[left]->value > nodes[right]->value)
                    left = idx;
                else
                    right = idx;
            }
        }

        if (nodes[left]->value < nodes[right]->value)
            std::swap(left, right);

        TreeNode * n = new TreeNode;
        n->parent = nullptr;
        n->left = nodes[left];
        n->right = nodes[right];
        n->value = nodes[left]->value + nodes[right]->value;
        nodes[left]->parent = n;
        nodes[right]->parent = n;

        if (left > right)
            std::swap(left, right);

        nodes.erase(nodes.begin() + right);
        nodes[left] = n;
    }

    /*
    int d = 0;
    for (int g = 0; g < 256; g++ ) 
    {
        if (s[g].count > 0) 
        { 
            std::cout << (char)s[g].code << " is written " << s[g].count << " times.\n"; 
            d++; 
            std::cout << "elements - " << d;
        }
    }
    */
    std::cout << "Ku\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
