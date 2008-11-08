#include "processutils.h"

KProcess* ProcessUtils::getNew(QString program, QString arg1, QString arg2)
{
    KProcess p = new KProcess();
    p->clearEnvironment();
    p->clearProgram();

    *p << program;
    if (arg1 != QString())
        *p << arg1;
    if (arg2 != QString())
        *p << arg2;

    return p;
}
