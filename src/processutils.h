#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <KProcess>

class ProcessUtils : QObject
{
    Q_OBJECT
public:
    static KProcess* getNew(QString program, QString arg1=QString(), QString arg2=QString());
};

#endif // PROCESSUTILS_H
