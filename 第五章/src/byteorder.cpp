#include <iostream>
using namespace std;

void byteteorder()
{
    union
    {
        short value;
        char union_bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    if( (test.union_bytes[0] == 1) && (test.union_bytes[2] == 2) )
    {
        cout<<"数据是大端字节序"<<endl;
    }
    else if ((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    {
        cout<<"数据是小端字节序"<<endl;
    }
    else
    {
        cout<<"未知字节序"<<endl;
    }
    
}
int main()
{
    byteteorder();
    return 0;
}