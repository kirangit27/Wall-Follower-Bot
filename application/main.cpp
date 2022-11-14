#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <vector>
#include <cstdlib>   // rand() and srand()
#include <ctime>     // For the time()
#include "simulator/simulator.h"

/**
 * @brief 
 * 
 */
void Printvector(std::vector<std::array<int,2>> k, std::vector<char> d)
{
        // If vector is empty then return
        if (k.empty())
        return;
        if (d.empty())
        return;   

        int x = k.back().at(0);
        int y = k.back().at(1);
        char z = d.back();

        // Pop the top element of the vector
        k.pop_back();
        d.pop_back();

        // Recursively call the function Printvector
        Printvector(k,d);

        // Print the vector element starting
        // from the bottom
        std::cerr<<"( "<< x <<","<< y <<" ), "<<z<<"\n";

        // push_back the same element onto the vector
        // to preserve the order
        k.push_back({x,y});
        d.push_back(z);
}

void PrintvectorData(std::vector<std::array<int,2>> k, std::vector<std::array<char,2>>  d)
{
        // If vector is empty then return
        if (k.empty())
                return;
        if (d.empty())
                return;   

        int x = k.back().at(0);
        int y = k.back().at(1);
        char z1 = d.back().at(0);
        char z2 = d.back().at(1);

        // Pop the top element of the vector
        k.pop_back();
        d.pop_back();

        // Recursively call the function Printvector
        PrintvectorData(k,d);

        // Print the vector element starting
        // from the bottom
        std::cerr<<"Entry: "<<z1<<" -> ( "<< x <<","<< y <<" ) -> "<<z2<<"\n";

        // push_back the same element onto the vector
        // to preserve the order
        k.push_back({x,y});
        d.push_back({z1,z2});
}

/*std::vector<std::array<std::string,4>> G_cell_info;

void StacktoVec(std::vector<std::array<int,2>> k, std::vector<std::array<char,2>>  d)
{
        // If vector is empty then return
        if (k.empty())
                return;
        if (d.empty())
                return;   

        std::string x{std::to_string(k.back().at(0))};
        std::string y{std::to_string(k.back().at(1))};
        std::string z1{d.back().at(0)};
        std::string z2{d.back().at(1)};

        // Pop the top element of the vector
        k.pop_back();
        d.pop_back();

        // Recursively call the function Printvector
        StacktoVec(k,d);

        // Print the vector element starting
        // from the bottom
        std::cerr<<"Entry: "<<z1<<" -> ( "<< x <<","<< y <<" ) -> "<<z2<<"\n";
        G_cell_info.push_back({x,y,z1,z2});
        std::cerr<<"Ent: "<<G_cell_info.back().at(2)<<" -* ( "<< x <<","<< y <<" ) -* "<<z2<<"\n";

        // push_back the same element onto the vector
        // to preserve the order
        k.push_back({k.back().at(0),k.back().at(1)});
        d.push_back({d.back().at(0),d.back().at(1)});
}*/

void PrintCellInfo(std::vector<std::array<int,2>> k)
{
        // If vector is empty then return
        if (k.empty())
                return; 

        int x = k.back().at(0);
        int y = k.back().at(1);


        // Pop the top element of the vector
        k.pop_back();

        // Recursively call the function Printvector
        PrintCellInfo(k);

        // Print the vector element starting
        // from the bottom
        std::cerr<<"Entry: "<<" -> ( "<< x <<","<< y <<" ) -> "<<"\n";

        // push_back the same element onto the vector
        // to preserve the order
        k.push_back({x,y});
       
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

        std::vector<std::array<int,2>> s;            //vector to keep record of current position in terms of 2 element 1D array (x,y)
        s.push_back({0,0});
        std::vector<std::array<int,2>> ret;            //vector to keep record of return position in terms of 2 element 1D array (x,y)
        ret.push_back({0,0});
        std::vector<std::array<int,2>> dead_end;            //vector to keep record of current position in terms of 2 element 1D array (x,y)

        std::vector<std::array<char,2>> dir_vector;
        //dir_vector.push_back({'N','N'});
        
        std::cerr<<s.back().at(0)<<","<<s.back().at(1)<<std::endl;
        std::vector<char> dir;                       //vector to keep record of direction facing (N,S,E,W)
        char direction{'N'};                        
        char new_direction{};                       //variable to update direction once the robot turns
        dir.push_back(direction);
        int x{0};                                   //variable to update position once the robot moves
        int y{0};                                   //variable to update position once the robot moves        
        
        // move the robot back and forth

        // setting some walls for goal
        std::array<int,2> goal{generate_goal()};
        //std::array<int,2> goal{15,15};

        //Simulator::setWall(8, 0, 's');

        while ((s.back().at(0) != goal.at(0)) || (s.back().at(1) != goal.at(1)))
        {   
                //std::cerr<<"current position ("<<s.back().at(0)<<" , "<<s.back().at(1)<<")"<<std::endl;
                if(Simulator::wallLeft())
                {
                        //std::cerr << "--- left wall detected ---" << std::endl;
                        if(Simulator::wallFront())
                        {
                                //std::cerr << "--- front wall detected ---" << std::endl;
                                if(Simulator::wallRight())
                                {
                                        //std::cerr << "--- right wall detected ---" << std::endl;
                                        Simulator::turnLeft();
                                        Simulator::turnLeft();
                                        Simulator::setColor(s.back().at(0),s.back().at(1),'R');
                                        dead_end.push_back({s.back().at(0),s.back().at(1)});
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
                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'S' : new_direction = 'N';
                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'E' : new_direction = 'W';
                                                                x = s.back().at(0)-1; y = s.back().at(1);
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'W' : new_direction = 'E';
                                                                x = s.back().at(0)+1; y = s.back().at(1);
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        direction = new_direction;
                                        
                                }
                                else
                                {
                                        Simulator::turnRight();
                                        switch(direction)
                                        {
                                                case 'N' : new_direction = 'E';
                                                                x = s.back().at(0)+1; y = s.back().at(1);
                                                                s.push_back({x,y}); 
                                                                dir_vector.push_back({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'S' : new_direction = 'W';
                                                                x = s.back().at(0)-1; y = s.back().at(1);
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'E' : new_direction = 'S';
                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                                case 'W' : new_direction = 'N';
                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                                //O = direction; N = direction;
                                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});  
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                        //std::cerr<<"current position ("<<s.back().at(0)<<" , "<<s.back().at(1)<<")"<<std::endl;
                                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                                }
                        }
                        else
                        {
                                switch(direction)
                                {
                                        case 'N' :  x = s.back().at(0); y = s.back().at(1)+1;  
                                                        s.push_back({x,y});  
                                                        dir_vector.push_back({direction,direction});
                                                        //O = direction; N = direction;
                                                        //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});                            
                                                break;
                                        case 'S' :  x = s.back().at(0); y = s.back().at(1)-1;
                                                        s.push_back({x,y});
                                                        dir_vector.push_back({direction,direction});
                                                     //   O = direction; N = direction;
                                                       // cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                        case 'E' :  x = s.back().at(0)+1; y = s.back().at(1);
                                                        s.push_back({x,y});
                                                        dir_vector.push_back({direction,direction});
                                                        //O = direction; N = direction;
                                                     //   cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                        case 'W' :  x = s.back().at(0)-1; y = s.back().at(1);
                                                        s.push_back({x,y});
                                                        dir_vector.push_back({direction,direction});
                                                       // O = direction; N = direction;
                                                        //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                                break;
                                }
                                Simulator::moveForward();
                                Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                new_direction = direction;
                        //std::cerr<<"current position ("<<s.back().at(0)<<" , "<<s.back().at(1)<<")"<<std::endl;
                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                        }
                }
                else
                {
                        Simulator::turnLeft();
                        switch(direction)
                        {
                                case 'N' : new_direction = 'W';
                                                x = s.back().at(0)-1; y = s.back().at(1);
                                                s.push_back({x,y});
                                                dir_vector.push_back({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'S' : new_direction = 'E';
                                                x = s.back().at(0)+1; y = s.back().at(1);
                                                s.push_back({x,y});
                                                dir_vector.push_back({direction,new_direction});
                                                //O = direction; N = direction;
                                               // cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'E' : new_direction = 'N';
                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                s.push_back({x,y});
                                                dir_vector.push_back({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                        break;
                                case 'W' : new_direction = 'S';
                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                s.push_back({x,y});
                                                dir_vector.push_back({direction,new_direction});
                                                //O = direction; N = direction;
                                                //cell_info.push_back({std::to_string(x),std::to_string(y),O,N});
                                        break;
                        }
                        Simulator::moveForward();
                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                        //std::cerr<<"current position ("<<s.back().at(0)<<" , "<<s.back().at(1)<<")"<<std::endl;
                        //std::cerr<<"facing "<<new_direction<<" direction"<<std::endl;
                }

                direction = new_direction;
                dir.push_back(direction);
                //std::cerr<<"current position ("<<s.back().at(0)<<" , "<<s.back().at(1)<<")"<<std::endl;
                //std::cerr<<"facing "<<direction<<" direction"<<std::endl;
                //std::cerr<<"facing "<<dir.back()<<" direction"<<std::endl;
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
      // Printvector(s,dir);
        dir_vector.push_back({direction,new_direction});
        std::cerr<<"##########################################"<<std::endl;
        std::cerr<<s.size()<<","<<dir_vector.size()<<std::endl;
        PrintvectorData(s,dir_vector);
        std::cerr<<"##########################################"<<std::endl;
        PrintCellInfo(dead_end);
        std::cerr<<"##########################################"<<std::endl;
        std::vector<std::array<std::string,4>> cell_info;
        std::string O{""};
        std::string N{""};

        for(int i=0;i<s.size();i++)
        {
                O = dir_vector.at(i).at(0);
                N = dir_vector.at(i).at(1);
                cell_info.push_back({{std::to_string(s.at(i).at(0)),std::to_string(s.at(i).at(1)),O,N}});
        }

        std::cerr<<"cell info size : "<<cell_info.size()<<std::endl;
        for(int i =0;i<cell_info.size();i++)
        {
                //std::cerr<<i<<" - ent : "<<cell_info.at(i).at(2)<<" --> ("<<cell_info.at(i).at(0)<<","<<cell_info.at(i).at(1)<<") --> "<<cell_info.at(i).at(3)<<": exit"<<std::endl;
                std::cerr<<"{\""<<cell_info.at(i).at(0)<<"\",\""<<cell_info.at(i).at(1)<<"\",\""<<cell_info.at(i).at(2)<<"\",\""<<cell_info.at(i).at(3)<<"\"},"<<"   //"<<i<<std::endl;
        }
        
        std::vector<std::array<std::string,4>> cell_info_copy;
        cell_info_copy = cell_info;


        for(int i = 0;i<cell_info.size();i++)
        {
                for(int j = cell_info.size()-1; j >= 0; j--)
                {
                        if((cell_info.at(i).at(0) == cell_info.at(j).at(0)) && (cell_info.at(i).at(1)) == cell_info.at(j).at(1) && i!=j)
                        {
                                std::cerr<<"Found : ("<<cell_info.at(i).at(0)<<","<<cell_info.at(i).at(1)<<") at "<<i<<" and "<<j<<std::endl;
                                cell_info.erase(cell_info.begin()+i,cell_info.begin()+j);

                                if(i > cell_info.size() || j > cell_info.size())
                                {
                                        break;
                                }
                        }
                }
        } 


        std::cerr<<"\n\n\nnew vector : size "<<cell_info.size()<<std::endl;
        for(int j = 0; j<cell_info.size();j++)
        {
                std::cerr<<cell_info.at(j).at(0)<<","<<cell_info.at(j).at(1)<<","<<cell_info.at(j).at(2)<<","<<cell_info.at(j).at(3)<<"----"<<j<<std::endl;
        }


        for(int i = 0; i<cell_info_copy.size(); i++)
        { 
                int ctr{0};
                for(int j =0;j<cell_info.size();j++)
                {
                        if((cell_info_copy.at(i).at(0) == cell_info.at(j).at(0)) && (cell_info_copy.at(i).at(1) == cell_info.at(j).at(1)))
                        {
                                ctr++;
                        }
                }
                if(ctr == 0)
                {
                        Simulator::setColor(stoi(cell_info_copy.at(i).at(0)),stoi(cell_info_copy.at(i).at(1)),'R');
                }
        }

        
        std::vector<char> return_dir;

        for(int k = cell_info.size()-1; k >= 0 ; k--)
        {
                //if(cell_info.at(k).at(2))

                switch(cell_info.at(k).at(2).at(0))
                {
                        case 'N' : return_dir.push_back('S');
                                break;
                        case 'S' : return_dir.push_back('N');
                                break;
                        case 'E' : return_dir.push_back('W');
                                break;
                        case 'W' : return_dir.push_back('E');
                                break;                       
                }
        }

        for(int i = 1; i<return_dir.size(); i++)
        {
                std::cerr<<"-->"<<return_dir.at(i)<<std::endl;
        }

        std::vector<std::array<int,2>> return_path;
        for(int k = cell_info.size()-1; k >= 0 ; k--)
        {
                return_path.push_back({stoi(cell_info.at(k).at(0)),stoi(cell_info.at(k).at(1))});
        }

        for(int i = 0; i<return_path.size(); i++)
        {
                std::cerr<<"-->("<<return_path.at(i).at(0)<<","<<return_path.at(i).at(1)<<")"<<std::endl;
                Simulator::setColor(return_path.at(i).at(0), return_path.at(i).at(1), 'G');
        }

        direction = new_direction;
        //Simulator::moveForward();

        for(int i=0;i<return_path.size()-1;i++)
        {
                int x1{return_path.at(i).at(0)};
                int y1{return_path.at(i).at(1)};

                int x2{return_path.at(i+1).at(0)};
                int y2{return_path.at(i+1).at(1)};

                int x_diff{x2-x1};
                int y_diff{y2-y1};

                Simulator::setColor(return_path.at(i).at(0),return_path.at(i).at(1), 'c');
                std::cerr<<"("<<return_path.at(i).at(0)<<","<<return_path.at(i).at(1)<<")"<<std::endl;
                std::cerr<<"|"<<x_diff<<","<<y_diff<<"|"<<std::endl;

                /**
                 * @brief Construct a new if object, used to traverse through unliked path 
                 * 
                 */
                if(x_diff == 0  ||  y_diff ==0)
                {
                        if(x_diff == 0 && (y_diff == 1 || y_diff == -1))
                        {
                                switch(direction)
                                {
                                        case 'N': Simulator::moveForward();
                                                        new_direction='N';
                                                break;
                                        case 'S': Simulator::moveForward();
                                                        new_direction='S';
                                                break;
                                        case 'E':  if(y_diff == 1)
                                                        {
                                                        Simulator::turnLeft();
                                                        Simulator::moveForward();
                                                        new_direction='N';         
                                                        }
                                                        else
                                                        {
                                                        Simulator::turnRight();
                                                        Simulator::moveForward();
                                                        new_direction='S';  
                                                        }
                                                break;
                                        case 'W':  if(y_diff == 1)
                                                        {
                                                        Simulator::turnRight();
                                                        Simulator::moveForward();
                                                        new_direction='N';         
                                                        }
                                                        else
                                                        {
                                                        Simulator::turnLeft();
                                                        Simulator::moveForward();
                                                        new_direction='S';  
                                                        }
                                                break;  
                                }
                        }
                        else if(y_diff == 0 && (x_diff == 1 || x_diff == -1))
                        {
                                switch(direction)
                                {
                                        case 'E': Simulator::moveForward();
                                                        new_direction='E';
                                                break;
                                        case 'W': Simulator::moveForward();
                                                        new_direction='W';
                                                break;
                                        case 'S':  if(x_diff == 1)
                                                        {
                                                        Simulator::turnLeft();
                                                        Simulator::moveForward();
                                                        new_direction='E';         
                                                        }
                                                        else
                                                        {
                                                        Simulator::turnRight();
                                                        Simulator::moveForward();
                                                        new_direction='W';  
                                                        }
                                                break;
                                        case 'N':  if(x_diff == 1)
                                                        {
                                                        Simulator::turnRight();
                                                        Simulator::moveForward();
                                                        new_direction='E';         
                                                        }
                                                        else
                                                        {
                                                        Simulator::turnLeft();
                                                        Simulator::moveForward();
                                                        new_direction='W';  
                                                        }
                                                break;  
                                }
                        }
                }   
                direction = new_direction;
        }     


/*
        Simulator::moveForward();
        direction = new_direction;
        for(int i = 1; i<return_dir.size(); i++)
        {

                switch(direction)
                {
                        case 'N' :      switch(return_dir.at(i))  
                                        {
                                                case 'N':       Simulator::moveForward();
                                                                new_direction = 'N';
                                                                break;
                                                case 'E':       Simulator::turnRight();
                                                                Simulator::moveForward();
                                                                new_direction = 'E';
                                                                break;
                                                case 'W':       Simulator::turnLeft();
                                                                Simulator::moveForward();
                                                                new_direction = 'W';
                                                                break;
                                        }
                                        break;
                        case 'S' :      switch(return_dir.at(i))  
                                        {
                                                case 'S':       Simulator::moveForward();
                                                                new_direction = 'S';
                                                                break;
                                                case 'W':       Simulator::turnRight();
                                                                Simulator::moveForward();
                                                                new_direction = 'W';
                                                                break;
                                                case 'E':       Simulator::turnLeft();
                                                                Simulator::moveForward();
                                                                new_direction = 'E';
                                                                break;
                                        }
                                        break;
                        case 'E' :      switch(return_dir.at(i))  
                                        {
                                                case 'E':       Simulator::moveForward();
                                                                new_direction = 'E';
                                                                break;
                                                case 'S':       Simulator::turnRight();
                                                                Simulator::moveForward();
                                                                new_direction = 'S';
                                                                break;
                                                case 'N':       Simulator::turnLeft();
                                                                Simulator::moveForward();
                                                                new_direction = 'N';
                                                                break;
                                        }
                                        break;
                        case 'W' :      switch(return_dir.at(i))  
                                        {
                                                case 'W':       Simulator::moveForward();
                                                                new_direction = 'W';
                                                                break;
                                                case 'N':       Simulator::turnRight();
                                                                Simulator::moveForward();
                                                                new_direction = 'N';
                                                                break;
                                                case 'S':       Simulator::turnLeft();
                                                                Simulator::moveForward();
                                                                new_direction = 'S';
                                                                break;
                                        }
                                        break;

                }

                direction = new_direction;
        }*/

        return 0;
}
