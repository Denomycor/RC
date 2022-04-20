#include "socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


CommunicationSocket::CommunicationSocket(int sockfd, sockaddr addr, socklen_t len)
    :m_sockfd(sockfd), m_addr(addr), m_len(len)
{}

CommunicationSocket::~CommunicationSocket(){
    if(m_sockfd != -1) close(m_sockfd);
}

bool CommunicationSocket::invalid() const noexcept {
    return m_sockfd == -1;
}

int CommunicationSocket::send(const void* msg, int len, int flags) const {
    return ::send(m_sockfd, msg, len, flags);
}

int CommunicationSocket::recv(void* buff, int len, int flags) const {
    return ::recv(m_sockfd, buff, len, flags);
}

int CommunicationSocket::sendto(const void* msg, int len, int flags, const sockaddr* to, socklen_t tolen) const{
    return ::sendto(m_sockfd, msg, len, flags, to, tolen);
}

int CommunicationSocket::recvfrom(void* buff, int len, int flags, sockaddr* from, socklen_t* fromlen) const {
    return ::recvfrom(m_sockfd, buff, len, flags, from, fromlen);
}

int CommunicationSocket::getpeername(sockaddr& addr, socklen_t& len){
    return ::getpeername(m_sockfd, &addr, &len);
}



Socket::Socket(int sockfd, addrinfo* llist)
    : CommunicationSocket(sockfd, *llist->ai_addr, llist->ai_addrlen), specs_ll(llist)
{}

Socket::~Socket(){
    if(specs_ll != nullptr) freeaddrinfo(specs_ll);
}

Socket Socket::make_socket(const char* name, const char* service, const addrinfo& hints){
    addrinfo* specs_ll;

    if(getaddrinfo(name, service, &hints, &specs_ll) != 0){
        specs_ll = nullptr;
    }
    
    int sockfd;

    if(specs_ll == nullptr){
        sockfd = -1;
    }else{
        sockfd = socket(specs_ll->ai_family, specs_ll->ai_socktype, specs_ll->ai_protocol);
    }

    return {sockfd, specs_ll};
}

int Socket::bind(){
    return ::bind(m_sockfd, specs_ll->ai_addr, specs_ll->ai_addrlen);
}

int Socket::connect(){
    return ::connect(m_sockfd, specs_ll->ai_addr, specs_ll->ai_addrlen);
}

int Socket::listen(int backlog){
    return ::listen(m_sockfd, backlog);
}

CommunicationSocket Socket::accept(){
    sockaddr addr;
    socklen_t len;
    return {::accept(m_sockfd, &addr, &len), addr, len};
}
