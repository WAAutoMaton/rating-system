#pragma once

#include <QDialog>
#include <QtCharts>

struct Student;

namespace Ui {
class StudentInfomationDialog;
}

class StudentInfomationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInfomationDialog(QWidget *parent, const Student &);
    ~StudentInfomationDialog();

private:
    Ui::StudentInfomationDialog *ui;
};
