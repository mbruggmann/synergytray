/*
 * iconloader.h
 *
 * Copyright (C) 2007 Marc Bruggmann <bruggmann@web.de>
 */

#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <kiconloader.h>
#include <QPixmap>

class IconLoader
{
public:
    IconLoader();
    virtual ~IconLoader();

    static QPixmap get(QString name);
};

#endif // ICONLOADER_H
