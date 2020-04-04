#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input->setPlaceholderText("...");
    connect(ui->input,SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(searchClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::searchClicked()
{
    QString txt=ui->input->text(),means;
    ui->output->setPlainText(search(txt));
}
void Trie::insert( QString s,QString means)
{
    no_of_words++;
    Node* temp=root;
    for(int i=0;i<s.length();i++)
    {
        int index=s.at(i).toUpper().toLatin1() -65;
        if(!temp->children[index])
        {
            temp->children[index]=new Node;
            for(int i=0;i<26;i++)
                temp->children[index]->children[i]=nullptr;

        }
        temp=temp->children[index];
    }
    temp->end=no_of_words;
    meaning<<means;
}
QString Trie::search(QString s)
{
    Node* temp=root;
    for(int i=0;i<s.length();i++)
    {
        int index=s.at(i).toUpper().toLatin1() -65;
        if(!temp->children[index])
            return "Word Not Found";
        temp=temp->children[index];
    }
    if(temp->end!=-1)
    return meaning.at(temp->end);
}
