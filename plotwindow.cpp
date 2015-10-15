/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2015 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 25.04.15                                             **
**          Version: 1.3.1                                                **
****************************************************************************/

#include "plotwindow.h"
#include "ui_plotwindow.h"

QVector<double> generateRange(double a, double b, double c) {
    QVector<double> array;
    while(a <= c) {
        array.push_back(a);
        a += b;         // could recode to better handle rounding errors
    }
    return array;
}

QVector<double> linspace(double a, double b, int n) {
    QVector<double> array;
    double step = (b-a) / (n-1);

    while(a <= b) {
        array.push_back(a);
        a += step;           // could recode to better handle rounding errors
    }
    return array;
}

plotwindow::plotwindow(QWidget *parent, mathParser *m, QVector<QString> * p) :
  QMainWindow(parent),
  ui(new Ui::plotwindow)
{
  mp = m;
  mp_params = p;
  ui->setupUi(this);
  setupPlot();

  // configure scroll bars:
  // Since scroll bars only support integer values, we'll set a high default range of -500..500 and
  // divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
  // axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
  // just increase the the minimum/maximum values of the scroll bars as needed.
  ui->horizontalScrollBar->setRange(-500, 500);
  ui->verticalScrollBar->setRange(-500, 500);

  // create connection between axes and scroll bars:
  connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
  connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
  connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
  connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

  // initialize axis range (and scroll bar positions via signals we just connected):
  ui->plot->xAxis->setRange(0, 6, Qt::AlignCenter);
  ui->plot->yAxis->setRange(0, 10, Qt::AlignCenter);
}

plotwindow::~plotwindow()
{
  delete ui;
}

void plotwindow::setupPlot()
{
  if(mp != NULL && mp_params != NULL && mp_params->size() <= 2) {
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::blue));
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::red));
    // QVector<double> x = generateRange(-100,100,0.01);
    QVector<double> x = linspace(-10.0,10.0,500.0);
    QVector<double> y(x.size());
    std::string pn0;
    std::string pn1;
    if(mp_params->size() <= 2) {
      pn0 = mp_params->at(0).toUtf8().constData();
    }
    if(mp_params->size() == 2) {
      pn1 = mp_params->at(1).toUtf8().constData();
    }
    FOR_EACH_ENUMERATE(j, i, x) {
      if(mp_params->size() == 1) {
        mp->add_var(pn0, (long double) *i);
        y[j] = (double) mp->eval();
      }else if(mp_params->size() == 2) {
        mp->add_var(pn0, (long double) *i);
        // mp->add_var(pn1, 0.0);
        // y[j] = (double) mp->eval();

        // mp->add_var(pn0, 0.0);
        mp->add_var(pn1, (long double) *i);
        // *i = (double) mp->eval();

        y[j] = (double) mp->eval();

      }
    }
    ui->plot->graph(0)->setData(x, y);
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  }
}

void plotwindow::horzScrollBarChanged(int value)
{
  if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
    ui->plot->replot();
  }
}

void plotwindow::vertScrollBarChanged(int value)
{
  if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
    ui->plot->replot();
  }
}

void plotwindow::xAxisChanged(QCPRange range)
{
  ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void plotwindow::yAxisChanged(QCPRange range)
{
  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}
