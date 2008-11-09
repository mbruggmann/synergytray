#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <string>
#include <iostream>
#include <cstdio>

#include <KProcess>
#include <KDebug>

class ProcessUtils : QObject
{
    Q_OBJECT
public:
    static KProcess* getNew(QObject *parent, QString program, QString arg1=QString(), QString arg2=QString(), QString arg3=QString());
    static bool isRunning(QString processName);
};

#endif // PROCESSUTILS_H
