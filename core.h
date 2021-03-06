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
    bool readFromFile(QString = "data.txt");
    bool writeToFile(QString = "data.txt");
    bool importContent(QString);
    void deleteContent(int p);
};
