#include "params_widget.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

ParametersWidget::ParametersWidget(QWidget * parent):
QWidget(parent) {

    //auto form_group_box = new QGroupBox(tr("Параметры"), this);
    QFormLayout * layout = new QFormLayout();
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit());
//        layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
//        layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    //form_group_box->setLayout(layout);

    //(form_group_box);

    this->setLayout(layout);

}




// End of the file

