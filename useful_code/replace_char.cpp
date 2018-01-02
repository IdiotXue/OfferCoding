#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

bool IsOver(vector<int> &num)
{
    bool bIsOver = false;
    int nCarryBit = 0, nBitSum = 0;
    for (int i = num.size() - 1; i >= 0; --i)
    {
        nBitSum = num[i] + nCarryBit;
        if (i == num.size() - 1)
            ++nBitSum;
        if (nBitSum >= 2) // 进位
        {
            if (i == 0) //溢出
                bIsOver = true;
            else
            {
                nCarryBit = 1;
                num[i] = nBitSum - 2;
            }
        }
        else
        {
            num[i] += 1;
            break;
        }
    }
    return bIsOver;
}

int main(int argc, char const *argv[])
{
    string str;
    char oc, nc;

    while (cin >> str >> oc >> nc)
    {
        vector<int> vnIndex;
        int diff = 'a' - 'A';
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (str[i] == oc || str[i] == (oc - diff) || str[i] == (oc + diff))
                vnIndex.push_back(i);
        }
        vector<int> binary(vnIndex.size(), 0);
        cout << str << ',';
        int times = pow(2, vnIndex.size());
        for (int i = 1; i < times; ++i)
        {
            IsOver(binary);
            string temp = str;
            for (size_t i = 0; i < vnIndex.size(); ++i)
            {
                if (binary[i])
                    temp[vnIndex[i]] = nc;
            }
            cout << temp;
            if (i == times - 1)
                break;
            cout << ',';
        }
        cout << endl;
    }
}