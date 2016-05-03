#include <QtCore/QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString s = "Hello, World";

    qDebug() << s;

    return a.exec();
}
