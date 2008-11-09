#include "synergytray.h"
#include <kapplication.h>
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

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    
    KApplication app;

    SynergyTray *widget = new SynergyTray;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(SynergyTray);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
