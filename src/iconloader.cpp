#include "iconloader.h"

IconLoader::IconLoader()
{

}

IconLoader::~IconLoader()
{

}

QPixmap IconLoader::get(QString name)
{
    QPixmap icon;
    KIconLoader *loader = KIconLoader::global();
    icon = loader->loadIcon(name, KIconLoader::Desktop);
    return icon;

    /* other icon groups
        NoGroup = -1, Desktop = 0, FirstGroup = 0, Toolbar,
        MainToolbar, Small, Panel, Dialog,
        LastGroup, User
    */
}
