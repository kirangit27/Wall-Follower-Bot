#include <iostream>
#include <string>
#include <stack>
#include <array>
#include <vector>
#include "simulator/simulator.h"



int main(int argc, char *argv[])
{
        // colorize and add text
        Simulator::setColor(0, 0, 'G');
        Simulator::setText(0, 0, "A");
        Simulator::setColor(0, 15, 'G');
        Simulator::setText(0, 15, "B");
        Simulator::setColor(15, 15, 'G');
        Simulator::setText(15, 15, "C");
        Simulator::setColor(15, 0, 'G');
        Simulator::setText(15, 0, "D");

        std::stack<std::array<int,2>> s;            //stack to keep record of current position in terms of 2 element 1D array (x,y)
        s.push({0,0});
        std::cout<<s.top().at(0)<<","<<s.top().at(1)<<std::endl;
        std::stack<char> dir;                       //stack to keep record of direction facing (N,S,E,W)
        char direction{'N'};                        
        char new_direction{};                       //variable to update direction once the robot turns
        dir.push(direction);
        int x{0};                                   //variable to update position once the robot moves
        int y{0};                                   //variable to update position once the robot moves        
        // move the robot back and forth

        // setting some walls for goal
        std::array<int,2> goal{7,0};

        //Simulator::setWall(8, 0, 's');

        while ((s.top().at(0) != goal.at(0)) || (s.top().at(1) != goal.at(1)))
        {   
        //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
        if(Simulator::wallLeft())
        {
                std::cerr << "--- left wall detected ---" << std::endl;
                if(Simulator::wallFront())
                {
                std::cerr << "--- front wall detected ---" << std::endl;
                if(Simulator::wallRight())
                {
                        std::cerr << "--- right wall detected ---" << std::endl;
                        Simulator::turnLeft();
                        switch(direction)
                        {
                        case 'N' : new_direction = 'W';
                                        x = s.top().at(0); y = s.top().at(1);
                                        s.push({x,y});
                                break;
                        case 'S' : new_direction = 'E';
                                        x = s.top().at(0); y = s.top().at(1);
                                        s.push({x,y});
                                break;
                        case 'E' : new_direction = 'N';
                                        x = s.top().at(0); y = s.top().at(1);
                                        s.push({x,y});
                                break;
                        case 'W' : new_direction = 'S';
                                        x = s.top().at(0); y = s.top().at(1);
                                        s.push({x,y});
                                break;
                        }
                        //Simulator::moveForward();
                        //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                        //dir.push(direction);
                }
                else
                {
                        Simulator::turnRight();
                        switch(direction)
                        {
                        case 'N' : new_direction = 'E';
                                        x = s.top().at(0)+1; y = s.top().at(1);
                                        s.push({x,y}); 
                                break;
                        case 'S' : new_direction = 'W';
                                        x = s.top().at(0)-1; y = s.top().at(1);
                                        s.push({x,y});
                                break;
                        case 'E' : new_direction = 'S';
                                        x = s.top().at(0); y = s.top().at(1)-1;
                                        s.push({x,y});
                                break;
                        case 'W' : new_direction = 'N';
                                        x = s.top().at(0); y = s.top().at(1)+1;
                                        s.push({x,y});
                                break;
                        }
                        Simulator::moveForward();
                        Simulator::setColor(s.top().at(0),s.top().at(1), 'Y');
                        //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                }
                }
                else
                {
                switch(direction)
                {
                        case 'N' :  x = s.top().at(0); y = s.top().at(1)+1;  
                                        s.push({x,y});                              
                                break;
                        case 'S' :  x = s.top().at(0); y = s.top().at(1)-1;
                                s.push({x,y});
                                break;
                        case 'E' :  x = s.top().at(0)+1; y = s.top().at(1);
                                s.push({x,y});
                                break;
                        case 'W' :  x = s.top().at(0)-1; y = s.top().at(1);
                                s.push({x,y});
                                break;
                }
                Simulator::moveForward();
                Simulator::setColor(s.top().at(0),s.top().at(1), 'Y');
                new_direction = direction;
                //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
                //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                }
        }
        else
        {
                Simulator::turnLeft();
                switch(direction)
                {
                case 'N' : new_direction = 'W';
                                x = s.top().at(0)-1; y = s.top().at(1);
                                s.push({x,y});
                        break;
                case 'S' : new_direction = 'E';
                                x = s.top().at(0)+1; y = s.top().at(1);
                                s.push({x,y});
                        break;
                case 'E' : new_direction = 'N';
                                x = s.top().at(0); y = s.top().at(1)+1;
                                s.push({x,y});
                        break;
                case 'W' : new_direction = 'S';
                                x = s.top().at(0); y = s.top().at(1)-1;
                                s.push({x,y});
                        break;
                }
                Simulator::moveForward();
                Simulator::setColor(s.top().at(0),s.top().at(1), 'Y');
                //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
                //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
        }

        direction = new_direction;
        dir.push(direction);
        std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
        std::cerr<<"facing "<<direction<<" direction"<<std::endl;
        std::cerr<<"facing "<<dir.top()<<" direction"<<std::endl;
        }

        std::cerr<<"GOAL reached ...\n Now back to home\n"<<std::endl;
        Simulator::turnLeft();
        Simulator::turnLeft();
        switch(direction)
        {
        case 'N' : new_direction = 'S';
                break;
        case 'S' : new_direction = 'N';
                break;
        case 'E' : new_direction = 'W';
                break;
        case 'W' : new_direction = 'E';
                break;
        }
        std::cerr<<s.size()<<","<<dir.size()<<std::endl;


        return 0;
}