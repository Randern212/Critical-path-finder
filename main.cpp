#include <iostream>
#include <string>
#include"2ndTry.cpp"
#include"Act.cpp"


int main()
{
    std::vector<Act> acList = createActList();
    std::vector<std::pair<bool,std::vector<int>>> depMatrix=createDepMat(acList);
    displayDepMat(depMatrix);
    std::vector<std::pair<bool,std::vector<int>>> adjMatrix=DepToAdjMat(depMatrix);
    displayDepMat(adjMatrix);
    assignSucci(acList,adjMatrix);
    forwardPass(acList,adjMatrix);
    backwardPass(acList);
    findCriticalPath(acList,depMatrix);
    return 0;
}