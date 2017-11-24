#ifndef QANSWERFORM_H
#define QANSWERFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

using namespace std;
class QAnswerForm : public QWidget
{
    Q_OBJECT
public:
    explicit QAnswerForm(QWidget *parent = 0);
    void setAnswer( const vector<double>& answer ){

        size = answer.size();
        main       = new QVBoxLayout();
        textLayout = new QHBoxLayout();
        valsLayout = new QVBoxLayout();
        text = new QLabel();
        QFont font =  text->font();
        font.setPixelSize(30);
        text->setFont(font);
        text->setText("Решение системы");
        vals = new QLabel*[answer.size()];
        for(int i = 0 ; i < answer.size(); i++){
            vals[i] = new QLabel();
            QFont font =  vals[i]->font();
            font.setPixelSize(24);
            vals[i]->setFont(font);
            vals[i]->setText("X" + QString::number(i) + " = " + QString::number(answer[i]));
            valsLayout->addWidget(vals[i]);
        }

        textLayout->addWidget(text);
        main->addLayout(textLayout);
        main->addLayout(valsLayout);
        setLayout(main);
    }
    virtual ~QAnswerForm(){
        delete main;
        delete textLayout;
        delete valsLayout;
        delete text;
        for(int i = 0 ; i < size;i++){
            delete vals[i];
        }
        delete[] vals;
    }

signals:

public slots:
private:
    QVBoxLayout *main;
    QHBoxLayout *textLayout;
    QVBoxLayout *valsLayout;
    QLabel *text;
    QLabel** vals;
    int size;

};

#endif // QANSWERFORM_H
