# 主机字节序和网络字节序
现代CPU一次能处理4字节(32位机)，这四个字节排列顺序会影响其在寄存器中的整数值。
大端字节序：高位字节存储在内存的低地址端，低位字节存储在内存的高地址端。
小端字节序：低位字节存储在内存的低地址端，高位字节存储在内存的高地址端。
现代PC多采用小端字节序，因此小端字节序又称为主机字节序。
Linux提供以下几个函数进行主机字节序和网络字节序的转换：
```C++
#include <netinet/in.h>
unsigned long int htonl (unsigned long int hostlong);//h means host;nl means network long
unsigned short int htos (unsigned short int hostshort);
unsigned long int ntohl (unsigned long int netlong);
unsigned short int ntohs (unsigned short int netshort);
```
四个函数中，长整形函数用来转换IP地址，短整形函数用来转换端口号。

# 通用socket地址
