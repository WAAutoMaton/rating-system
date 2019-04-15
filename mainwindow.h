#pragma once

#include <QMainWindow>
#include <core.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Class c;
    QVector<Student> sortedStudent;
    bool isForceExit = false;

private slots:
    void on_importButton_clicked();

    void on_refreshRankingButton_clicked();

    void on_rankingWidget_cellDoubleClicked(int row, int column);

    void on_readFileAction_triggered();

    void on_writeFileAction_triggered();

    void on_deleteAction_triggered();

    void on_forceExitAction_triggered();

private:
    Ui::MainWindow *ui;
};
