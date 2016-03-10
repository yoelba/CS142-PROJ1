#include<iostream>
#include<string>
#include<vector>

int main(){

    std::string tester = "balls";
    std::vector<string> death;

    death.pushback( tester ); 
    std::cout << death.at(0);

    return 0;

}
