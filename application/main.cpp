#include <iostream>
#include <string>
#include <stack>
#include <array>
#include <vector>
#include <cstdlib>   // rand() and srand()
#include <ctime>     // For the time()
#include "simulator/simulator.h"

/**
 * @brief 
 * 
 */
void PrintStack(std::stack<std::array<int,2>> k, std::stack<char> d)
{
        // If stack is empty then return
        if (k.empty())
        return;
        if (d.empty())
        return;   

        int x = k.top().at(0);
        int y = k.top().at(1);
        char z = d.top();

        // Pop the top element of the stack
        k.pop();
        d.pop();

        // Recursively call the function PrintStack
        PrintStack(k,d);

        // Print the stack element starting
        // from the bottom
        std::cerr<<"( "<< x <<","<< y <<" ), "<<z<<"\n";

        // Push the same element onto the stack
        // to preserve the order
        k.push({x,y});
        d.push(z);
}

void PrintStackData(std::stack<std::array<int,2>> k, std::stack<std::array<char,2>>  d)
{
        // If stack is empty then return
        if (k.empty())
                return;
        if (d.empty())
                return;   

        int x = k.top().at(0);
        int y = k.top().at(1);
        char z1 = d.top().at(0);
        char z2 = d.top().at(1);

        // Pop the top element of the stack
        k.pop();
        d.pop();

        // Recursively call the function PrintStack
        PrintStackData(k,d);

        // Print the stack element starting
        // from the bottom
        std::cerr<<"Entry: "<<z1<<" -> ( "<< x <<","<< y <<" ) -> "<<z2<<"\n";

        // Push the same element onto the stack
        // to preserve the order
        k.push({x,y});
        d.push({z1,z2});
}

void PrintCellInfo(std::stack<std::array<int,2>> k)
{
        // If stack is empty then return
        if (k.empty())
                return; 

        int x = k.top().at(0);
        int y = k.top().at(1);


        // Pop the top element of the stack
        k.pop();

        // Recursively call the function PrintStack
        PrintCellInfo(k);

        // Print the stack element starting
        // from the bottom
        std::cerr<<"Entry: "<<" -> ( "<< x <<","<< y <<" ) -> "<<"\n";

        // Push the same element onto the stack
        // to preserve the order
        k.push({x,y});
       
}

void print_grind_numbers()
{
        std::string grid{""};
        for(int i =0;i<16;i++)
        {
                for(int j=0; j<16; j++)
                {
                        grid = std::to_string(i)+","+std::to_string(j);
                        Simulator::setText(i,j,grid);
                }
        }
}

void set_outer_walls()
{
        for(int i = 0; i<16; i++)
        {
                Simulator::setWall(i,0, 's');
        }
        for(int i = 0; i<16; i++)
        {
                Simulator::setWall(0,i, 'w');
        }
        for(int i = 0; i<16; i++)
        {
                Simulator::setWall(i,15, 'n');
        }
        for(int i = 0; i<16; i++)
        {
                Simulator::setWall(15,i, 'e');
        }
} 

/**
 * @brief 
 * 
 */
std::array<int,2> generate_goal()
{
        int x{};
        int y{};
        unsigned seed = time(0);
       
        // Seed the random number generator.
        srand(seed);

        x = rand()%16;          //generates random number between 0 and 15

        do
        {
                if(x == 0 || x == 15)           //if x is either 0 or 15; y can be any number between 0 and 15
                {       y = rand()%16;   }      //generates random number between 0 and 15               
                else
                {
                        y = rand()%2;           //generates random number between 0 and 1
                        if(y == 1)              //if y = 1, set it to 15; Thus y is either 0 or 15
                        {  y = 15;  }
                }

        }while(x==0 &&y==0);            //ensures goal is not (0,0)

        Simulator::setText(x,y,"G");        
        std::cerr<<"GOAL : ("<<x<<","<<y<<")"<<std::endl;
        Simulator::setColor(x,y,'w');
        if(y == 0)
            Simulator::setWall(x,y, 's');
        else if(y == 15)
            Simulator::setWall(x,y, 'n');
        else if(x == 0)
            Simulator::setWall(x,y, 'w');
        else
            Simulator::setWall(x,y, 'e');

        return {x,y};
}


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


        set_outer_walls();
        print_grind_numbers();

        std::stack<std::array<int,2>> s;            //stack to keep record of current position in terms of 2 element 1D array (x,y)
        s.push({0,0});
        std::stack<std::array<int,2>> ret;            //stack to keep record of return position in terms of 2 element 1D array (x,y)
        ret.push({0,0});
        std::stack<std::array<int,2>> red;            //stack to keep record of current position in terms of 2 element 1D array (x,y)

        std::stack<std::array<char,2>> dir_stack;
        //dir_stack.push({'N','N'});
        std::stack<std::array<std::string,4>> cell_info;
        std::cerr<<s.top().at(0)<<","<<s.top().at(1)<<std::endl;
        std::stack<char> dir;                       //stack to keep record of direction facing (N,S,E,W)
        char direction{'N'};                        
        char new_direction{};                       //variable to update direction once the robot turns
        dir.push(direction);
        int x{0};                                   //variable to update position once the robot moves
        int y{0};                                   //variable to update position once the robot moves        

        std::array<int,2> goal{generate_goal()};

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
                                        Simulator::turnLeft();
                                        Simulator::setColor(s.top().at(0),s.top().at(1),'R');
                                        red.push({s.top().at(0),s.top().at(1)});
                                        if(direction == 'N')
                                                {Simulator::setWall(x,y,'n');
                                                Simulator::setWall(x,y,'w');}
                                        else if(direction == 'S')
                                                {Simulator::setWall(x,y,'s');
                                                Simulator::setWall(x,y,'e');}
                                        else if(direction == 'W')
                                                {Simulator::setWall(x,y,'w');
                                                Simulator::setWall(x,y,'s');}
                                        else if(direction == 'E')
                                                {Simulator::setWall(x,y,'e');
                                                Simulator::setWall(x,y,'n');}

                                        switch(direction)
                                        {
                                                case 'N' : new_direction = 'S';
                                                                x = s.top().at(0); y = s.top().at(1)-1;
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                        break;
                                                case 'S' : new_direction = 'N';
                                                                x = s.top().at(0); y = s.top().at(1)+1;
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                        break;
                                                case 'E' : new_direction = 'W';
                                                                x = s.top().at(0)-1; y = s.top().at(1);
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                        break;
                                                case 'W' : new_direction = 'E';
                                                                x = s.top().at(0)+1; y = s.top().at(1);
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        //std::cerr<<"current position ("<<s.top().at(0)<<" , "<<s.top().at(1)<<")"<<std::endl;
                                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                                        //dir.push(direction);
                                        
                                        direction = new_direction;

                                }
                                else
                                {
                                        Simulator::turnRight();
                                        switch(direction)
                                        {
                                                case 'N' : new_direction = 'E';
                                                                x = s.top().at(0)+1; y = s.top().at(1);
                                                                s.push({x,y}); 
                                                                dir_stack.push({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'S' : new_direction = 'W';
                                                                x = s.top().at(0)-1; y = s.top().at(1);
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'E' : new_direction = 'S';
                                                                x = s.top().at(0); y = s.top().at(1)-1;
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'W' : new_direction = 'N';
                                                                x = s.top().at(0); y = s.top().at(1)+1;
                                                                s.push({x,y});
                                                                dir_stack.push({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        Simulator::setColor(s.top().at(0),s.top().at(1), 'c');
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
                                                        dir_stack.push({direction,direction});
                                                        //O = direction; N = direction;
                                                        //cell_info.push({std::to_string(x),std::to_string(y),O,N});                            
                                                break;
                                        case 'S' :  x = s.top().at(0); y = s.top().at(1)-1;
                                                        s.push({x,y});
                                                        dir_stack.push({direction,direction});
                                                     //   O = direction; N = direction;
                                                       // cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                        case 'E' :  x = s.top().at(0)+1; y = s.top().at(1);
                                                        s.push({x,y});
                                                        dir_stack.push({direction,direction});
                                                        //O = direction; N = direction;
                                                     //   cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                        case 'W' :  x = s.top().at(0)-1; y = s.top().at(1);
                                                        s.push({x,y});
                                                        dir_stack.push({direction,direction});
                                                       // O = direction; N = direction;
                                                        //cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                }
                                Simulator::moveForward();
                                Simulator::setColor(s.top().at(0),s.top().at(1), 'c');
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
                                                dir_stack.push({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'S' : new_direction = 'E';
                                                x = s.top().at(0)+1; y = s.top().at(1);
                                                s.push({x,y});
                                                dir_stack.push({direction,new_direction});
                                                //O = direction; N = direction;
                                               // cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'E' : new_direction = 'N';
                                                x = s.top().at(0); y = s.top().at(1)+1;
                                                s.push({x,y});
                                                dir_stack.push({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'W' : new_direction = 'S';
                                                x = s.top().at(0); y = s.top().at(1)-1;
                                                s.push({x,y});
                                                dir_stack.push({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push({std::to_string(x),std::to_string(y),O,N});
                                        break;
                        }
                        Simulator::moveForward();
                        Simulator::setColor(s.top().at(0),s.top().at(1), 'c');
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
        PrintStack(s,dir);
        dir_stack.push({direction,new_direction});
        std::cerr<<"##########################################"<<std::endl;
        std::cerr<<s.size()<<","<<dir_stack.size()<<std::endl;
        PrintStackData(s,dir_stack);
        std::cerr<<"##########################################"<<std::endl;
        PrintCellInfo(red);

        
        return 0;
}