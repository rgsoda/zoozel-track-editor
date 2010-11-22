#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

#include "scene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    s = new scene;
    QMenuBar *mbar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu(tr("&File"), this);

    mbar->addMenu(fileMenu);

    this->setMenuBar(mbar);
    fileMenu->addAction(tr("&Save..."), this, SLOT(saveActualFile()), QKeySequence::Save);
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("ready",100);
    setCentralWidget(s);
    resize(900,700);
}

MainWindow::~MainWindow()
{
    delete s;

}

void MainWindow::saveActualFile() {
    s->saveActualFile();
}
