#include <iostream>
#include <vector>
using namespace std;

// Function to create LPS (Longest Prefix Suffix) array
void computeLPS(string pattern, vector<int> &lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pattern.length())
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP pattern matching function
void KMPsearch(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m);
    computeLPS(pattern, lps);

    int i = 0, j = 0; // i → text index, j → pattern index

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main()
{
    string text, pattern;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern to search: ";
    getline(cin, pattern);

    cout << "\nSearching using KMP algorithm...\n";
    KMPsearch(text, pattern);

    return 0;
}
