#include "processutils.h"

KProcess* ProcessUtils::getNew(QObject *parent, QString program, QString arg1, QString arg2, QString arg3)
{
    KProcess *p = new KProcess(parent);
    p->clearEnvironment();
    p->clearProgram();

    *p << program;
    if (arg1 != QString())
        *p << arg1;
    if (arg2 != QString())
        *p << arg2;
    if (arg3 != QString())
        *p << arg3;

    return p;
}
