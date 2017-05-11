#include <progbase-cpp/net.h>
#include <iostream>
#include <vector>
#include "places.h"
#include "tcp_server.h"
#include <fstream>
#include <ctype.h>
#include <string>
#include <jansson.h>
#include <time.h>
#include <stdio.h>
//#include <io.h>

using namespace std;
using namespace progbase::net;

string get_key(string message);
int get_id_from_string(string message);

    //"GET /api/v2/pokemon/1/ HTTP/1.0\r\nHost: pokeapi.co\r\n\r\n"

int tcpServer() {
//int main(void){
    vector<places*> place;
    place.push_back(new places(0,"Sofievka", "Uman"));
    place.push_back(new places(1,"Flora", "Uman"));
    place.push_back(new places(2,"Golden gates", "Kiev"));
    place.push_back(new places(3,"Maidan Nesalegnosti", "Kiev"));

    const int serverPort = 3001;
    TcpListener listener;
    NetMessage message(1000);
    string servername = "LOCAL";
    string developer = "Vadim Scherbina";
    //QTime currTime = QTime::currentTime();
    try {
        listener.bind(IpAddress("127.0.0.1", serverPort));
        listener.start();
        while (true) {
            cout << ">> Waiting for clients at " << serverPort << "..." << endl;
            TcpClient * client = listener.accept();
            client->receive(message);
            cout << ">> Received: " << endl << message.dataAsString() << endl;
            if( message.dataAsString() == "GET / HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                    time_t rawtime;
                    struct tm * timeinfo; 
                    time ( &rawtime );
                    timeinfo = localtime ( &rawtime );
                    json_t * json = json_object();
                    //json_object_set_new(json, "time", json_string(songs[i]->getName().c_str()));
                    json_object_set_new(json, "title", json_string(servername.c_str()));
                    json_object_set_new(json, "developer", json_string(developer.c_str()));
                    json_object_set_new(json, "time", json_string(asctime (timeinfo)));
                   // json_decref(json);
                    char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                    message.setDataString(jsonString);


            }
            if(message.dataAsString() == "GET /favorites HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
               json_t * array = json_array(); 
                for(int i = 0; i < place.size(); i++){
                    json_t * json = json_object();
                    json_object_set_new(json, "id", json_integer(place[i]->get_id()));
                    json_object_set_new(json, "name", json_string(place[i]->get_name().c_str()));
                    json_object_set_new(json, "location", json_string(place[i]->get_location().c_str()));
                    json_array_append(array, json);
                    json_decref(json);
                }
                char * jsonString = json_dumps(array, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                message.setDataString(jsonString);
            }
            if(get_key(message.dataAsString()) != "/"){
                json_t * array = json_array(); 
                string search = get_key(message.dataAsString());
                for(int i = 0; i < place.size();i++){
                    if(place[i]->get_location() == search){
                        json_t * json = json_object();
                        json_object_set_new(json, "id", json_integer(place[i]->get_id()));
                        json_object_set_new(json, "name", json_string(place[i]->get_name().c_str()));
                        json_object_set_new(json, "location", json_string(place[i]->get_location().c_str()));
                        json_array_append(array, json);
                        json_decref(json); 
                    }
                }
                char * jsonString = json_dumps(array, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                message.setDataString(jsonString);
            }
            if(get_id_from_string(message.dataAsString()) != -1){
                int id = get_id_from_string(message.dataAsString());
                // QJsonDocument doc;
                for(int i = 0; i < place.size();i++){
                    if(place[i]->get_id() == id){
                        json_t * json = json_object();
                        json_object_set_new(json, "id", json_integer(place[i]->get_id()));
                        json_object_set_new(json, "name", json_string(place[i]->get_name().c_str()));
                        json_object_set_new(json, "location", json_string(place[i]->get_location().c_str()));
                        char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                        message.setDataString(jsonString);
                    }
                }
                //message.setDataString(doc.toJson().toStdString());
            }
            if(message.dataAsString() == "GET /file HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                    string line;
                    string text;
                    ifstream myfile ("/home/vadim/lab8/data/data.txt");
                    if (myfile.is_open()){
                        while (! myfile.eof() ){
                            getline (myfile,line);
                            text += line;
                        }
                        myfile.close();
                    }
                    else cout << "Unable to open file"; 
                    json_t * json = json_object();
                    json_object_set_new(json, "name", json_string("data.txt"));
                    fstream file("/home/vadim/lab8/data/data.txt");
                    int size = 0;
                    file.seekg (0, std::ios::end);
                    size = file.tellg();
                    // size = filesize("/home/vadim/lab8/data/data.txt");
                     json_object_set_new(json, "size", json_integer(size));
                    json_object_set_new(json, "content", json_string(text.c_str()));
                    char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                    message.setDataString(jsonString);
                     
            }
            if(message.dataAsString() == "GET /file/data HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                string line;
                string text;
                ifstream myfile ("/home/vadim/lab8/data/data.txt");
                if (myfile.is_open()){
                    while (! myfile.eof() ){
                        getline (myfile,line);
                        text += line;
                    }
                    myfile.close();
                }
                else cout << "Unable to open file"; 
                int lower = 0;
                int upper = 0;
                for(int i = 0; i < text.size(); i++){
                    if(islower(text[i])){
                        lower++;
                    }
                    if(isupper(text[i])){
                        upper++;
                    }
                }
                json_t * json = json_object();
                json_object_set_new(json, "lower", json_integer(lower));
                json_object_set_new(json, "upper", json_integer(lower));
                char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
                message.setDataString(jsonString);
            }
            client->send(message);
            cout << ">> Response sent." << endl;
            delete client;
        }
    } catch(NetException const & exc) {
        cerr << exc.what() << endl;
    }
    return 0;
}

string get_key(string message){
    string get = "GET /favorites?location=";
    int i = 0;
    for(; i < get.size(); i++){
        if(message[i] != get[i]){
            return "/";
        }
    }
    string key = "";
    while(message[i] != ' '){
//        key[j] = message[i];
        key += message[i];
//        cout << message[i];
        i++;
    }
    return key;
}

int get_id_from_string(string message){
    string get = "GET /favorites/";
    int i = 0;
    for(; i < get.size(); i++){
        if(message[i] != get[i]){
            return -1;
        }
    }
    string num = "";
    for(; message[i] != ' '; i++){
        num += message[i];
    }
    int id = stoi(num);
    return id;
}


