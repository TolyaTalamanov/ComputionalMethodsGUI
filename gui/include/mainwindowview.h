#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H
#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "matrixinputview.h"
#include <iostream>
#include <random>
#include "control.h"
#include "lib/include/icomputionalmethods.h"
#include "qanswerform.h"
#include <QMessageBox>
#include <gui/include/qinputparamsline.h>
#include <gui/include/qinputsizeline.h>

using namespace std;

class MainWindowView : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindowView(QWidget *parent = 0);
    ~MainWindowView(){
        delete _answerForm;
    }


public slots:
    void incSize(){
        if(_size <= 10){
            setFixedSize(size().width() + 96, size().height() + 26);
            _matrixInputView.reset(new QMatrixInputView(++_size));
            _hBoxLayouts[1]->addWidget(_matrixInputView.get());

        }
    }
    void decSize(){
        if(_size >= 3){
            setFixedSize(size().width() - 96, size().height() - 26);
            _matrixInputView.reset(new QMatrixInputView(--_size));
            _hBoxLayouts[1]->addWidget(_matrixInputView.get());
        }
    }
    void fillRandom(){
        std::uniform_int_distribution<int> d(0, 50);
        std::mt19937 g{std::random_device()()};
        for(int i = 0; i < _size;i++){
            int f_val = d(g);
            _matrixInputView->_freeValLineEdit[i]->setText(QString::number(f_val));
            for(int j = 0; j < _size; j++){
            int val = d(g);
            _matrixInputView->_lineEdits[i * _size + j]->setText(QString::number(val));
          }
        }
    }
    void clear(){
        for(int i = 0; i < _size;i++){
            _matrixInputView->_freeValLineEdit[i]->clear();
            for(int j = 0; j < _size; j++){
            _matrixInputView->_lineEdits[i * _size + j]->clear();
          }
        }
    }
    void getMatrixValInfo(Matrix& m, vector<double>& b ){
        int size = _matrixInputView->_size;
        for(int i = 0; i < size;i++ ){
            b[i] = (_matrixInputView->_freeValLineEdit[i]->text().toDouble());
            for(int j = 0; j < size;j++ ){
                m[i].emplace_back(_matrixInputView->_lineEdits[i * size + j ]->text().toDouble());
            }
        }
    }
    void setSize(){
        int nextIndex = _inputSizeLine->_sizesBox->currentIndex() + 2;
        int dSize = nextIndex - _inputSizeLine->_currentIndex;
        setFixedSize(size().width() + dSize * 96, size().height() + dSize * 26);
        _matrixInputView.reset(new QMatrixInputView(nextIndex));
        _size = nextIndex;
        _hBoxLayouts[1]->addWidget(_matrixInputView.get());
        _inputSizeLine->_currentIndex = nextIndex;
    }

    void compute(){
        Matrix m(_matrixInputView->_size);
        vector<double> b(_matrixInputView->_size);
        getMatrixValInfo(m, b);
        vector<double> answer;
        if(_comboBox->currentText() == "Метод Гаусса"){
            auto method = IComputionalMethod::create(Implementation::GAUSS);
            try{
                answer = method->compute(m, b);
            }
            catch(QString& qmsg){
              QMessageBox::information(NULL, QObject::tr("Ошибка"), QObject::tr(qmsg.toStdString().c_str()));
              return;
            }
        }
        if(_comboBox->currentText() == "Метод Крамера"){
            auto method = IComputionalMethod::create(Implementation::KRAMMER);
            try{
                answer = method->compute(m, b);
            }
            catch(QString& qmsg){
              QMessageBox::information(NULL, QObject::tr("Ошибка"), QObject::tr(qmsg.toStdString().c_str()));
              return;
            }
        }
        if(_comboBox->currentText() == "Метод Зейделя"){
            auto method = IComputionalMethod::create(Implementation::SEIDEL);
            method->setEpsilon(_epsilon->getParams());
            try{
                answer = method->compute(m, b);
            }
            catch(QString& qmsg){
              QMessageBox::information(NULL, QObject::tr("Ошибка"), QObject::tr(qmsg.toStdString().c_str()));
              return;
            }
        }
        if(_comboBox->currentText() == "Метод верхней релаксации"){
            auto method = IComputionalMethod::create(Implementation::UPPER_RELAXATION);
            method->setEpsilon(_epsilon->getParams());
            method->setOmega(_omega->getParams());
            try{
                answer = method->compute(m, b);
            }
            catch(QString& qmsg){
              QMessageBox::information(NULL, QObject::tr("Ошибка"), QObject::tr(qmsg.toStdString().c_str()));
              return;
            }
        }
        if(_comboBox->currentText() == "Метод простых итераций"){
            auto method = IComputionalMethod::create(Implementation::SIMPLE_ITERATION);
            method->setEpsilon(_epsilon->getParams());
            try{
                answer = method->compute(m, b);
            }
            catch(QString& qmsg){
              QMessageBox::information(NULL, QObject::tr("Ошибка"), QObject::tr(qmsg.toStdString().c_str()));
              return;
            }
        }

        _answerForm = new QAnswerForm();
        _answerForm->setAnswer(answer);
        _answerForm->show();

    }

signals:
private:
    shared_ptr<QPushButton>              _computeButton;
    shared_ptr<QPushButton>              _clearButton;
    shared_ptr<QPushButton>              _plusButton;
    shared_ptr<QPushButton>              _minusButton;
    shared_ptr<QPushButton>              _generateButton;
    shared_ptr<QMatrixInputView>         _matrixInputView;
    shared_ptr<QComboBox>                _comboBox;
    shared_ptr<QInputParamsLine>         _omega;
    shared_ptr<QInputParamsLine>         _epsilon;
    shared_ptr<QInputSizeLine>           _inputSizeLine;
    QStringList                          _stringList;
    QAnswerForm*                         _answerForm;
    std::unique_ptr<IComputionalMethod>  _method;
    QVBoxLayout*                         _vBoxLayout[4];
    QHBoxLayout*                         _hBoxLayouts[4];
    int                                  _size = 3;
    Control*                             _contol;
    QLabel                               _paramsLbl[2];
    QLineEdit                            _paramsEdit[2];

};

#endif // MAINWINDOWVIEW_H
