#include "balancer.h"
#include "shared.h"

void attachCBPF(int sockFD, unsigned int groupSize)
{
    // CBPF code for REUSEPORT dispatch based on CPU() % group_size, returns [1, groupSize-1]
    struct sock_filter code[] = {
        {BPF_LD | BPF_W | BPF_ABS, 0, 0, SKF_AD_CPU},     // A = #cpu
        {BPF_ALU | BPF_MOD | BPF_K, 0, 0, groupSize - 1}, // A = A % group_size-1
        {BPF_ALU | BPF_ADD | BPF_K, 0, 0, 1},             // A = A+1
        {BPF_RET | BPF_A, 0, 0, 0}                        // return A
    };

    struct sock_fprog bpf = {
        .len = sizeof(code) / sizeof(code[0]),
        .filter = code,
    };

    // Attach CBPF program to this socket
    socklen_t sizeOfBPF = (socklen_t)sizeof(bpf);
    if (setsockopt(sockFD, SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, &bpf, sizeOfBPF) < 0)
    {
        log_error("Failed to attach so_reuseport_cbpf.\n");
        exit(EXIT_FAILURE);
    }
}

void displayConfig(int sockFD)
{
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    // Assuming sockfd is your bound UDP socket
    if (getsockname(sockFD, (struct sockaddr *)&addr, &addrLen) == -1)
    {
        log_error("getsockname failed.\n");
        exit(EXIT_FAILURE);
    }

    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);

    log_info("Udp Socket listening on %s:%d\n", ipStr, ntohs(addr.sin_port));
}

void signal_handler(int signal)
{
    log_debug("Terminal Signal caught\n");
}

void udpLoadBalancer(char* serviceIp, int port, unsigned int groupSize)
{
    int sockFD;
    struct sockaddr_in serverAddress;

    // initialise socket
    sockFD = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockFD < 0)
    {
        log_error("udp socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Enable SO_REUSEPORT option
    const int enable = 1;
    if (setsockopt(sockFD, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
    {
        log_error("setsockopt(SO_REUSEPORT) failed.\n");
        exit(EXIT_FAILURE);
    }

    // Attach CBPF program
    attachCBPF(sockFD, groupSize);

    //  Configure serverAddress object
    serverAddress.sin_family = AF_INET;         
    serverAddress.sin_addr.s_addr = inet_addr(serviceIp);
    serverAddress.sin_port = htons(port);

    // Bind socket to specific ip and port
    if (bind(sockFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        log_error("bind failed for udp socket.\n");
        exit(EXIT_FAILURE);
    }

    // display config
    displayConfig(sockFD);

    // Register signal handler
    struct sigaction act;
    act.sa_handler =  signal_handler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIG_ERR, &act, NULL);

    int ret = pause();
    if (-1 == ret)
        log_debug("Process exited\n");
}