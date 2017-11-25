#include "gui/include/qinputsizeline.h"

QInputSizeLine::QInputSizeLine(QWidget *parent) : QWidget(parent),
    _enterSizeLabel(new QLabel),_sizesBox(new QComboBox), _layout(new QHBoxLayout),
    _currentIndex(3)
{
    _enterSizeLabel->setText(QString("Выберите размер матрицы"));
    for(int i = 2 ; i <= 10; i++)
        _sizesList << QString::number(i) + " x " + QString::number(i);

    _sizesBox->addItems(_sizesList);
    _sizesBox->setCurrentIndex(1);
    QFont font =  _enterSizeLabel->font();
    font.setPixelSize(20);
    _enterSizeLabel->setFont(font);
    _layout->addWidget(_enterSizeLabel.get());
    _layout->addWidget(_sizesBox.get());
    _layout->setAlignment(Qt::AlignCenter);

    this->setLayout(_layout.get());
}
