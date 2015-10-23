#include <QtGui>
#include <cctype>
#include <string>
#include <iomanip>

#include "mainWindow.h"
#include "evalMath/mathParser.h"

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << a_value;
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
  inputText->setText("f(x)=cos(x)");

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
      QString d = QInputDialog::getText(this, tr("Enter Value for `%1`").arg(*i), tr("Amount:"));
      long double d2;
      try {
        mathParser *mp2 = new mathParser(d.toUtf8().constData());
        d2 = mp2->eval();
      }catch(std::runtime_error& e) {
        d2 = d.toDouble();
      }

      mp->add_var(i->toUtf8().constData(), d2);
    }
    try {
      QString ans = QString(to_string_with_precision<long double> (mp->eval(), 15).c_str());
      outputText->setText(ans);
    }catch(std::runtime_error& e) {
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
    }catch(std::runtime_error& e) {
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
