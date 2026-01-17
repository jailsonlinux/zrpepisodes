#include "searchepisodes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("ZRP Buscador de episódios");
    a.setOrganizationName("ZRP testes");
    SearchEpisodes w;
    w.show();
    return a.exec();
}
