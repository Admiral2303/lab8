#include <progbase-cpp/net.h>
#include <iostream>
#include <QTime>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QDataStream>
#include <vector>
#include "places.h"
#include "tcp_server.h"
#include <fstream>
#include <QFile>
#include <ctype.h>


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

    const int serverPort = 3100;
    TcpListener listener;
    NetMessage message(1000);
    QString servername = "LOCAL";
    QString developer = "Vadim Scherbina";
    QTime currTime = QTime::currentTime();
    try {
        listener.bind(IpAddress("127.0.0.1", serverPort));
        listener.start();
        while (true) {
            cout << ">> Waiting for clients at " << serverPort << "..." << endl;
            TcpClient * client = listener.accept();
            client->receive(message);
            cout << ">> Received: " << endl << message.dataAsString() << endl;
            if( message.dataAsString() == "GET / HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                QJsonObject send;
                send.insert("time", currTime.toString("hh:mm:ss"));
                send.insert("title", servername);
                send.insert("developer", developer);
                QJsonDocument doc(send);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                //qDebug() <<   strJson;
                message.setDataString(strJson.toStdString());

            }
            if(message.dataAsString() == "GET /favorites HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                QJsonArray place_s;
                for(int i = 0; i < place.size(); i++){
                    QJsonObject json;
                    json.insert("id", place[i]->get_id());
                    json["name"] = place[i]->get_name();
                    json["location"] = place[i]->get_location();
                    place_s.insert(i, json);
                }

                QJsonDocument doc;

                doc.setArray(place_s);
                message.setDataString(doc.toJson().toStdString());
            }
            if(get_key(message.dataAsString()) != "/"){
                QJsonArray place_s;
                QString search = QString::fromStdString(get_key(message.dataAsString()));
                for(int i = 0; i < place.size();i++){
                    if(place[i]->get_location() == search){
                        QJsonObject json;
                        json.insert("id", place[i]->get_id());
                        json["name"] = place[i]->get_name();
                        json["location"] = place[i]->get_location();
                        place_s.insert(i, json);
                    }
                }
                QJsonDocument doc;
                doc.setArray(place_s);
                message.setDataString(doc.toJson().toStdString());
            }
            if(get_id_from_string(message.dataAsString()) != -1){
                int id = get_id_from_string(message.dataAsString());
                 QJsonDocument doc;
                qDebug() << get_id_from_string(message.dataAsString());
                for(int i = 0; i < place.size();i++){
                    if(place[i]->get_id() == id){
                        QJsonObject json;
                        json.insert("id", place[i]->get_id());
                        json["name"] = place[i]->get_name();
                        json["location"] = place[i]->get_location();
                        doc.setObject(json);
                    }
                }
                message.setDataString(doc.toJson().toStdString());
            }
            if(message.dataAsString() == "GET /file HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                    QFile file(":/data/data.txt");
                    QByteArray data;
                    if (!file.open(QIODevice::ReadOnly)){
                        qDebug() << "++";
                    }
                    data = file.readAll();
                    qDebug() << QString(data);

                    QJsonObject send;
                    send.insert("name", "data.txt");
                    send.insert("size", QString::number(file.size()));
                    send.insert("content",QString::fromStdString( data.toStdString()));
                    QJsonDocument doc(send);
                    QString strJson(doc.toJson(QJsonDocument::Compact));
                    //qDebug() <<   strJson;
                    message.setDataString(strJson.toStdString());
            }
            if(message.dataAsString() == "GET /file/data HTTP/1.0\r\nHost: Localhost \r\n\r\n"){
                QFile file(":/data/data.txt");
                QByteArray data;
                if (!file.open(QIODevice::ReadOnly)){
                    qDebug() << "++";
                }
                data = file.readAll();
                string dat = data.toStdString();
                int lower = 0;
                int upper = 0;
                for(int i = 0; i < dat.size(); i++){
                    if(islower(dat[i])){
                        lower++;
                    }
                    if(isupper(dat[i])){
                        upper++;
                    }
                }
                QJsonObject send;
                send.insert("lower", QString::number(lower));
                send.insert("upper", QString::number(upper));
                QJsonDocument doc(send);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                //qDebug() <<   strJson;
                message.setDataString(strJson.toStdString());
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



