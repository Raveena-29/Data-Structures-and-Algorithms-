#include <iostream>
using namespace std;

// B-Tree Node
class BTreeNode
{
public:
    int *keys;     // Array of keys
    int t;         // Minimum degree
    BTreeNode **C; // Children pointers
    int n;         // Current number of keys
    bool leaf;     // True if node is leaf

    BTreeNode(int _t, bool _leaf);

    void traverse();                      // Print tree
    BTreeNode *search(int k);             // Search key in tree
    void insertNonFull(int k);            // Insert when node not full
    void splitChild(int i, BTreeNode *y); // Split full child

    friend class BTree;
};

// B-Tree Class
class BTree
{
public:
    BTreeNode *root;
    int t; // Minimum degree

    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void insert(int k); // Insert key
    void traverse()
    {
        if (root)
            root->traverse();
    }
    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
};

// Constructor for B-Tree Node
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

// Traverse the tree
void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!leaf)
            C[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf)
        C[i]->traverse();
}

// Search a key
BTreeNode *BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (i < n && keys[i] == k)
        return this;

    if (leaf)
        return NULL;

    return C[i]->search(k);
}

// Insert when node is not full
void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Split a full child
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

// Insert key into B-Tree
void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

// Main Function
int main()
{
    int t;
    cout << "Enter minimum degree (t) of B-Tree: ";
    cin >> t;

    BTree tree(t);

    int n, value;
    cout << "Enter number of values to insert: ";
    cin >> n;

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        tree.insert(value);
    }

    cout << "\nB-Tree traversal: ";
    tree.traverse();
    cout << endl;

    int key;
    cout << "\nEnter key to search: ";
    cin >> key;

    if (tree.search(key))
        cout << "Key found in the B-Tree\n";
    else
        cout << "Key not found\n";

    return 0;
}
