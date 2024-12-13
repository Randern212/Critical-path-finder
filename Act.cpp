#include "Act.h"
#include<vector>
#include<iostream>
#pragma once
Act::Act()
{

}
void Act::calcEF()
{
    EF=ES+duration;
}
void Act::calcLS()
{
    LS=LF-duration;
}
Act::Act(std::string n,int d)
{
    name=n;
    duration=d;
    calcEF();
}
Act::~Act()
{

}