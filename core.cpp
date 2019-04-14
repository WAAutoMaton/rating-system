#include <bits/stdc++.h>
#include <core.h>

void Class::calcAllRating()
{
    for (auto &i : student) {
        i.rating[0] = 1500;
        i.vol[0] = 250;
    }
    for (int i = 1; i <= m; ++i) {
        calcRating(i);
    }
}

void Class::calcRating(int p)
{
    auto erf_1 = [](double x) {
        double l = -1e10, r = 1e10;
        for (int i = 1; i <= 100; ++i)
            if (erf((l + r) / 2) <= x)
                l = (l + r) / 2;
            else
                r = (l + r) / 2;
        return (l + r) / 2;
    };
    auto phi = [&](double x) { return sqrt(2) * erf_1(2 * x - 1); };
    struct node
    {
        double x;
        int y;
    };
    for (auto &i : student) {
        Q_ASSERT(i.score.size() >= p + 1);
        if (i.rating.size() < p + 1)
            i.rating.resize(p + 1);
        if (i.vol.size() < p + 1)
            i.vol.resize(p + 1);
    }
    double ave_rating = 0;
    int num = 0;
    QVector<node> q;
    QVector<int> Rank;
    Rank.resize(n + 1);
    q.push_back({ 0, 0 });
    for (auto &i : student)
        if (i.score[p] > 0) {
            ave_rating += i.rating[p - 1];
            q.push_back({ i.score[p], i.id });
            num++;
        }
    std::sort(q.begin() + 1, q.end(), [](const node &a, const node &b) { return a.x > b.x; });
    for (int i = 1; i <= num; ++i)
        if (abs(q[i].x - q[i - 1].x) < 1e-5)
            Rank[q[i].y] = i;
        else
            Rank[q[i].y] = Rank[q[i - 1].y];
    ave_rating /= num;
    double CF0 = 0, CF1 = 0;
    for (auto &i : student)
        if (i.score[p] > 0) {
            CF0 += pow(i.vol[p - 1], 2);
            CF1 += pow(i.rating[p - 1] - ave_rating, 2);
        }
    double CF = sqrt(CF0 / num + CF1 / (num - 1));
    for (auto &i : student)
        if (i.score[p] > 0) {
            double Erank = 0.5;
            for (auto &j : student)
                if (j.score[p] > 0)
                    Erank += 0.5
                        * (erf((j.rating[p - 1] - j.rating[p - 1])
                               / sqrt(2 * pow(i.vol[p - 1], 2) + 2 * pow(j.vol[p - 1], 2) + 1e-8))
                           + 1);
            double Epref = -phi((Erank - 0.5) / num);
            double Apref = -phi((Rank[i.id] - 0.5) / num);
            double PerfAs = i.rating[p - 1] + CF * (Apref - Epref);
            int content_num = 0;
            for (int j = 1; j < p; ++j) {
                if (i.score[j] > 0)
                    ++content_num;
            }
            // content_num += 4;
            double Weight = 1 / (1 - (0.42 / (content_num + 1) + 0.18)) - 1;
            if (i.rating[p - 1] >= 2600)
                Weight *= 0.8;
            else if (i.rating[p - 1] >= 2000)
                Weight *= 0.9;
            double Cap = 150 + 1500.0 / (content_num + 2);
            i.rating[p] = (i.rating[p - 1] + Weight * PerfAs) / (1 + Weight);
            i.rating[p] = std::min(i.rating[p], i.rating[p - 1] + Cap);
            i.rating[p] = std::max(i.rating[p], i.rating[p - 1] - Cap);
            i.vol[p] = sqrt(pow(i.rating[p] - i.rating[p - 1], 2) / Weight
                            + pow(i.vol[p - 1], 2) / (Weight + 1));
        } else {
            i.rating[p] = i.rating[p - 1];
            i.vol[p] = i.vol[p - 1];
        }
}

void Class::readFromFile(QString fileName)
{
    n = m = 0;
    idList.clear();
    student.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File Open Error";
        return;
    }
    QTextStream fin(&file);
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        Student s;
        s.id = i;
        fin >> s.name;
        s.score.push_back(0);
        s.rating.push_back(1500);
        s.vol.push_back(250);
        for (int i = 1; i <= m; ++i) {
            double t;
            fin >> t;
            s.score.push_back(t);
        }
        student.push_back(s);
        idList[s.name] = i;
    }
}

void Class::writeToFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "File Open Error";
        return;
    }
    QTextStream fout(&file);
    fout << n << " " << m << '\n';
    for (int i = 0; i < n; ++i) {
        fout << student[i].name << " ";
        for (int j = 1; j <= m; ++j) {
            fout << student[i].score[j] << " ";
        }
        fout << '\n';
    }
}

bool Class::importContent(QString data)
{
    QTextStream fin(&data, QIODevice::ReadOnly);
    for (auto &i : student) {
        if (i.score.size() < m + 2)
            i.score.resize(m + 2);
    }
    for (int i = 1; i <= n; ++i) {
        QString name;
        double score;
        fin >> name >> score;
        if (idList.count(name) == 0) {
            qDebug() << QString("第%2条，数据库中找不到学生%1").arg(name).arg(i);
            return false;
        }
        student[idList[name]].score[m + 1] = score;
    }
    m++;
    return true;
}
