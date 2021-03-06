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
    btnGroupLocation = new QButtonGroup(this);
    btnGroupLocation->addButton(ui->CrossRoad,0);
    btnGroupLocation->addButton(ui->ZhiEr,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(flag == false) {
        string url = "data.txt";
        obj.ReadFromFile(url);
        flag = true;
    }
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(5);
    painter.setPen(pen);
    for(unsigned i=0;i<lines.size();i++) {
        cout << "i=" << i << endl;
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
    int startPtnNum = obj.get_number(startPtn);
    int endPtnNum = obj.get_number(endPtn);
    if(startPtnNum == -1) {
        ui->startPtnError->setText(tr("出发地不存在！请重新输入"));
        fail = true;
    }
    if(endPtnNum == -1) {
        ui->EndPtnError->setText(tr("目的地不存在！请重新输入"));
        fail = true;
    }
    if(fail) {
        return;
    }

    ui->startPtnError->setText(tr(" "));
    ui->EndPtnError->setText(tr(" "));
    auto cache =  obj.find_a_driveway(startPtnNum, endPtnNum);
    if(cache.size() == 0) {
        ui->startPtnError->setText(tr("不能直接开车到达目的地"));
        return;
    }
cout << "Pass " << cache.size() << " points" << endl;

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int num1 = 0;
    int num2 = 0;
    for(unsigned i=0;i<cache.size()-1;i++) {
        myLine* pLine = new myLine;
        num1 = obj.get_number(obj.getName(cache[i]));
        num2 = obj.get_number(obj.getName(cache[i+1]));
        x1 = obj.getX(num1);
        y1 = obj.getY(num1);
        x2 = obj.getX(num2);
        y2 = obj.getY(num2);
        pLine->startPtn = QPoint(x1,y1);
        pLine->endPtn = QPoint(x2,y2);
        cout << "(" << x2 << "," << y2 << ")" << endl;
        this->lines.push_back(pLine);
    }
    update();
}

void MainWindow::on_StartWalk_clicked()
{
    bool fail = false;
    QString startPtnCache = ui->StartPtn->text();
    QString endPtnCache = ui->EndPtn->text();
    string startPtn = startPtnCache.toStdString();
    string endPtn = endPtnCache.toStdString();
    int startPtnNum = obj.get_number(startPtn);
    int endPtnNum = obj.get_number(endPtn);
    if(startPtnNum == -1) {
        ui->startPtnError->setText(tr("出发地不存在！请重新输入"));
        fail = true;
    }
    if(endPtnNum == -1) {
        ui->EndPtnError->setText(tr("目的地不存在！请重新输入"));
        fail = true;
    }
    if(fail) {
        return;
    }

    ui->startPtnError->setText(tr(" "));
    ui->EndPtnError->setText(tr(" "));
    auto cache =  obj.find_a_pavement(startPtnNum, endPtnNum);
    if(cache.size() == 0) {
        ui->startPtnError->setText(tr("不能直接走路到达目的地"));
        return;
    }
    cout << "Pass " << cache.size() << " points" << endl;

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int num1 = 0;
    int num2 = 0;
    for(unsigned i=0;i<cache.size()-1;i++) {

        myLine* pLine = new myLine;
        num1 = obj.get_number(obj.getName(cache[i]));
        num2 = obj.get_number(obj.getName(cache[i+1]));
        x1 = obj.getX(num1);
        y1 = obj.getY(num1);
        x2 = obj.getX(num2);
        y2 = obj.getY(num2);
        pLine->startPtn = QPoint(x1,y1);
        pLine->endPtn = QPoint(x2,y2);
        cout << "(" << x2 << "," << y2 << ")" << endl;
        this->lines.push_back(pLine);
    }
    update();
}
