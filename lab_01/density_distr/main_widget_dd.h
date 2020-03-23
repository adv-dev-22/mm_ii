#ifndef _MAIN_WIDGET_DD_H_
#define _MAIN_WIDGET_DD_H_

#include <QWidget>
#include <memory>
#include "density_engine.h"
#include "compute_thread.h"
#include "threads_stop_indicator.h"

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

    // Range
    QLabel    * a_left_label_;
    QLineEdit * a_left_edit_;
    QLabel    * b_right_label_;
    QLineEdit * b_right_edit_;

    // Push buttons
    QPushButton * update_btn_;
    QPushButton * clear_btn_;

    QPushButton * quit_button_;

    // Numerical data. Provides f(x) and F(x) arrays.
    const size_t n_points_;

    std::unique_ptr<BaseDensityEngine<double>> xrange_engine_;
    std::unique_ptr<BaseDensityEngine<double>> f_dens_engine_;
    std::unique_ptr<BaseDensityEngine<double>> F_prob_engine_;

    std::unique_ptr<ComputeDensityThread> xrange_thread_;
    std::unique_ptr<ComputeDensityThread> f_dens_thread_;
    std::unique_ptr<ComputeDensityThread> F_prob_thread_;

    std::unique_ptr<ThreadsStopIndicator> threads_indicator_;

private slots:
    void emit_quit_clicked_();
    void unoform_distr_radio_selected_(bool checked);
    void start_plot_data_computation_();

public slots:
    void extract_data_and_draw_();

private:
    void muth_compute_uniform_data_();
    // ..

};

#endif // _MAIN_WIDGET_DD_H_

