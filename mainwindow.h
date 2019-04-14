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

private slots:
    void on_importButton_clicked();

    void on_writeFileButton_clicked();

    void on_refreshRankingButton_clicked();

    void on_rankingWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};
