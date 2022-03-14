#include <iostream>
using namespace std;

void convertHeap(int array[], int len, int x)
{
    int largest = x;
    int left = 2 * x + 1;
    int right = 2 * x + 2;

    if (left < len && array[left] > array[largest])
        largest = left;

    if (right < len && array[right] > array[largest])
        largest = right;

    if (largest != x)
    {
        swap(array[x], array[largest]);

        convertHeap(array, len, largest);
    }
}

void heapSort(int array[], int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
        convertHeap(array, len, i);

    for (int i = len - 1; i >= 0; i--)
    {
        swap(array[0], array[i]);
        convertHeap(array, i, 0);
    }
}

void display(int array[], int len)
{
    cout << "After sorting, the array is: \n";
    for (int i = 0; i < len; ++i)
        cout << array[i] << " ";
    cout << endl;
}

void show(){
    int len;
	int arr[100] = { 0 };
    cout << "enter number of elements " << endl << endl;
	cin >> len;
	cout << "enter elements" << endl << endl;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}

    heapSort(arr, len);
    display(arr, len);
}


int main(){
    show();
    return 0;
}
