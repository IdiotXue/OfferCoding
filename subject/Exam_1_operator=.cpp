#include <iostream>
#include <cstring>
using namespace std;

class CMyString
{
    friend ostream &operator<<(ostream &out, const CMyString &str)
    {
        out << str.m_pData;
        return out;
    }

  public:
    CMyString(const char *pData = nullptr) : m_pData(nullptr)
    {
        if (pData != nullptr)
        {
            //strlen不包括‘\0’
            m_pData = new char[strlen(pData) + 1];
            strcpy(m_pData, pData);
        }
    }
    CMyString(const CMyString &str) : m_pData(nullptr)
    {
        if (str.m_pData != nullptr)
        {
            //strlen不包括‘\0’
            m_pData = new char[strlen(str.m_pData) + 1];
            strcpy(m_pData, str.m_pData);
        }
    }
    CMyString &operator=(const CMyString &);
    ~CMyString()
    {
        delete m_pData;
        m_pData = nullptr;
    }

  private:
    char *m_pData;
};
//最好再声明一次，外部函数才能调用
ostream &operator<<(ostream &out, const CMyString &str);

CMyString &CMyString::operator=(const CMyString &rhs)
{
    //考点1：返回引用，才能连续赋值str1=str2=str3
    //考点2：传入参数类型为常量引用，避免调用复制构造和函数内改变rhs
    //考点3：判断传入rhs和当前this是否为同一实例，避免释放自身空间
    if (this != &rhs)
    {
        //考点4：创建临时实例，交换空间，出if后自动释放，指针tmp不会释放
        //这种做法是异常安全的(delete/new之间发送分配空间异常CMyString
        //无法保持有效状态)
        CMyString tmpString(rhs);
        char *tmp = m_pData;
        m_pData = tmpString.m_pData;
        tmpString.m_pData = tmp;
    }
    return *this;
}
int main(int argc, char *argv[])
{
    //测试1.赋值
    CMyString a("abc");
    CMyString b("haha");
    cout << a << " " << b << endl;
    b = a;
    cout << b << endl;
    //测试2.自赋值
    a = a;
    cout << a << endl;
    //测试3.连续赋值
    CMyString c("good");
    a = b = c;
    cout << a << " " << b << " " << c << endl;
}