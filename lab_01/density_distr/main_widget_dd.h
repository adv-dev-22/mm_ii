#ifndef _MAIN_WIDGET_DD_H_
#define _MAIN_WIDGET_DD_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QPushButton>

class PlotGraphicsScene;

class MainWidgetDD : public QWidget {
Q_OBJECT
public:
    MainWidgetDD(QWidget *parent = nullptr);
    ~MainWidgetDD();

private:
    QHBoxLayout * horizontal_layout_;
    QVBoxLayout * vertical_layout_;

    QGraphicsView * graphics_view_;
    PlotGraphicsScene * gscene_;


    QPushButton * update_btn_;
};

#endif // _MAIN_WIDGET_DD_H_
