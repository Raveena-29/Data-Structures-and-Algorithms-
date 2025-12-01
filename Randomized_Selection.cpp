#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = a;
}

int partition(vector<int> &arr, int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
// randomized selection function
int randomizedSelection(vector<int> &arr, int low, int high, int i)
{
    if (low == high)
    {
        return arr[low];
    }
    int pi = partition(arr, low, high);
    int k = pi + low - 1;
    if (i == k)
    {
        return arr[pi];
    }
    else if (i < k)
    {
        return randomizedSelection(arr, low, pi - 1, i);
    }
    else
    {
        return randomizedSelection(arr, pi + 1, high, i - k);
    }
}
void printArray(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main()
{
    srand(time(0));
    int n, i;
    cout << "Enter the number of elemnts: ";
    cin >> n;
    vector<int> arr(n);

    cout << " Enter the elements " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << " ORIGINAL ARRAY " << endl;
    printArray(arr, n);

    cout << "Enter i (to find the ith smallest element): ";
    cin >> i;
    if (i < 1 || i > n)
    {
        cout << "Invalid value" << endl;
    }

    int smallest = randomizedSelection(arr, 0, n - 1, i);

    cout << "The " << i << "th smallest element is " << smallest << endl;
    return 0;
}