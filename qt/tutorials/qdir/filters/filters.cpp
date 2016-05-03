#include <QTextStream>
#include <QDir>

int main()
{
    QTextStream out(stdout);
    QDir dir;

    QStringList filters;
    filters << "*.c" << "*.c~";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        out << QString("%1").arg(fileInfo.fileName());
        out << endl;
    }
}
