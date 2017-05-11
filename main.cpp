
#include <iostream>
#include <tcp_client.h>
#include <tcp_server.h>
#include <fstream>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>
using namespace std;

int main(void)
{
//  tcpServer();
   tcpWebClient();
//    {

//        QFile file(":/data/data.txt"); // создаем объект класса QFile

//        QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные

//        if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения

//        qDebug() << "++"; // если это сделать невозможно, то завершаем функцию

//        data = file.readAll(); //считываем все данные с файла в объект data

//        qDebug() << QString(data); // Выводим данные в консоль, предварительно создав строку из полученных данных

//    }
    return 0;
}

