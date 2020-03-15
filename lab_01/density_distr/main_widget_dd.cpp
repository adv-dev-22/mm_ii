#include "main_widget_dd.h"
//#include "plot_graphics_scene.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

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
#include <QDebug>


MainWidgetDD::MainWidgetDD(QWidget * parent):
QWidget(parent),
plotter2d_(nullptr),
uniform_distr_rbtn_(nullptr),
exponent_distr_rbtn_(nullptr),
normal_distr_rbtn_(nullptr),
poisson_distr_rbtn_(nullptr),
param_01_label_(nullptr),
param_02_label_(nullptr),
param_01_edit_(nullptr),
param_02_edit_(nullptr),
a_left_label_(nullptr),
a_left_edit_(nullptr),
b_right_label_(nullptr),
b_right_edit_(nullptr),
update_btn_(nullptr),
clear_btn_(nullptr),
quit_button_(nullptr),
n_points_(1024),
xrange_engine_(nullptr),
f_dens_engine_(nullptr),
F_prob_engine_(nullptr),
xrange_thread_(nullptr),
f_dens_thread_(nullptr),
F_prob_thread_(nullptr) {

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
    plotter2d_ = new QwtPlot();
    horizontal_layout->addWidget(plotter2d_,1);


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
    form_group_box->setMinimumWidth(225);

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
    a_left_label_ = new QLabel(tr("a = "));
    a_left_edit_  = new QLineEdit();
    a_left_edit_->setFixedSize(100,30);
    // b_right
    QHBoxLayout * b_right_layout = new QHBoxLayout();
    b_right_label_ = new QLabel(tr("b = "));
    b_right_edit_  = new QLineEdit();
    b_right_edit_->setFixedSize(100,30);

    a_left_layout->setSizeConstraint(QLayout::SetMinimumSize);
    a_left_layout->addWidget(a_left_label_, 0, Qt::AlignCenter);
    a_left_layout->addWidget(a_left_edit_);
    a_left_edit_->setValidator(new QDoubleValidator());

    b_right_layout->setSizeConstraint(QLayout::SetMinimumSize);
    b_right_layout->addWidget(b_right_label_, 0, Qt::AlignCenter);
    b_right_layout->addWidget(b_right_edit_);
    b_right_edit_->setValidator(new QDoubleValidator());

    range_layout->addLayout(a_left_layout);
    range_layout->addLayout(b_right_layout);
    range_group_box->setLayout(range_layout);
    vertical_layout->addWidget(range_group_box);
    vertical_layout->addSpacing(32);

    update_btn_ = new QPushButton(tr("Построить графики"));
    vertical_layout->addWidget(update_btn_);
    vertical_layout->addSpacing(10);

    clear_btn_ = new QPushButton(tr("Очистить"));
    vertical_layout->addWidget(clear_btn_);

    vertical_layout->addStretch(1);

    quit_button_ = new QPushButton(tr("Выход"));
    vertical_layout->addWidget(quit_button_);

    // Numerical data
    // ..

    // Threads
    xrange_thread_ = std::make_unique<ComputeDensityThread>();
    f_dens_thread_ = std::make_unique<ComputeDensityThread>();
    F_prob_thread_ = std::make_unique<ComputeDensityThread>();

    // Signals and slots connections.
    QObject::connect(quit_button_, SIGNAL(clicked()), this, SLOT(emit_quit_clicked_()));

    QObject::connect(uniform_distr_rbtn_, SIGNAL(toggled(bool)),
                     this, SLOT(unoform_distr_radio_selected_(bool)));

    QObject::connect(update_btn_, SIGNAL(clicked()), this, SLOT(draw_plot_()));

    // ..
}

MainWidgetDD::~MainWidgetDD() {

    plotter2d_ = nullptr;
    uniform_distr_rbtn_ = nullptr;
    exponent_distr_rbtn_ = nullptr;
    normal_distr_rbtn_ = nullptr;
    poisson_distr_rbtn_ = nullptr;
    param_01_label_ = nullptr;
    param_02_label_ = nullptr;
    param_01_edit_ = nullptr;
    param_02_edit_ = nullptr;
    a_left_label_ = nullptr;
    a_left_edit_  = nullptr;
    b_right_label_ = nullptr;
    b_right_edit_  = nullptr;
    update_btn_ = nullptr;
    clear_btn_ = nullptr;
    quit_button_ = nullptr;
}

void MainWidgetDD::emit_quit_clicked_() {
    emit quit_button_pressed();
}

void MainWidgetDD::unoform_distr_radio_selected_(bool checked) {

    if (!checked) return;

    param_01_label_->setText(tr(""));
    param_01_label_->setDisabled(true);
    param_01_edit_->setDisabled(true);

    param_02_label_->setText(tr(""));
    param_02_label_->setDisabled(true);
    param_02_edit_->setDisabled(true);

    plotter2d_->setTitle(tr("Равномерное распределение"));
    plotter2d_->setCanvasBackground(Qt::white);

    a_left_edit_->setText("0");
    b_right_edit_->setText("1");
}

void MainWidgetDD::draw_plot_() {

    if (uniform_distr_rbtn_->isChecked()) {
        draw_uniform_plot_();
    }

    // ..



}

void MainWidgetDD::draw_uniform_plot_() {

    const double a_left  = a_left_edit_->text().toDouble();
    const double b_right = b_right_edit_->text().toDouble();

    tuple_ttu<double> abn_range(a_left, b_right, n_points_);

    xrange_engine_ = std::make_unique<UniformRange<double>>();
    xrange_engine_->set_range(abn_range);

    xrange_thread_->set_engine(xrange_engine_.get());
    xrange_thread_->start(QThread::InheritPriority);



//    const std::vector<T> & get_data() const;


    //xrange_engine_;
    //f_dens_engine_;
    //F_prob_engine_

//    std::unique_ptr<ComputeDensityThread> xrange_thread_;


}




// End of the file
