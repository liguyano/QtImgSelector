#include <QApplication>
#include <QPushButton>
#include "AiImgSelector.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QStringList imgs;
    imgs<<"./a.png"<<"./b.jpg"<<"a1.jpg"
    ;
    ImageSelectionWidget mis(imgs);
    mis.show();
    mis.resize(500,400);
    return QApplication::exec();
}
