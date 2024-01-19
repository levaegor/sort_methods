#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include <algorithm>
using namespace std;
 
 
bool find2Symbols(string vecToSearch, string subStr)
{
    for (int i = 0; i < vecToSearch.size() - 1; i++)
    {
        if (vecToSearch[i] == subStr[1])
        {
            for (int j = 0; j < vecToSearch.size(); j++)
            {
                if (vecToSearch[j] == subStr[0])
                {
                    return true;
                }
            }
        }
        else if (vecToSearch[i] == subStr[0])
        {
            for (int j = 0; j < vecToSearch.size(); j++)
            {
                if (vecToSearch[j] == subStr[1])
                {
                    return true;
                }
            }
        }
    }
    return false;
}
 
 
vector<int> linearSearch(vector<string> vecToSearch, int length, string hintRow, vector<string>& found)
{
    vector<int> index;
    for (int i = 0; i < vecToSearch.size(); i++)
    {
        if (vecToSearch[i].size() != length)
        {
            continue;
        }
        if (find2Symbols(vecToSearch[i], hintRow))
        {
            index.push_back(i);
            found.push_back(vecToSearch[i]);
        }
    }
    return index;
}
 
 
vector<int> returnStringSize(vector<string> stringsToSize)
{
    vector<int> sizeVec;
    for (int j = 0; j < stringsToSize.size(); j++)
    {
        sizeVec.push_back(stringsToSize[j].size());
    }
    return sizeVec;
}
 
 
int binarySearchForSizes(vector<int> intVec, int start, int end, int length)
{
    sort(intVec.begin(), intVec.end());
    while (start <= end)
    {
        int middle = start + (end - start) / 2;
        if (intVec[middle] == length)
        {
            return length;
        }
        if (length > intVec[middle])
        {
            end = middle - 1;
        }
        else
        {
            start = middle + 1;
        }
    }
    return -1;
}
 
 
int entriesFromBinarySearchedSizeVector(int foundSize, vector<string> stringVec, string hintRow)
{
    int cntr = 0;
    for (int i = 0; i < stringVec.size(); i++)
    {
        if (stringVec[i].size() == foundSize)
        {
            if (find2Symbols(stringVec[i], hintRow))
            {
                cntr++;
            }
        }
    }
    return cntr;
}
 
 
vector<string> splitStr(string strToSplit)
{
    char separator = ' ';
    vector<string> splittedStr;
    string tmp;
    for (int i = 0; i < strToSplit.size(); i++)
    {
        if (strToSplit[i] == separator)
        {
            if (tmp != "")
            {
                splittedStr.push_back(tmp);
                tmp = "";
            }
            continue;
        }
        tmp += strToSplit[i];
    }
    if (tmp.size() != 0)
    {
        splittedStr.push_back(tmp);
    }
    return splittedStr;
}
 
 
void outputStr1dVec(vector<string> strVec)
{
    for (int i = 0; i < strVec.size(); i++)
    {
        cout << strVec[i] << endl;
    }
}
 
 
void outputInt1dVec(vector<int> intVec)
{
    for (int i = 0; i < intVec.size(); i++)
    {
        cout << intVec[i] << endl;
    }
}
 
 
int main()
{
    setlocale(LC_CTYPE, "ru");
    string a, hint;
    int len;
    vector<string> foundWords;
    cout << "Введите текст: " << endl;
    getline(cin, a);
    cout << "Введите длину слова: " << endl;
    cin >> len;
    if (len < 2)
    {
        cout << "Минимальная длина слова должна быть равна 2" << endl;
        return -1;
    }
    cout << "Введите две буквы: " << endl;
    cin >> hint;
    if (hint.size() > 2)
    {
        cout << "Можно ввести только два символа" << endl;
        return -1;
    }
    vector <string> res = splitStr(a);
    vector<int> sizeVector = returnStringSize(res);
    int fSize = binarySearchForSizes(sizeVector, 0, sizeVector.size() - 1, len);
    int counter = entriesFromBinarySearchedSizeVector(fSize, res, hint);
    vector<int> res_linear = linearSearch(res, len, hint, foundWords);
    if (counter == 0)
    {
        cout << "По Вашему шаблону не было найдено слов" << endl;
        return -1;
    }
    cout << "Найдено слов по заданному шаблону: " << endl << counter << endl;
    cout << "Найденные слова: " << endl;
    outputStr1dVec(foundWords);
    cout << "Индексы найденных слов по заданному шаблону: " << endl;
    outputInt1dVec(res_linear);
 
 
    return 0;
}
