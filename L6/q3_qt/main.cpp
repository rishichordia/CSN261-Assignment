#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#define  ft float
using namespace std;

bool intersect(Segment* firstSeg, Segment* Secondseg, ft* x, ft *y)
{
    if (firstSeg->m == Secondseg->m)
    {
        return false;
    }
    else
    {
        ft slope1,slope2,intercept1,intercept2;
        slope1 = firstSeg->m;
        intercept1 = firstSeg->c;
        slope2 = Secondseg->m;
        intercept2 = Secondseg->c;
        *x = (intercept2-intercept1)/(slope1-slope2);
        *y = slope1*(*x) + intercept1;
        if (firstSeg->check(*x,*y) && Secondseg->check(*x,*y))
            return true;
        else
            return false;
        
    }
}


void linearFit(ft* x,ft* y,int n, ft* a, ft* b)
{
    ft summation_x = 0,summation_y = 0;
    for (int j = 0; j < n; j++)
    {
        summation_x += x[j];
        summation_y += y[j];
    }


    ft avgY = summation_y/n;
    ft avgX = summation_x/n;

    ft m = 0;
    ft temp = 0;
    for (int i = 0; i < n; ++i)
    {
        m += (x[i] - avgX)*(y[i]-avgY);
        temp += (x[i] - avgX) * (x[i] - avgX);
    }

    *a = m/temp;
    *b = avgY - (*a) * avgX;
}

int main(int argc, char *argv[])
{
    int number_of_lines;
        cout << "Enter the number of lines : ";
        cin >> number_of_lines;
        Segment** segments = new Segment*[number_of_lines];

        priority_queue <Vertex, vector<Vertex> , CompareQueue> que;
        cout << "Enter the coordinates space separated" << endl;
        for (int k = 0; k < number_of_lines; k++)
        {
            ft x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments[k] = new Segment(x1,y1,x2,y2);
            que.push(*(segments[k]->left));
            que.push(*(segments[k]->right));
        }

        set<Vertex,CompareSet> output;
        set<Segment*> active;

        while(que.empty() == false)
        {
            Vertex ver = que.top();
            if (ver.isLeft == true)
            {
                Segment* curr = (Segment*)ver.segment;
                for (auto itr = active.begin() ; itr != active.end() ; itr++)
                {
                    Segment* temp = *itr;
                    ft x,y;
                    bool is_intersecting = intersect(curr, temp,&x,&y);
                    if (is_intersecting)
                    {
                        Vertex ins(x,y);
                        output.insert(ins);
                    }
                }
                active.insert((Segment*)ver.segment);
            }
            else
                active.erase((Segment*)ver.segment);
            que.pop();
        }

        cout << "No. of intersection points: "<< output.size() << endl;
        for (auto it = output.begin(); it != output.end(); it++)
            cout << "(" << it->x << "," << it->y << ")" << endl;

        int n2 = output.size();
        ft* x = new ft[n2];
        ft* y = new ft[n2];
        int i = 0;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            x[i] = it->x;
            y[i] = it->y;
            i++;}
        ft a;
        ft b;

        linearFit(x,y,n2,&a,&b);
    QApplication app(argc, argv);
    MainWindow w(nullptr,x,y,number_of_lines,n2,segments,a,b);
    w.show();
    return app.exec();
}
