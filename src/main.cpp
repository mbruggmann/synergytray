#include "synergytray.h"

#include <kuniqueapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("Synergy Tray Application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("synergytray", 0, ki18n("SynergyTray"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2007 Marc Bruggmann"), KLocalizedString(), 0, "bruggmann@web.de");
    about.addAuthor( ki18n("Marc Bruggmann"), KLocalizedString(), "bruggmann@web.de" );

    KCmdLineArgs::init(argc, argv, &about);
    KUniqueApplication::addCmdLineOptions();

    KUniqueApplication app;
    app.setQuitOnLastWindowClosed(false);

    if (!KUniqueApplication::start()) {
        fprintf(stderr, "Synergytray is already running!\n");
        return 0;
    }

    SynergyTray tray;

    return app.exec();
}
