#include <QtGui>
#include <cctype>
#include <string>
#include <iomanip>

#include "mainWindow.h"
#include "evalMath/mathParser.hpp"

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

mainWindow::mainWindow()
{
  //  previewWindow = new PreviewWindow(this);
  inputText = new TextEdit;
  outputText = new TextEdit;

  QTextCursor textCursor;
  textCursor.setPosition(0, QTextCursor::MoveAnchor);
  inputText->setTextCursor( textCursor );
  inputText->setText("f(x)=cos(deg(x))");

  calcButton = new QPushButton("&Calculate");
  showPlot = new QPushButton("&Show Plot");
  quitButton = new QPushButton("&Quit");

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addStretch();
  layout->addWidget(inputText);
  layout->addWidget(outputText);
  layout->addWidget(calcButton);
  layout->addWidget(showPlot);
  layout->addWidget(quitButton);

  inputText->setPlaceholderText("Function");
  outputText->setPlaceholderText("Answer goes here");

  connect(calcButton, SIGNAL(clicked()), this, SLOT(calulate()));
  connect(showPlot, SIGNAL(clicked()), this, SLOT(showPlots()));
  connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(layout);
  setLayout(mainLayout);

  setWindowTitle(tr("Eval Math By Sajjad Hashemian"));
}

void mainWindow::calulate() {
  QString t = inputText->toPlainText();
  std::string text = t.toUtf8().constData();
  if (!t.isEmpty() && t != inputText->getPlaceholderText()) {
    std::string fun = text.substr(text.find('('), text.find('=') - text.find('('));
    QVector<QString> params;
    std::string buff;
    for(unsigned long i=0;i<fun.length();++i) {
      if(fun[i] != ' ' && fun[i] != '(' && fun[i] != ')') {
        if(fun[i] != ',')
          buff += fun[i];
        else if(!buff.empty()) {
          params.push_back(QString(buff.c_str()));
          buff = "";
        }
      }
    }
    if(!buff.empty()) {
      params.push_back(QString(buff.c_str()));
    }
    fun = text.substr(text.find('=')+1);
    mathParser *mp = new mathParser(fun);
    FOR_EACH(i, params) {
      double d = QInputDialog::getDouble(this, tr("Enter Value for `%1`").arg(*i), tr("Amount:"), 0, -2147483647, 2147483647, 7);
      mp->add_var(i->toUtf8().constData(), (long double) d);
    }
    try {
      QString ans = QString(to_string_with_precision<long double> (mp->eval(), 15).c_str());
      outputText->setText(ans);
    }catch(runtime_error& e) {
      QMessageBox msgBox;
      msgBox.setText(e.what());
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

void mainWindow::showPlots() {
  QString t = inputText->toPlainText();
  std::string text = t.toUtf8().constData();
  if (!t.isEmpty() && t != inputText->getPlaceholderText()) {
    std::string fun = text.substr(text.find('('), text.find('=') - text.find('('));
    QVector<QString> *params = new QVector<QString>();
    std::string buff;
    for(unsigned long i=0;i<fun.length();++i) {
      if(fun[i] != ' ' && fun[i] != '(' && fun[i] != ')') {
        if(fun[i] != ',')
          buff += fun[i];
        else if(!buff.empty()) {
          params->push_back(QString(buff.c_str()));
          buff = "";
        }
      }
    }
    if(!buff.empty()) {
      params->push_back(QString(buff.c_str()));
    }
    if(params->size() <= 2) {
      fun = text.substr(text.find('=')+1);
      mathParser *mp = new mathParser(fun);
      try {
        plotwindow *plotwin = new plotwindow(0, mp, params);
        plotwin->show();
      }catch(runtime_error& e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
      }
    }else{
      QMessageBox msgBox;
      msgBox.setText("Plot only works for less than 1 parameter.");
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}
