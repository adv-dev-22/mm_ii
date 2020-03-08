#include "main_widget_dd.h"
#include "plot_graphics_scene.h"
#include <QApplication>
#include <QRect>
#include <QScreen>


MainWidgetDD::MainWidgetDD(QWidget * parent):
QWidget(parent),
horizontal_layout_(nullptr),
vertical_layout_(nullptr),
graphics_view_(nullptr),
gscene_(nullptr),
update_btn_(nullptr) {

    // Setup main widget size.
    auto screen_list = QApplication::screens();
    QSize screen_size(screen_list.front()->size());

    const int horizont_delta = 400;
    const int vertical_delta = 200;
    const int win_width  = screen_size.width()  - horizont_delta;
    const int win_height = screen_size.height() - vertical_delta;
    QSize window_size(win_width, win_height);
    this->resize(window_size);

    // Main window position
    const int x_pos = 100;
    const int y_pos = 80;
    this->move(x_pos, y_pos);

    // Create basic layout
    horizontal_layout_ = new QHBoxLayout();
    this->setLayout(horizontal_layout_);

    // PlotGraphicsScene
    gscene_ = new PlotGraphicsScene();
    gscene_->addText("Test GScene");

    graphics_view_ = new QGraphicsView(gscene_);
    horizontal_layout_->addWidget(graphics_view_);
    graphics_view_->show();

    // Create control pannel layout
    vertical_layout_ = new QVBoxLayout();
    horizontal_layout_->addLayout(vertical_layout_);


    update_btn_ = new QPushButton("update");
    vertical_layout_->addWidget(update_btn_);

}

MainWidgetDD::~MainWidgetDD() {

    gscene_ = nullptr;
    //graphics_panel_layout_ = nullptr;
}
