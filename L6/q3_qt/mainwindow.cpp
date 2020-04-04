#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ft float
MainWindow::MainWindow(QWidget *parent, ft* x, ft* y,int n1,int n2, Segment** segments, ft a, ft b)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->x = x;
    this->y = y;
    this->n1 = n1;
    this->n2 = n2;
    this->a = a;
    this->b = b;
    this->segments = segments;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter write_on_screen(this);
    QPen points;
    QPen text;

    text.setWidth(2);

    points.setCapStyle(Qt::RoundCap);
    points.setWidth(4);

    write_on_screen.drawText(QPoint(10,20),"number of intersections : " + QString::number(this->n2));
    write_on_screen.setPen(Qt::blue);
    write_on_screen.drawText(QPoint(10,40),"The fit line is of the form "+QString::number(this->a)+"x + "+QString::number(this->b));

    for (int j = 0; j < n1; j++) {
        Segment* seg = segments[j];
        QPointF p1(seg->left->x,seg->left->y);
        QPointF p2(seg->right->x,seg->right->y);
        write_on_screen.setPen(Qt::black);
        write_on_screen.drawLine(p1,p2);
        write_on_screen.setPen(points);
        write_on_screen.drawPoint(p1);
        write_on_screen.drawPoint(p2);
        write_on_screen.setPen(text);
        write_on_screen.drawText(p1,"("+QString::number(p1.rx())+","+QString::number(p1.ry())+")");
        write_on_screen.drawText(p2,"("+QString::number(p2.rx())+","+QString::number(p2.ry())+")");
    }

    points.setColor(Qt::red);
    text.setColor(Qt::red);
    for (int k = 0; k < n2; k++) {
        QPointF p(x[k],y[k]);
        write_on_screen.setPen(points);
        write_on_screen.drawPoint(p);
        write_on_screen.setPen(text);
        write_on_screen.drawText(p,"("+QString::number(p.rx())+","+QString::number(p.ry())+")");
    }

    ft y1 = b;
    ft y2 = (a*1000) + b;
    write_on_screen.setPen(Qt::blue);
    write_on_screen.drawLine(QPointF(0,y1),QPointF(1000,y2));

}

