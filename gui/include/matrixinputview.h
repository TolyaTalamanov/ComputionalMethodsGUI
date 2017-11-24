#ifndef MATRIXINPUTVIEW_H
#define MATRIXINPUTVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindowView;
class QMatrixInputView : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindowView;
    explicit QMatrixInputView(int size = 3, QWidget *parent = 0);


signals:
public:
    int           _size;
    QLineEdit**   _lineEdits;
    QLabel**      _qLabels;
    QHBoxLayout** _hLayout;
    QVBoxLayout*  _vLayout;
    QVBoxLayout*  _vLayoutFreeVal;
    QLineEdit**   _freeValLineEdit;
    QHBoxLayout*  _mainLayout;


public slots:
};

#endif // MATRIXINPUTVIEW_H
