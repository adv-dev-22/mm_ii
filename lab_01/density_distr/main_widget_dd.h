#ifndef _MAIN_WIDGET_DD_H_
#define _MAIN_WIDGET_DD_H_

#include <QWidget>

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
    QGraphicsView * graphics_view_;
    PlotGraphicsScene * gscene_;

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

private slots:
    void emit_quit_clicked();
};

#endif // _MAIN_WIDGET_DD_H_

