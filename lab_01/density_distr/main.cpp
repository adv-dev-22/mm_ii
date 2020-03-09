#include "main_widget_dd.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication app_dd(argc, argv);
    MainWidgetDD mw_dd;

    QObject::connect(&mw_dd, SIGNAL(quit_button_pressed()), &app_dd, SLOT(quit()));

    mw_dd.show();
    return app_dd.exec();
}
