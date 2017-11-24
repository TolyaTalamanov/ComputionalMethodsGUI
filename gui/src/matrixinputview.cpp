#include "gui/include/matrixinputview.h"
#include <QScrollArea>

QMatrixInputView::QMatrixInputView(int size, QWidget *parent) :
                                   QWidget(parent), _size(size)
{
     _lineEdits       = new QLineEdit*   [_size * _size];
     _qLabels         = new QLabel*      [_size * _size];
     _hLayout         = new QHBoxLayout* [_size];
     _freeValLineEdit = new QLineEdit*   [_size];
     _vLayout         = new QVBoxLayout;
     _vLayoutFreeVal  = new QVBoxLayout;
     _mainLayout      = new QHBoxLayout;

     QString operation;
     for(int i = 0 ; i < _size; i++){
         _freeValLineEdit[i] = new QLineEdit;
         _freeValLineEdit[i]->setFixedSize(50, 20);
         _hLayout[i] = new QHBoxLayout;
         for(int j = 0 ; j < _size; j++){
             _qLabels  [i * _size + j] = new QLabel;
             operation = (j == _size - 1 ? " = " : " + ");
             _qLabels  [i * _size + j]->setText("X" + QString::number(j) + operation);

             _lineEdits[i * _size + j] = new QLineEdit;
             _lineEdits[i * _size + j]->setFixedSize(50, 20);

             _hLayout[i]->addWidget(_lineEdits[i * _size + j]);
             _hLayout[i]->addWidget(_qLabels  [i * _size + j]);
         }
         _hLayout[i]->addWidget(_freeValLineEdit[i]);
         _vLayout->addLayout(_hLayout[i]);
     }
     _mainLayout->addLayout(_vLayout);
    // _mainLayout->addLayout(_vLayoutFreeVal);
     setLayout(_mainLayout);

}
