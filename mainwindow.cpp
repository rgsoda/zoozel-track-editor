#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QFile>
#include "scene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    s = new scene;
    s->setParent(this);
    QMenuBar *mbar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu(tr("&File"), this);

    mbar->addMenu(fileMenu);

    this->setMenuBar(mbar);
    fileMenu->addAction(tr("&Save..."), this, SLOT(saveActualFile()), QKeySequence::Save);
    setCentralWidget(s);
}

MainWindow::~MainWindow()
{
    delete s;

}

void MainWindow::saveActualFile() {
    s->saveActualFile();
}

bool MainWindow::setFileName(QString &path) {
    if (!path.isEmpty()) {
        QFile file(path);
        if (file.open(QFile::ReadOnly)) {
            s->setTrack(path);
            return true;
        }
    }
    return false;
}
