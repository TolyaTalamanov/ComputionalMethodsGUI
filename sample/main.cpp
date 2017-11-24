#include "gui/include/mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "gui/include/matrixinputview.h"
#include "gui/include/mainwindowview.h"
#include "gui/include/control.h"
#include <memory>
#include "lib/include/icomputionalmethods.h"
#include "gui/include/qinputparamsline.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    unique_ptr<MainWindowView> mw(new MainWindowView);


    mw->show();
    return app.exec();
}
