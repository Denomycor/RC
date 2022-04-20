#pragma once

#include <sys/socket.h>
#include <netdb.h>

class CommunicationSocket {
public:

    CommunicationSocket() = delete;
    CommunicationSocket(const CommunicationSocket&) = delete;
    CommunicationSocket& operator=(const CommunicationSocket&) = delete;

    CommunicationSocket(int sockfd, sockaddr addr, socklen_t len);

    ~CommunicationSocket();

    bool invalid() const noexcept;

    int send(const void* msg, int len, int flags) const;

    int recv(void* buff, int len, int flags) const;

    int sendto(const void* msg, int len, int flags, const sockaddr* to, socklen_t tolen) const;

    int recvfrom(void* buff, int len, int flags, sockaddr* from, socklen_t* fromlen) const;

    int getpeername(sockaddr& addr, socklen_t& len);

protected:
    const int m_sockfd;
    const sockaddr m_addr;
    const socklen_t m_len;
};

class Socket final : public CommunicationSocket {
public:

    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(int sockfd, addrinfo* llist);

    ~Socket();

    static Socket make_socket(const char* name, const char* service, const addrinfo& hints);

    int bind();

    int connect();

    int listen(int backlog);

    CommunicationSocket accept();

private:
    addrinfo*const specs_ll;
};
