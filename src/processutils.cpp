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

bool ProcessUtils::isRunning(QString processName) {
    bool processRunning = false;

    std::string proc(processName.toAscii().constData());
    std::string cmd("pidof " + proc);

    FILE *pfd = popen(cmd.c_str(), "r");

    if (pfd > 0){
        while (!feof(pfd)) {
            char buf[1024] = {0};

            if (fgets(buf, sizeof(buf), pfd) > 0) {
                std::string result(buf);

                if (result != "\n") {
                    processRunning = true;
                    break;
                }
            }
        }
        pclose(pfd);
    }

    return processRunning;
}
