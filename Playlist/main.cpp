#include <QApplication>

#include "musicview.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    MusicView v;

    l.exec();

    if (l.result() == QDialog::Accepted)
    {
        v.show();

        return a.exec();
    }
    else if (l.result() == QDialog::Rejected)
    {
        QApplication::quit();

        a.closeAllWindows();
    }


}
