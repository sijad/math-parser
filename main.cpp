#include <QApplication>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   mainWindow mw;
   mw.show();
   return app.exec();
}
