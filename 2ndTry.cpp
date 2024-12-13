#include <iostream>
#include "Act.cpp"
#include<vector>
#include<queue>
void displayDepMat(std::vector<std::pair<bool,std::vector<int>>> depMatrix)
{
    std::cout<<"======================================================================================\n";
    for (size_t i = 0; i < depMatrix.size(); i++)
    {
        for (size_t j = 0; j < depMatrix[i].second.size(); j++)
        {
            std::cout<<depMatrix[i].second[j]<<"\t";
        }
        std::cout<<"\n";
    }
    std::cout<<"======================================================================================\n";
}
std::vector<Act> createActList()
{
    int flag;
    std::cout<<"Enter the number of activities: ";
    std::cin>>flag;
    std::cout<<"\n";

    std::vector<Act> acList;
    int duration;
    std::string name;
    for(int i=0;i<flag;i++)
    {
        std::cout<<"enter the activity name, duration\n";
        std::cin>> name>>duration;
        Act act = Act(name,duration);
        acList.push_back(act);
    }
    return acList;
}

std::vector<std::pair<bool,std::vector<int>>> createDepMat(std::vector<Act> &acList)
{
    std::vector<std::pair<bool,std::vector<int>>> depMatrix(acList.size(),std::make_pair(false,std::vector<int>(acList.size(),0)));
    int inp,n;
    for(int i=0;i<acList.size();i++)
    {
        std::cout<<"How many activities does activity: "<<acList[i].name<<" have?\n";
        std::cin>>n;
        if(n>0)
        {
            std::cout<<"for Activity: "<<acList[i].name<<" enter its dependencies(as indexed)\n";
            for(int k=0;k<n;k++)
            {
                std::cin>>inp;
                acList[i].predi.push_back(inp);
            }
            for(int item:acList[i].predi)
                depMatrix[i].second[item]=1;
        }
        else
        {
            depMatrix[i].first=true;
            acList[i].ES=0;
            acList[i].calcEF();
        }
    }
    return depMatrix;
}

std::vector<std::pair<bool,std::vector<int>>> DepToAdjMat(std::vector<std::pair<bool,std::vector<int>>> depMat)
{
    std::vector<std::pair<bool,std::vector<int>>> adjMat(depMat);
    for(int i = 0; i < depMat.size(); i++)
    {
        for (int j = 0; j < depMat.size(); j++)
        {
            adjMat[j].second[i]=depMat[i].second[j];
        }
    }
    return adjMat;
}

void assignSucci(std::vector<Act> &acList,std::vector<std::pair<bool,std::vector<int>>> adjMat)
{
    for(int i=0;i<acList.size();i++)
    {
        for (int j = 0; j < adjMat[i].second.size(); j++)
        {
            if(adjMat[i].second[j]==1)
                acList[i].succi.push_back(j);
        }
        
    }
}

void recForward(Act &act,std::vector<Act> &acList)
{
    for(int item: act.succi)
    {
        acList[item].ES=std::max(acList[item].ES,act.EF);
        acList[item].calcEF();
        recForward(acList[item],acList);
    }
}
void forwardPass(std::vector<Act> &acList,std::vector<std::pair<bool,std::vector<int>>> adjMatrix)
{
    std::cout<<"======================================================================================\n";
    for(int i=0;i<acList.size();i++)
    {
        if(adjMatrix[i].first)
        {
            recForward(acList[i],acList);
        }
    }
    for(Act item:acList)
    {
        std::cout<<item.name<<" : "<<item.ES<<"\t"<<item.EF<<"\n";
    }
    std::cout<<"======================================================================================\n";
}
void recBackward(Act &act,std::vector<Act> &acList)
{
    for(int item:act.predi)
    {
        if(acList[item].LF<=-1)
            acList[item].LF=act.LS;
        else
            acList[item].LF=std::min(acList[item].LF,act.LS);
        acList[item].calcLS();
        recBackward(acList[item],acList);
    }
}
void backwardPass(std::vector<Act> &acList)
{
    std::cout<<"======================================================================================\n";
    int maxEF=0;
    for(Act &item:acList)
    {
        maxEF=std::max(maxEF,item.EF);
    }

    for (int i = 0;i<acList.size();i++)
    {
        if(acList[i].succi.empty())
        {
            acList[i].LF=maxEF;
            acList[i].calcLS();
            recBackward(acList[i],acList);
        }
    }
    for(Act item:acList)
    {
        std::cout<<item.name<<" : "<<item.LS<<"\t"<<item.LF<<"\n";
    }
    std::cout<<"======================================================================================\n";
}
void reCPM(int &i,std::vector<Act> &acList,bool &end,std::vector<bool> &visList)
{
    std::cout<<acList[i].name<<" => ";
    visList[i]=true;
    for(int item:acList[i].succi)
    {
        if(acList[i].succi.empty())
        {
            end=true;
            break;
        }
        else if (acList[item].EF==acList[item].LF && !visList[item])
        {
            reCPM(item,acList,end,visList);
        }
    }
}
void findCriticalPath(std::vector<Act> &acList,std::vector<std::pair<bool,std::vector<int>>> depMatrix)
{
    std::vector<bool> visList(acList.size(),false);
    std::cout<<"======================================================================================\n";
    std::cout<<"START => ";
    bool finished=false;
    for(int i=0;i<acList.size();i++)
    {
        if(depMatrix[i].first && acList[i].EF==acList[i].LF)
            reCPM(i,acList,finished,visList);
        if(finished)
            break;
    }
    std::cout<<"END\n";
    std::cout<<"======================================================================================\n";
}