#include "window.h"

#include <QApplication>

int main( int argc, char **argv )
{
    QApplication app(argc, argv);
    app.setOrganizationName("XXX");
    app.setApplicationName("plot");

    Ui::Window window;
    window.show();

    return app.exec();
}
