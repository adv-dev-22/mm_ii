#ifndef _MAIN_WIDGET_DD_H_
#define _MAIN_WIDGET_DD_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

class ParametersWidget;
class PlotGraphicsScene;
class QLabel;
class QLineEdit;

class MainWidgetDD : public QWidget {
Q_OBJECT
public:
    MainWidgetDD(QWidget *parent = nullptr);
    ~MainWidgetDD();

private:
    // Auxiliary layouts
    QHBoxLayout * horizontal_layout_;
    QVBoxLayout * vertical_layout_;

    // Graphical plotting
    QGraphicsView * graphics_view_;
    PlotGraphicsScene * gscene_;

    // Control buttons etc.
    QGroupBox * group_box_;
    QRadioButton * uniform_distr_rbtn_;
    QRadioButton * normal_distr_rbtn_;
    QRadioButton * poisson_distr_rbtn_;

    QLabel * param_01_label_;
    QLineEdit * param_01_edit_;

    QPushButton * update_btn_;
    QPushButton * clear_btn_;


};

#endif // _MAIN_WIDGET_DD_H_
