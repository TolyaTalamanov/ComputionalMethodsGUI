#ifndef QINPUTPARAMSLINE_H
#define QINPUTPARAMSLINE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <memory>
using std::shared_ptr;

class QInputParamsLine : public QWidget
{
    Q_OBJECT
public:
    explicit QInputParamsLine(QWidget *parent = 0);

    void setParamsName(const QString& name){
        _paramsName->setText(name);
    }
    double getParams(){
        return _paramsEnterField->text().toDouble();
    }

signals:

public slots:
private:
    shared_ptr<QHBoxLayout>    _plane;
    shared_ptr<QLabel>         _paramsName;
    shared_ptr<QLineEdit>      _paramsEnterField;
};

#endif // QINPUTPARAMSLINE_H
