#include "main_widget_dd.h"
#include "params_widget.h"
#include "plot_graphics_scene.h"
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>


MainWidgetDD::MainWidgetDD(QWidget * parent):
QWidget(parent),
horizontal_layout_(nullptr),
vertical_layout_(nullptr),
graphics_view_(nullptr),
gscene_(nullptr),
group_box_(nullptr),
uniform_distr_rbtn_(nullptr),
normal_distr_rbtn_(nullptr),
poisson_distr_rbtn_(nullptr),
param_01_label_(nullptr),
param_01_edit_(nullptr),

update_btn_(nullptr),
clear_btn_(nullptr) {

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
    vertical_layout_->setSizeConstraint(QLayout::SetMinimumSize);
    horizontal_layout_->addLayout(vertical_layout_);

    // Density groupbox
    group_box_ = new QGroupBox(tr("Распределение"));
    uniform_distr_rbtn_ = new QRadioButton(tr("Равномерное"));
    normal_distr_rbtn_  = new QRadioButton(tr("Нормальное"));
    poisson_distr_rbtn_ = new QRadioButton(tr("Пуассона"));

    QVBoxLayout * radio_layout = new QVBoxLayout();
    radio_layout->addWidget(uniform_distr_rbtn_);
    radio_layout->addWidget(normal_distr_rbtn_);
    radio_layout->addWidget(poisson_distr_rbtn_);
    group_box_->setLayout(radio_layout);
    vertical_layout_->addWidget(group_box_);

    auto form_group_box = new QGroupBox(tr("Параметры"));
    QVBoxLayout * params_layout = new QVBoxLayout();

    QHBoxLayout * param_01_layout = new QHBoxLayout();
//    param_01_layout->setSizeConstraint(100);
    param_01_label_ = new QLabel(tr("undef"));
    param_01_edit_  = new QLineEdit();
//    //param_01_edit_->setMaxLength(2);
    param_01_edit_->setFixedSize(100,50);

//    param_01_layout->addWidget(param_01_label_);
    param_01_layout->setSizeConstraint(QLayout::SetMinimumSize);
//    param_01_layout->addStretch();
    param_01_layout->addWidget(param_01_edit_);
//            //addRow(param_01_label_, param_01_edit_);
//    param_01_layout->addStretch();

    params_layout->addLayout(param_01_layout);
    form_group_box->setLayout(params_layout);
    vertical_layout_->addWidget(form_group_box);


    update_btn_ = new QPushButton(tr("Добавить график"));
    vertical_layout_->addWidget(update_btn_);

    clear_btn_ = new QPushButton(tr("Очистить"));
    vertical_layout_->addWidget(clear_btn_);

    vertical_layout_->addStretch(1);
}

MainWidgetDD::~MainWidgetDD() {

    gscene_ = nullptr;
    //graphics_panel_layout_ = nullptr;
}
