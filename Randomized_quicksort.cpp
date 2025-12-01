#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

// To count the number of comparisons
int comparisons = 0;

// function to swap values
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
// Partition function using random pivot
int partition(vector<int> &arr, int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); // Move random pivot to end

    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        comparisons++;

        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort function

void randomizedQuiksort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        randomizedQuiksort(arr, low, pi - 1);
        randomizedQuiksort(arr, pi + 1, high);
    }
}

void printarray(vector<int> &arr, int n)
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
    int n;
    cout << "Enter the number of elements in the arr" << endl;
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements :  \n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "ORIGINAL ARRAY" << endl;
    printarray(arr, n);

    randomizedQuiksort(arr, 0, n - 1);
    cout << "SORTED ARRAY" << endl;
    printarray(arr, n);

    cout << "\nTotal number of comparisons: " << comparisons << endl;

    return 0;
}