#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct balls{
    int xcenter,ycenter; 
    bool xdir,ydir;
    balls() : xcenter((rand() % 1240)- 620),ycenter((rand() % 680)- 340),xdir((rand()%2)==0),ydir((rand()%2)==0){}
};


int main(){

    balls* arr = new balls[100];
    for(int i=0;i<100;i++)
    for (int i = 0; i < 100; i++)
    {
        printf("%d %d %d %d\n",arr[i].xcenter,arr[i].ycenter,arr[i].xdir,arr[i].ydir);
    }
    
    return 0;
}