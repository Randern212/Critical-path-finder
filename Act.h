#ifndef ACT_H
#define ACT_H
#include<iostream>
#include<vector>
#pragma once

class Act
{
public:
    Act();
    Act(std::string n,int d);
    void calcEF();
    void calcLS();
    std::string name;
    std::vector<int> succi;
    std::vector<int> predi;
    int ES=0;
    int LF=-1;
    int EF , LS, duration;
    ~Act();
private:

};

#endif