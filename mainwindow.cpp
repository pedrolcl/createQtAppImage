#include <QLabel>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto w = new QLabel("Qt AppImage Works!", this);
    w->setAlignment(Qt::AlignCenter);
    setCentralWidget(w);
}

MainWindow::~MainWindow() = default;
