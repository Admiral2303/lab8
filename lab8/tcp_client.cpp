#include <progbase-cpp/net.h>
#include <iostream>
#include "tcp_client.h"


using namespace std;
using namespace progbase::net;
    //"GET /api/v2/pokemon/1/ HTTP/1.0\r\nHost: pokeapi.co\r\n\r\n"

int tcpWebClient(void) {
//    int main(void){
    TcpClient client;
    NetMessage message(1000);
    try {
        client.connect(IpAddress("127.0.0.1", 3100));
        message.setDataString("GET /file/data HTTP/1.0\r\nHost: Localhost \r\n\r\n");
        client.send(message);
        cout << ">> Request sent" << endl;
        do {
            client.receive(message);
            std::string str = message.dataAsString();
            cout << ">> Received " << str.length() << " bytes: " << endl << str << endl;
        } while (!message.isEmpty());
    } catch(NetException const & exc) {
        cerr << exc.what() << endl;
    }
    return 0;
}
