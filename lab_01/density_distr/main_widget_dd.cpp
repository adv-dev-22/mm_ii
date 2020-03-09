#include "main_widget_dd.h"
#include "plot_graphics_scene.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QRect>
#include <QScreen>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>

MainWidgetDD::MainWidgetDD(QWidget * parent):
QWidget(parent),
graphics_view_(nullptr),
gscene_(nullptr),
uniform_distr_rbtn_(nullptr),
exponent_distr_rbtn_(nullptr),
normal_distr_rbtn_(nullptr),
poisson_distr_rbtn_(nullptr),
param_01_label_(nullptr),
param_02_label_(nullptr),
param_01_edit_(nullptr),
param_02_edit_(nullptr),
update_btn_(nullptr),
clear_btn_(nullptr),
quit_button_(nullptr) {

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
    auto horizontal_layout = new QHBoxLayout();
    this->setLayout(horizontal_layout);

    // PlotGraphicsScene
    gscene_ = new PlotGraphicsScene();
    gscene_->addText("Test GScene");

    graphics_view_ = new QGraphicsView(gscene_);
    graphics_view_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    horizontal_layout->addWidget(graphics_view_, 1);
    graphics_view_->show();

    // Create control pannel layout
    auto vertical_layout = new QVBoxLayout();
    vertical_layout->setSizeConstraint(QLayout::SetMinimumSize);
    horizontal_layout->addLayout(vertical_layout);

    // Density groupbox
    auto group_box = new QGroupBox(tr("Распределение"));
    uniform_distr_rbtn_  = new QRadioButton(tr("Равномерное"));
    exponent_distr_rbtn_ = new QRadioButton(tr("Экспоненциальное"));
    normal_distr_rbtn_   = new QRadioButton(tr("Нормальное"));
    poisson_distr_rbtn_  = new QRadioButton(tr("Пуассона"));

    QVBoxLayout * radio_layout = new QVBoxLayout();
    radio_layout->addWidget(uniform_distr_rbtn_);
    radio_layout->addWidget(exponent_distr_rbtn_);
    radio_layout->addWidget(normal_distr_rbtn_);
    radio_layout->addWidget(poisson_distr_rbtn_);
    group_box->setLayout(radio_layout);
    vertical_layout->addWidget(group_box);
    vertical_layout->addSpacing(32);

    // Parameters groupbox
    auto form_group_box = new QGroupBox(tr("Параметры"));
    QVBoxLayout * params_layout = new QVBoxLayout();

    // Parameter 1
    QHBoxLayout * param_01_layout = new QHBoxLayout();
    param_01_label_ = new QLabel(tr("Парам_1 = "));
    param_01_edit_  = new QLineEdit();
    param_01_edit_->setFixedSize(100,30);
    // Parameter 2
    QHBoxLayout * param_02_layout = new QHBoxLayout();
    param_02_label_ = new QLabel(tr("Парам_2 = "));
    param_02_edit_  = new QLineEdit();
    param_02_edit_->setFixedSize(100,30);

    param_01_layout->setSizeConstraint(QLayout::SetMinimumSize);
    param_01_layout->addWidget(param_01_label_);
    param_01_layout->addWidget(param_01_edit_);
    param_01_edit_->setValidator(new QDoubleValidator());

    param_02_layout->setSizeConstraint(QLayout::SetMinimumSize);
    param_02_layout->addWidget(param_02_label_);
    param_02_layout->addWidget(param_02_edit_);
    param_02_edit_->setValidator(new QDoubleValidator());

    params_layout->addLayout(param_01_layout);
    params_layout->addLayout(param_02_layout);
    form_group_box->setLayout(params_layout);
    vertical_layout->addWidget(form_group_box);
    vertical_layout->addSpacing(32);

    // Range GroupBox
    auto range_group_box = new QGroupBox(tr("Диапазон"));
    QVBoxLayout * range_layout = new QVBoxLayout();
    // a_left
    QHBoxLayout * a_left_layout = new QHBoxLayout();
    auto a_left_label = new QLabel(tr("a = "));
    auto a_left_edit  = new QLineEdit();
    a_left_edit->setFixedSize(100,30);
    // b_right
    QHBoxLayout * b_right_layout = new QHBoxLayout();
    auto b_right_label = new QLabel(tr("b = "));
    auto b_right_edit  = new QLineEdit();
    b_right_edit->setFixedSize(100,30);

    a_left_layout->setSizeConstraint(QLayout::SetMinimumSize);
    a_left_layout->addWidget(a_left_label, 0, Qt::AlignCenter);
    a_left_layout->addWidget(a_left_edit);
    a_left_edit->setValidator(new QDoubleValidator());

    b_right_layout->setSizeConstraint(QLayout::SetMinimumSize);
    b_right_layout->addWidget(b_right_label, 0, Qt::AlignCenter);
    b_right_layout->addWidget(b_right_edit);
    b_right_edit->setValidator(new QDoubleValidator());

    range_layout->addLayout(a_left_layout);
    range_layout->addLayout(b_right_layout);
    range_group_box->setLayout(range_layout);
    vertical_layout->addWidget(range_group_box);
    vertical_layout->addSpacing(32);

    update_btn_ = new QPushButton(tr("Добавить график"));
    vertical_layout->addWidget(update_btn_);
    vertical_layout->addSpacing(10);

    clear_btn_ = new QPushButton(tr("Очистить"));
    vertical_layout->addWidget(clear_btn_);

    vertical_layout->addStretch(1);

    quit_button_ = new QPushButton(tr("Выход"));
    vertical_layout->addWidget(quit_button_);

    // Signals and slots connections.
    QObject::connect(quit_button_, SIGNAL(clicked()), this, SLOT(emit_quit_clicked()));

    // ..

}

MainWidgetDD::~MainWidgetDD() {

    graphics_view_ = nullptr;
    gscene_ = nullptr;
    uniform_distr_rbtn_ = nullptr;
    exponent_distr_rbtn_ = nullptr;
    normal_distr_rbtn_ = nullptr;
    poisson_distr_rbtn_ = nullptr;
    param_01_label_ = nullptr;
    param_02_label_ = nullptr;
    param_01_edit_ = nullptr;
    param_02_edit_ = nullptr;
    update_btn_ = nullptr;
    clear_btn_ = nullptr;
    quit_button_ = nullptr;
}

void MainWidgetDD::emit_quit_clicked() {
    emit quit_button_pressed();
}

// End of the file
