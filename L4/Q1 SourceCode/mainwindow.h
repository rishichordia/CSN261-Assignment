#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class Node{
public:
    Node* children[26];
    Node()
    {
        for(int i=0;i<26;i++)
            children[i]=nullptr;
    }
    int end=-1;
};


class Trie{

public:
    QStringList meaning;
    Node* root;
    int no_of_words;
    Trie()
    {
        root=new Node();
        no_of_words=-1;
    }
    ~Trie()
    {
        delete root;
    }
    void insert(QString s,QString means);
    QString search(QString word);
};
class MainWindow : public QMainWindow,public Trie
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void searchClicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
