#ifndef CONTROLLERWINDOW_H
#define CONTROLLERWINDOW_H

#include <QWidget>
#include "newTextEdit.h"
#include "qcustomplot.h"
#include "plotwindow.h"

class QPushButton;
class TextEdit;

class mainWindow : public QWidget
{
   Q_OBJECT

public:
   mainWindow();

private slots:
   void showPlots();
   void calulate();

private:
  //  PreviewWindow *previewWindow;
  TextEdit *inputText;
  TextEdit *outputText;
  QPushButton *calcButton;
  QPushButton *showPlot;
  QPushButton *quitButton;
};

#endif
