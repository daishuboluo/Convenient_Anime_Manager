#include "anime_management_homepage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Jia_xin_jia_mian");
    QApplication::setApplicationName("Convenient_Anime_Manager");
    QApplication::setApplicationVersion("0.0.1");

    Anime_Management_Homepage w;
    w.show();
    return a.exec();
}
