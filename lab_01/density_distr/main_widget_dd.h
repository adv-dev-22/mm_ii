#ifndef _MAIN_WIDGET_DD_H_
#define _MAIN_WIDGET_DD_H_

#include <QWidget>
#include <memory>
#include "density_solver.h"

class QwtPlot;
class QHBoxLayout;
class QVBoxLayout;
class QGraphicsView;
class QPushButton;
class QGroupBox;
class QRadioButton;
class PlotGraphicsScene;
class QLabel;
class QLineEdit;

class MainWidgetDD : public QWidget {
Q_OBJECT
public:
    MainWidgetDD(QWidget *parent = nullptr);
    ~MainWidgetDD();

signals:
    void quit_button_pressed();

private:
    // Graphical plotting
    QwtPlot * plotter2d_;

    // Type of the distribution radio buttons etc.
    QRadioButton * uniform_distr_rbtn_;
    QRadioButton * exponent_distr_rbtn_;
    QRadioButton * normal_distr_rbtn_;
    QRadioButton * poisson_distr_rbtn_;

    // Parameters
    QLabel * param_01_label_;
    QLabel * param_02_label_;
    QLineEdit * param_01_edit_;
    QLineEdit * param_02_edit_;

    // Push buttons
    QPushButton * update_btn_;
    QPushButton * clear_btn_;

    QPushButton * quit_button_;

    // Numerical data. Provides f(x) and F(x) arrays.
    std::unique_ptr<BaseDensity> density_engine_;

private slots:
    void emit_quit_clicked_();
    void unoform_distr_radio_selected_(bool checked);
};

#endif // _MAIN_WIDGET_DD_H_

