#include "gui/include/qinputparamsline.h"

QInputParamsLine::QInputParamsLine(QWidget *parent) : QWidget(parent), _paramsName(new QLabel()),
    _paramsEnterField(new QLineEdit()), _plane(new QHBoxLayout)
{
    _paramsEnterField->setMinimumHeight(15);
    _paramsEnterField->setStyleSheet("background-color:white");
    _plane->addWidget(_paramsName.get());
    _plane->addWidget(_paramsEnterField.get());
     this->setLayout(_plane.get());
    _plane->setAlignment(Qt::AlignTop);
}
