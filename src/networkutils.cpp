#include "networkutils.h"

bool NetworkUtils::isHostAvailable(QString name)
{
    const hostent* host_info = 0;
    host_info = gethostbyname(name.toAscii().constData());

    return (host_info);
}

QString NetworkUtils::getHostname()
{
    char buf[1024+1];
    gethostname(buf, 1024);
    return QString(buf);
}
