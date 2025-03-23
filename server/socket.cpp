#include "socket.h"

/**
 * @brief 构造一个新的 Socket 对象
 * 
 * @param domain 套接字域，指定通信的协议族（如 AF_INET 表示 IPv4）
 * @param type 套接字类型，指定通信的语义（如 SOCK_STREAM 表示 TCP）
 * 
 * @details 这个构造函数创建一个新的套接字。它使用给定的域和类型参数调用系统的 socket() 函数，
 *          并将返回的文件描述符存储在 sockfd 成员变量中。协议参数被设置为0，表示使用指定域和类型的默认协议。
 */
 Socket::Socket(Domain domain, Type type)
            :domain(domain), type(type)
{
    sockfd = ::socket(domain,type,0);
}

/**
 * @brief Socket 类的析构函数
 * 
 * @details 这个析构函数负责在 Socket 对象被销毁时关闭套接字。
 *          它调用 close() 函数来关闭由 sockfd 成员变量表示的文件描述符。
 *          这确保了在对象生命周期结束时，系统资源被正确释放，防止资源泄漏。
 */
Socket::~Socket()
{
    close();
}

void Socket::close()
{
    ::close(this->sockfd);
}
/**
 * @brief 将套接字绑定到指定的 IP 地址和端口
 * 
 * @param ip 要绑定的 IP 地址。如果为空字符串，则绑定到所有可用接口（INADDR_ANY）
 * @param port 要绑定的端口号
 * @return int 成功返回 0，失败返回 -1
 * 
 * @details 此函数创建一个 sockaddr_in 结构体，设置地址族、IP 地址和端口，
 *          然后调用系统的 bind() 函数将套接字与这个地址关联。
 *          如果 IP 参数为空，则绑定到所有可用接口（INADDR_ANY）。
 *          端口号会被转换为网络字节序。
 */
int Socket::bind(std::string ip,int port)
{
    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family = this->domain;
    if(ip.empty())
    {
        address.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    inet_pton(this->domain,ip.c_str(),&address.sin_addr);
    address.sin_port = htons(port);
    return ::bind(this->sockfd,(struct sockaddr*)&address,sizeof(address)); 
}

/**
 * @brief 使套接字进入监听状态
 * 
 * @param backlog 待处理连接队列的最大长度，默认值为5
 * @return int 成功返回0，失败返回-1
 * 
 * @details 此函数将套接字置于监听模式，准备接受传入的连接请求。
 *          backlog参数指定了操作系统可以保持在队列中的待处理连接的最大数量。
 *          如果队列满了，新的连接请求可能会被拒绝。
 *          该函数实际上是对系统调用listen()的封装。
 */
int Socket::listen(int backlog = 5)
{
    return ::listen(this->sockfd,backlog);
}

/**
 * @brief 连接到指定的服务器
 * 
 * @param ip 服务器的 IP 地址
 * @param port 服务器的端口号
 * @return int 成功返回 0，失败返回 -1
 * 
 * @details 此函数尝试建立与指定 IP 地址和端口的服务器的连接。
 *          它创建一个 sockaddr_in 结构体来存储服务器地址信息，
 *          然后调用系统的 connect() 函数来建立连接。
 *          IP 地址会被转换为网络字节序，端口号也会被转换为网络字节序。
 * 
 * @note 这个函数是阻塞的，会等待直到连接建立或发生错误。
 *       如果需要非阻塞连接，应考虑使用其他方法或设置套接字为非阻塞模式。
 */
int Socket::accept(struct sockaddr_in* client = nullptr,socklen_t* len = nullptr)
{
    return ::accept(this->sockfd,(struct sockaddr*)client,len);
}

/**
 * @brief 接受一个新的客户端连接
 * 
 * @param client 指向 sockaddr_in 结构的指针，用于存储客户端地址信息。可以为 nullptr
 * @param len 指向 socklen_t 的指针，用于存储地址长度。可以为 nullptr
 * @return int 成功时返回新连接的文件描述符，失败时返回 -1
 * 
 * @details 此函数尝试接受一个挂起的连接。如果没有挂起的连接，函数将阻塞直到有新的连接到来。
 *          如果 client 和 len 参数为 nullptr，函数仍会接受连接，但不会返回客户端的地址信息。
 *          这个函数是对系统调用 accept() 的封装，提供了更灵活的接口。
 * 
 * @note 使用默认参数 nullptr 允许调用者选择是否接收客户端信息。
 *       这种设计与底层 Linux API 的行为一致，提供了更大的灵活性。
 */
int Socket::connect(std::string ip,int port)
{
    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family = this->domain;
    inet_pton(this->domain,ip.c_str(),&address.sin_addr);
    address.sin_port = htons(port);
    return ::connect(this->sockfd,(struct sockaddr*)&address,sizeof(address));
}