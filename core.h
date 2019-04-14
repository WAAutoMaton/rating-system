#pragma once
#include <QtCore>
struct Student
{
    int id;
    QString name;
    QVector<double> score;
    QVector<double> rating;
    QVector<double> vol;
};
class Class
{
public:
    QMap<QString, int> idList;
    QVector<Student> student;
    int n, m;
    void calcAllRating();
    void calcRating(int);
    void readFromFile(QString = "data.txt");
    void writeToFile(QString = "data.txt");
    bool importContent(QString);
};
