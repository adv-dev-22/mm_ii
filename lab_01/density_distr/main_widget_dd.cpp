#include "main_widget_dd.h"
#include <QApplication>
#include <QRect>
#include <QScreen>


MainWidgetDD::MainWidgetDD(QWidget * parent):
QWidget(parent) {

    // Setup main widget size and position.
    auto screen_list = QApplication::screens();
    QSize screen_size(screen_list.front()->size());

    const int horizont_delta = 400;
    const int vertical_delta = 200;

    QSize window_size(screen_size.width()  - horizont_delta,
                      screen_size.height() - vertical_delta);
    this->resize(window_size);

    const int x_pos = 100;
    const int y_pos = 80;
    this->move(x_pos, y_pos);

    // Create layouts


}

MainWidgetDD::~MainWidgetDD() {

}
