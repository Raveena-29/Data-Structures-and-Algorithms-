#include <iostream>
#include <map>
using namespace std;

// Trie Node for Suffix Tree
class Node
{
public:
    map<char, Node *> children;
    bool isEnd;
    Node()
    {
        isEnd = false;
    }
};

class SuffixTree
{
private:
    Node *root;

public:
    SuffixTree()
    {
        root = new Node();
    }

    // Insert a suffix into the suffix tree
    void insertSuffix(string s)
    {
        Node *current = root;
        for (char ch : s)
        {
            if (current->children.find(ch) == current->children.end())
                current->children[ch] = new Node();
            current = current->children[ch];
        }
        current->isEnd = true;
    }

    // Build suffix tree using brute force
    void buildTree(string text)
    {
        for (int i = 0; i < text.length(); i++)
            insertSuffix(text.substr(i));
    }

    // Search if pattern exists in suffix tree
    bool search(string pattern)
    {
        Node *current = root;
        for (char ch : pattern)
        {
            if (current->children.find(ch) == current->children.end())
                return false;
            current = current->children[ch];
        }
        return true;
    }
};

int main()
{
    string text, pattern;

    cout << "Enter text: ";
    getline(cin, text);

    SuffixTree st;
    st.buildTree(text);

    cout << "Enter pattern to search: ";
    getline(cin, pattern);

    if (st.search(pattern))
        cout << "\nPattern FOUND in text.\n";
    else
        cout << "\nPattern NOT FOUND in text.\n";

    return 0;
}
