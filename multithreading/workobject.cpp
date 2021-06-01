#include "workobject.h"

WorkObject::WorkObject()
{

}
WorkObject::~WorkObject()
{

}

void WorkObject::run() {
    QDBusInterface interface( "org.freedesktop.NetworkManager",
                              "/org/freedesktop/NetworkManager",
                              "org.freedesktop.DBus.Properties",
                              QDBusConnection::systemBus() );
    QDBusMessage result = interface.call("Get", "org.freedesktop.NetworkManager", "ActiveConnections");
    QList<QVariant> outArgs = result.arguments();
    QVariant first = outArgs.at(0);
    QDBusVariant dbvFirst = first.value<QDBusVariant>();
    QVariant vFirst = dbvFirst.variant();
    const QDBusArgument &dbusArgs = vFirst.value<QDBusArgument>();

    QDBusObjectPath objPath;
    dbusArgs.beginArray();

    while (!dbusArgs.atEnd()) {
        dbusArgs >> objPath;
        QDBusInterface interfacePro("org.freedesktop.NetworkManager",
                                    objPath.path(),
                                    "org.freedesktop.NetworkManager.Connection.Active",
                                    QDBusConnection::systemBus());
        QString replyIPV4Path = interfacePro.property("Ip4Config")
                .value<QDBusObjectPath>()
                .path();
        if (replyIPV4Path != "/") {
            emit Ipv4PathSignal(replyIPV4Path);
        }
    }
}
