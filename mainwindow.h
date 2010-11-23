#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool setFileName(QString &path);

private:
    Ui::MainWindow *ui;
    scene *s;
    QString fileName;
private slots:
    void saveActualFile();
};

#endif // MAINWINDOW_H
