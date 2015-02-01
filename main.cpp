#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Dialog tabdlg;
    tabdlg.show();
    return app.exec();
}
