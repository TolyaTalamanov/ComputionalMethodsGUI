#include "gui/include/mainwindowview.h"

MainWindowView::MainWindowView(QWidget *parent) : QWidget(parent),
    _omega(new QInputParamsLine()), _epsilon(new QInputParamsLine())
                                 
{

    _matrixInputView.reset(new QMatrixInputView);
    _computeButton.reset(new QPushButton);
    _clearButton.reset(new QPushButton);
    _plusButton.reset(new QPushButton);
    _minusButton.reset(new QPushButton);
    _generateButton.reset(new QPushButton);

    _comboBox.reset(new QComboBox);
    _computeButton->setFixedSize(75,25);
    _computeButton->setText("посчитать");

    _clearButton->setFixedSize(75,25);
    _clearButton->setText("очистить");

    _plusButton->setFixedSize(30,30);
    _plusButton->setText("+");

    connect(_plusButton.get(),     SIGNAL(clicked()), this, SLOT(incSize()));
    connect(_minusButton.get(),    SIGNAL(clicked()), this, SLOT(decSize()));
    connect(_generateButton.get(), SIGNAL(clicked()), this, SLOT(fillRandom()));
    connect(_clearButton.get(),    SIGNAL(clicked()), this, SLOT(clear()));
    connect(_computeButton.get(),  SIGNAL(clicked()), this, SLOT(compute()));

    _minusButton->setFixedSize(30,30);
    _minusButton->setText("-");

    _generateButton->setFixedSize(_clearButton->size());
    _generateButton->setText("заполнить");

    for(int i = 0 ; i < 4; i++){
        _hBoxLayouts[i] = new QHBoxLayout;
    }

    for(int i = 0 ; i < 3; i++){
        _vBoxLayout[i] = new QVBoxLayout;
    }

    _hBoxLayouts[0]->addWidget(_generateButton.get());
    _hBoxLayouts[0]->addWidget(_clearButton.get());
    _hBoxLayouts[0]->addWidget(_plusButton.get());
    _hBoxLayouts[0]->addWidget(_minusButton.get());

    _stringList << "Метод Гаусса"
                   << "Метод Крамера"
                   << "Метод Зейделя"
                   << "Метод простых итераций"
                   << "Метод верхней релаксации";

    _comboBox->addItems(_stringList);

    _vBoxLayout[0]->addLayout(_hBoxLayouts[0]);
    _hBoxLayouts[0]->setAlignment(Qt::AlignTop);
    _omega->setParamsName(QString("omega = "));
    _epsilon->setParamsName(QString("epsilon = "));

    _vBoxLayout[2]->addWidget(_omega.get());
    _vBoxLayout[2]->addWidget(_epsilon.get());
    _vBoxLayout[0]->addLayout(_vBoxLayout[2]);
    _vBoxLayout[2]->setAlignment(Qt::AlignTop);

    _vBoxLayout[0]->addWidget(_comboBox.get(), 300, Qt::AlignTop);


    _hBoxLayouts[1]->addWidget(_matrixInputView.get());


     _hBoxLayouts[2]->addLayout(_hBoxLayouts[1]);
     _hBoxLayouts[2]->addLayout(_vBoxLayout[0]);

     _hBoxLayouts[3]->addWidget(_computeButton.get(), 50, Qt::AlignRight);

     _vBoxLayout[1]->addLayout(_hBoxLayouts[2]);
     _vBoxLayout[1]->addLayout(_hBoxLayouts[3]);

     setLayout(_vBoxLayout[1]);

 }

