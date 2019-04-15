#include "studentinfomationdialog.h"
#include "ui_studentinfomationdialog.h"
#include "core.h"

#include <algorithm>

StudentInfomationDialog::StudentInfomationDialog(QWidget *parent, const Student &student)
    : QDialog(parent)
    , ui(new Ui::StudentInfomationDialog)
{
    setModal(true);
    ui->setupUi(this);
    QRect screenRect = QGuiApplication::screens().at(0)->geometry();
    this->setGeometry(50, 50, screenRect.width() - 100, screenRect.height() - 100);
    ui->nameLabel->setText(student.name);
    int m = student.score.size() - 1;
    ui->ratingTableWidget->setColumnCount(4);
    ui->ratingTableWidget->setRowCount(m);
    QStringList header;
    header << "成绩"
           << "rating分"
           << "rating分变化"
           << "波动度";
    ui->ratingTableWidget->setHorizontalHeaderLabels(header);
    for (int i = 1; i <= m; ++i) {
        ui->ratingTableWidget->setItem(i - 1, 0,
                                       new QTableWidgetItem(std::abs(student.score[i])<1e-5?QString("未参加"):QString::number(student.score[i])));
        ui->ratingTableWidget->setItem(
            i - 1, 1, new QTableWidgetItem(QString::number(int(student.rating[i]))));
        ui->ratingTableWidget->setItem(
            i - 1, 2,
            new QTableWidgetItem(QString::number(int(student.rating[i] - student.rating[i - 1]))));
        ui->ratingTableWidget->setItem(i - 1, 3,
                                       new QTableWidgetItem(QString::number(int(student.vol[i]))));
    }
    auto series = new QLineSeries();
    series->setName("rating");
    // series->setUseOpenGL(true);
    QPen seriesPen(Qt::blue);
    seriesPen.setWidth(7);
    series->setPen(seriesPen);
    // series->setColor(QColor(255, 0, 255));
    series->setVisible(true);
    series->setPointLabelsVisible(true);
    series->setPointsVisible(true);
    series->setPointLabelsClipping(false);
    for (int i = 0; i <= m; ++i) {
        series->append(i, int(student.rating[i]));
    }

    auto chart = new QChart();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(series);
    chart->createDefaultAxes();
    QFont font;
    font.setPixelSize(70);
    chart->setFont(font);
    // chart->legend()->setBackgroundVisible(true);
    chart->legend()->setVisible(false);

    auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->tabWidget->insertTab(1, chartView, "rating曲线");
}

StudentInfomationDialog::~StudentInfomationDialog()
{
    delete ui;
}
