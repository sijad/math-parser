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
    // out << std::fixed << std::setprecision(n) << a_value;
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
  inputText->setText("f(x)=cos(x)");

  calcButton = new QPushButton("&Calculate");
  givenIntegral = new QPushButton("&Given Integral");
  showPlot = new QPushButton("&Show Plot");
  quitButton = new QPushButton("&Quit");

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addStretch();
  layout->addWidget(inputText);
  layout->addWidget(outputText);
  layout->addWidget(calcButton);
  layout->addWidget(givenIntegral);
  layout->addWidget(showPlot);
  layout->addWidget(quitButton);

  inputText->setPlaceholderText("Function");
  outputText->setPlaceholderText("Answer goes here");

  connect(calcButton, SIGNAL(clicked()), this, SLOT(calulate()));
  connect(givenIntegral, SIGNAL(clicked()), this, SLOT(calcGivenIntegral()));
  connect(showPlot, SIGNAL(clicked()), this, SLOT(showPlots()));
  connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(layout);
  setLayout(mainLayout);

  setWindowTitle(tr("Eval Math By Sajjad Hashemian"));
}

void mainWindow::calcGivenIntegral() {
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
    fun = text.substr(text.find('=')+1);
      QMessageBox msgBox;
  if(params->size() == 1) {
      double lower = QInputDialog::getDouble(this, tr("Enter Lower Bound Value"), tr("Amount:"), 0, -2147483647, 2147483647, 7);
      double upper = QInputDialog::getDouble(this, tr("Enter Upper Bound Value"), tr("Amount:"), 0, -2147483647, 2147483647, 7);
    //   double n_val = QInputDialog::getDouble(this, tr("Enter N Value"), tr("Amount:"), 0, -2147483647, 2147483647, 7);
      if(lower < upper) {
          try {
            mathParser *amp = new mathParser(fun);
            // amp->add_var(params->at(0).toUtf8().constData(), lower);
            // long double a = amp->eval();
            // amp->add_var(params->at(0).toUtf8().constData(), upper);
            // long double b = amp->eval();

            // QString ans = QString(to_string_with_precision<long double> (simpson(amp, params->at(0).toUtf8().constData(), lower, upper, n_val), 15).c_str());
            QString ans = QString(to_string_with_precision<long double> (simpson(amp, params->at(0).toUtf8().constData(), lower, upper, 999), 15).c_str());
            outputText->setText(ans);

          }catch(std::runtime_error& e) {
              msgBox.setText(e.what());
              msgBox.setIcon(QMessageBox::Critical);
              msgBox.exec();
          }
      }else{
          msgBox.setText("Lower bound should be smaller than upper bound!");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
      }
  }else{
      msgBox.setText("Given integram must have exactly 1 parameter.");
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
  }
}

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
      bool ok = false;
      QString d = QInputDialog::getText(this, tr("Enter Value for `%1`").arg(*i), tr("Value:"), QLineEdit::Normal, "", &ok);
      if(!ok)
        d = "0";
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
    // if(params->size() <= 2) {
    if(params->size() <= 1) {
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
    //   msgBox.setText("Plot only works for less than 2 parameters.");
      msgBox.setText("Plot only works for functions with one parameter.");
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

long double mainWindow::simpson(mathParser *mp, std::string p, double a, double b, int n) {
  // double c = (a+b)/2.0;
  // double h3 = abs(b-a)/6.0;
  // return (long double) h3*(fk(a)+4.0*fk(c)+fk(b));
  long double h = (b-a) / n, x, r;
  char m = 0;
  long double s = 0.0;
  for(x = a; x <= b; x+=h) {
      mp->add_var(p, x);
      r = mp->eval();
      if(x == a || x == b) {
          s += r;
      }else{
          m = !m;
          s += r * (m+1) * 2.0;
      }
  }
  return s * (h/3.0);
}
