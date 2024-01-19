/*Составить программу для сортировки массива данных методами: пузырьковой, отбора, вставки, Шелла и быстрой сортировки. Вывести на экран неупорядоченную (один раз) и упорядоченные (для каждого из методов) массивы данных. Составить сравнительную таблицу эффективности методов, в которой необходимо указать число сравнений и перестановок переменных в каждом методе сортировки.
Необходимо упорядочить каждую строку матрицы по возрастанию
Неупорядоченная матрица задается один раз случайным образом, далее она используется для каждого из методов сортировки.*/
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <algorithm>
#include <iomanip>
using namespace std;
 
 
vector<int> bubbleSort(vector<int> bVec, int& cmps, int& swps)
{
    for (int k = 0; k + 1 < bVec.size(); ++k)
    {
        for (int l = 0; l + 1 < bVec.size() - k; ++l)
        {
            cmps++;
            if (bVec[l] > bVec[l + 1])
            {
                swap(bVec[l], bVec[l + 1]);
                swps++;
            }
        }
        if (swps == 0)
        {
            break;
        }
    }
    return bVec;
}
 
 
vector<int> insertionSort(vector<int> iVec, int& cmps, int& swps)
{
    for (int i = 1; i < iVec.size(); ++i)
    {
        int tmp = iVec[i];
        int j = i;
        while (j > 0)
        {
            cmps++;
            if (iVec[j - 1] <= tmp)
            {
                break;
            }
            swps++;
            iVec[j] = iVec[j - 1];
            --j;
        }
        iVec[j] = tmp;
        //if (j != i)
        //{
 
        //}
 
 
    }
    return iVec;
}
 
 
vector<int> selectionSort(vector<int> selVec, int& cmps, int& swps)
{
    int i, j, min_index;
    for (i = 0; i < selVec.size() - 1; ++i)
    {
        min_index = i;
        for (j = i + 1; j < selVec.size(); ++j)
        {
            cmps++;
            if (selVec[j] < selVec[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(selVec[min_index], selVec[i]);
            swps++;
        }
    }
    return selVec;
}
 
 
vector<int> shellSort(vector<int> shellVec, int& cmps, int& swps)
{
    for (int step = shellVec.size() / 2; step > 0; step /= 2)
    {
        for (int i = step; i < shellVec.size(); ++i)
        {
            int tmp = shellVec[i];
            int j;
            for (j = i; j >= step; j -= step)
            {
                cmps++;
                if (shellVec[j - step] <= tmp)
                {
                    break;
                }
                shellVec[j] = shellVec[j - step];
                swps++;
            }
            shellVec[j] = tmp;
        }
    }
    return shellVec;
}
 
//функция определения опороного элемента(далее пивот) для квиксторта, на выходе индекс пивота, опороный берём в конце строки
int Partition(vector <int>& qVec, int start, int end, int& cmps, int& swps)
{
    int pivot = qVec[end];
    int j = end;
    for (int i = end - 1; i >= start; i--)
    {
        cmps++;
        if (qVec[i] > pivot)
        {
            //данный трюк с двумя свапами позволяет не считать свапы одинаковых элементов
            swap(qVec[i], qVec[j - 1]);
            swap(qVec[j], qVec[j - 1]);
            j--;
            swps++;
        }
    }
    return j;
}
 
 
vector <int> quickSort(vector<int>& qVec, int start, int end, int& cmps, int& swps)
{
    if (start < end)
    {
        int p = Partition(qVec, start, end, cmps, swps);
        quickSort(qVec, start, p - 1, cmps, swps);
        quickSort(qVec, p + 1, end, cmps, swps);
    }
    return qVec;
}
 
//вывод int 2d вектора
//перегрузку << преподаватель запретил :(
void output2d(vector<vector<int> > vecToOutput)
{
    for (int i = 0; i < vecToOutput.size(); i++)
    {
        for (int j = 0; j < vecToOutput[i].size(); j++)
        {
            cout << vecToOutput[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------------" << endl;
}
 
 //здесь функция для вывода красивой таблички
void tableOutput(vector<int> c, vector<int> s)
{
    cout << "            |Bubble|Insert|Select| Shell| Quicksort|" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Comparsions:|" << setw(6) << c[0] << "|" << setw(6) << c[1] << "|" << setw(6) << c[2] << "|" << setw(6) << c[3] << "|" << setw(10) << c[4] << "|" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "      Swaps:|" << setw(6) << s[0] << "|" << setw(6) << s[1] << "|" << setw(6) << s[2] << "|" << setw(6) << s[3] << "|" << setw(10) << s[4] << "|" << endl;
    cout << "----------------------------------------------------" << endl;
}
 
int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int n, m;
    cout << "H: " << endl;//количество строк
    cin >> n;
    cout << "W: " << endl;//длина строки
    cin >> m;
    if (m <= 0 || n <= 0)
    {
        cout << "Размерность введена неверно, оба числа должны быть больше 0" << endl;
        return -1;
    }
    vector<int> comparsions = { 0, 0, 0, 0, 0 };
    vector<int> swaps = { 0, 0, 0, 0, 0 };
    vector<vector<int> > myvect(n, vector<int>(m));
    vector<vector<int> > bubbleSortedArray;
    vector<vector<int> > insertionSortedArray;
    vector<vector<int> > selectionSortedArray;
    vector<vector<int> > shellSortedArray;
    vector<vector<int> > quickSortedArray;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            myvect[i][j] = rand() % 3 + 1; //сделано с целью увеличения шанса на повторение элементов
        }
    }
    cout << "Unsorted array: " << endl;
    output2d(myvect);
 
 
    for (int i = 0; i < myvect.size(); i++)
    {
        bubbleSortedArray.push_back(bubbleSort(myvect[i], comparsions[0], swaps[0]));
    }
    cout << "Bubble sorted array: " << endl;
    output2d(bubbleSortedArray);
 
 
 
    for (int i = 0; i < myvect.size(); i++)
    {
        insertionSortedArray.push_back(insertionSort(myvect[i], comparsions[1], swaps[1]));
    }
    cout << "Insertion sorted array: " << endl;
    output2d(insertionSortedArray);
 
 
 
    for (int i = 0; i < myvect.size(); i++)
    {
        selectionSortedArray.push_back(selectionSort(myvect[i], comparsions[2], swaps[2]));
    }
    cout << "Selection sorted array: " << endl;
    output2d(selectionSortedArray);
 
 
    for (int i = 0; i < myvect.size(); i++)
    {
        shellSortedArray.push_back(shellSort(myvect[i], comparsions[3], swaps[3]));
    }
    cout << "Shell sorted array: " << endl;
    output2d(shellSortedArray);
 
 
    for (int i = 0; i < myvect.size(); i++)
    {
        quickSortedArray.push_back(quickSort(myvect[i], 0, myvect[i].size() - 1, comparsions[4], swaps[4]));
    }
    cout << "Quicksorted array: " << endl;
    output2d(quickSortedArray);
 
 
    tableOutput(comparsions, swaps);
 
 

 
}
