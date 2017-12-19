#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "QPainter"
#include <iostream>

using namespace std;
Map obj;
bool flag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(flag == false) {
        string url = "data1.txt";
        obj.ReadFromFile(url);
        flag = true;
    }
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(5);
    painter.setPen(pen);
    for(unsigned i=0;i<lines.size();i++) {
        myLine* pLine = lines[i];
        painter.drawLine(pLine->startPtn, pLine->endPtn);
    }
    lines.clear();
}

void MainWindow::on_pushButton_clicked()
{
    int x = obj.getX(0);
    int y = obj.getY(0);
    myLine* pLine1 = new myLine;
    pLine1->startPtn = QPoint(0,0);
    pLine1->endPtn = QPoint(x,y);
    this->lines.push_back(pLine1);
    update();
    string name =  obj.getName(0);
    string info =  obj.getInfo(0);

    ui->Location->setText(QString::fromStdString(name));
    ui->Info->setText(QString::fromStdString(info));
}

void MainWindow::on_StartDrive_clicked()
{
    bool fail = false;
    QString startPtnCache = ui->StartPtn->text();
    QString endPtnCache = ui->EndPtn->text();
    string startPtn = startPtnCache.toStdString();
    string endPtn = endPtnCache.toStdString();
    if(obj.get_number(startPtn) == -1) {
        ui->startPtnError->setText(tr("出发地不存在！请重新输入"));
        fail = true;
    }
    if(obj.get_number(endPtn) == -1) {
        ui->EndPtnError->setText(tr("目的地不存在！请重新输入"));
        fail = true;
    }
    if(fail) {
        return;
    }

    ui->startPtnError->setText(tr(" "));
    ui->EndPtnError->setText(tr(" "));

}

void MainWindow::on_StartWalk_clicked()
{
    bool fail = false;
    QString startPtnCache = ui->StartPtn->text();
    QString endPtnCache = ui->EndPtn->text();
    string startPtn = startPtnCache.toStdString();
    string endPtn = endPtnCache.toStdString();
    if(obj.get_number(startPtn) == -1) {
        ui->startPtnError->setText(tr("出发地不存在！请重新输入"));
        fail = true;
    }
    if(obj.get_number(endPtn) == -1) {
        ui->EndPtnError->setText(tr("目的地不存在！请重新输入"));
        fail = true;
    }
    if(fail) {
        return;
    }

    ui->startPtnError->setText(tr(" "));
    ui->EndPtnError->setText(tr(" "));
}
