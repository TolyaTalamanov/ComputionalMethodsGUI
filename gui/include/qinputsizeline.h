#ifndef QINPUTSIZELINE_H
#define QINPUTSIZELINE_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <memory>
using std::shared_ptr;

class QInputSizeLine : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindowView;
    explicit QInputSizeLine(QWidget *parent = 0);

signals:

public slots:
private:
    int                     _currentIndex;
    shared_ptr<QLabel>      _enterSizeLabel;
    QStringList              _sizesList;
    shared_ptr<QComboBox>   _sizesBox;
    shared_ptr<QHBoxLayout> _layout;
};

#endif // QINPUTSIZELINE_H
