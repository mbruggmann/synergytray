/*
 * networkutils.h
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */

#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QString>

// for gethostbyname
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

class NetworkUtils
{
public:
    static bool isHostAvailable(QString name);
    static QString getHostname();
};

#endif // NETWORKUTILS_H
