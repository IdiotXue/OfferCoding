#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
using std::vector;
using std::string;
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;

/**
 * istringstream和getline做文件读写
 */
int main(int argc, char *argv[])
{
    string line, phone, name;
    map<string, vector<string>> mapNameToPhone;
    // istringstream iRecord; //注释了写法二,感觉没必要多写几行
    while (getline(cin, line))
    {
        istringstream iRecord(line);
        // iRecord.str(line);
        // iRecord.clear(); //清除eof位,因为上一个循环已经到末尾了
        iRecord >> name;
        while (iRecord >> phone)
            mapNameToPhone[name].push_back(phone);
    }
    for (const auto &x : mapNameToPhone)
    {
        cout << x.first << '\t';
        for (const auto &phone : x.second)
            cout << phone << '\t';
        cout << endl;
    }
    return 0;
}

/**
 * file: test.in
 * morgan 12354 2341412
 * drew 789087
 * lee 3129487 239487 12380
 * 
 * ./bin/work < test.in
 */