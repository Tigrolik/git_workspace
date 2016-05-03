#include <QTextStream>
#include <QTime>

int main()
{
    QTextStream out(stdout);

    QTime qtime = QTime::currentTime();
    QString stime = qtime.toString(Qt::LocalDate);

    out << stime << endl;
}
