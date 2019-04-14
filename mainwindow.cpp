#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

#include <studentinfomationdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c.readFromFile();
    c.calcAllRating();
    qDebug() << c.student.size();
    for (auto &i : c.student) {
        qDebug() << i.name << " " << i.rating[c.m] << " " << i.vol[c.m];
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_importButton_clicked()
{
    QString data = ui->importTextEdit->toPlainText();
    bool ok = c.importContent(data);
    if (ok) {
        QMessageBox::information(this, "提示",
                                 QString("导入考试成绩成功，该场考试为第%1场考试").arg(c.m));
    } else {
        QMessageBox::information(this, "提示", QString("导入考试成绩失败，请检查数据是否有误"));
    }
}

void MainWindow::on_writeFileButton_clicked()
{
    c.writeToFile();
    QMessageBox::information(this, "提示", "保存数据成功");
}

void MainWindow::on_refreshRankingButton_clicked()
{
    ui->rankingWidget->clear();
    ui->rankingWidget->setRowCount(c.n);
    ui->rankingWidget->setColumnCount(3);
    // ui->rankingWidget->resize(c.n, 3);
    QStringList header;
    header << "排名"
           << "姓名"
           << "rating分";
    ui->rankingWidget->setHorizontalHeaderLabels(header);
    auto student = c.student;
    std::sort(student.begin(), student.end(),
              [&](const Student &a, const Student &b) { return a.rating[c.m] > b.rating[c.m]; });
    for (int i = 0; i < c.n; ++i) {
        ui->rankingWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->rankingWidget->setItem(i, 1, new QTableWidgetItem(student[i].name));
        ui->rankingWidget->setItem(
            i, 2, new QTableWidgetItem(QString::number(int(student[i].rating[c.m]))));
    }
    sortedStudent = student;
}

void MainWindow::on_rankingWidget_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column)
    qDebug() << "Clicked" << row;
    auto widget = new StudentInfomationDialog(this, sortedStudent[row]);
    widget->show();
}
