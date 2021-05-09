#include "client1.h"

#include <QJsonDocument>
#include <QTimer>

#include <klibcore/src/network/kpackage.h>

Client1::Client1(QObject *parent) : QObject(parent) {



}

void Client1::sendMessage(QVariant msg) {
    setMsg(msg.toString());
    //local.write(KPackage("text", msg).toJson());
}
