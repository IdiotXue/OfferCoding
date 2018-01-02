#include <iostream>
using namespace std;

/**
 * union的特性：多个不同类型的数据共享同一块地址，
 *             同一时间只能存一个成员
 */
union ByteOrder {
    short value;
    char byte[sizeof(short)];
};
/**
 * 利用union特性判断系统的字节序是大端还是小端
 */
int main(int argc, char *argv[])
{
    ByteOrder bo;
    bo.value = 0x0102; //给一个short填满所有byte
    cout << "short size:" << sizeof(short) << " bytes" << endl;
    cout << "char array size：" << sizeof(bo.byte) << endl;
    //利用union的特性，判断系统的字节序
    if (bo.byte[0] == 0x01 && bo.byte[1] == 0x02)
        cout << "big endian" << endl; //低地址存高有效位
    else if (bo.byte[0] == 0x02 && bo.byte[1] == 0x01)
        cout << "small endian" << endl; //低地址存地有效为位
    else
        cout << "unknown" << endl;
    return 0;
}