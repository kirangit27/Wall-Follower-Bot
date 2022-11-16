#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <vector>
#include <tuple>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For the time()
#include "simulator/simulator.h"

namespace rwa2group19{

/**
 * @brief 
 * 
 */
class SetMaze{
        private:
                std::string grid{""};
                int x{};
                int y{};
                unsigned seed{};                        

        public:
                /**
                 * @brief 
                 * 
                 */
                void m_print_grind_numbers()
                {
                        for(int i =0;i<16;i++)
                        {
                                for(int j=0; j<16; j++)
                                {
                                        grid = std::to_string(i)+","+std::to_string(j);
                                        Simulator::setText(i,j,grid);
                                }
                        }
                }

                /**
                 * @brief 
                 * 
                 */
                void m_set_outer_walls()
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
                std::array<int,2> m_generate_goal()
                {                      
                        
                        seed = time(0);         // Seed the random number generator
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
                        std::cerr<<"GOAL at : ("<<x<<","<<y<<")"<<std::endl;
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

};
}//namespace rwa2group19


namespace rwa2group19{

/**
 * @brief 
 * 
 */
class Algorithm{

        private:
                std::vector<std::array<int,2>> s;            //vector to keep record of current position in terms of 2 element 1D array (x,y)        
                std::vector<std::array<int,2>> dead_end;     //vector to keep record of current position in terms of 2 element 1D array (x,y)

                std::vector<char> dir;                       //vector to keep record of direction facing (N,S,E,W)
                char direction{};                        
                char new_direction{};                       //variable to update direction once the robot turns

                std::vector<std::array<char,2>> dir_vector;     //vector to keep record of both previous and current direction the robot is facing
                #include <iostream>
#include <string>
#include <vector>
#include <array>
#include <vector>
#include <tuple>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For the time()
#include "simulator/simulator.h"

char direction;

namespace rwa2group19{

/**
 * @brief 
 * 
 */
class SetMaze{
        private:
                std::string grid{""};
                int x{};
                int y{};
                unsigned seed{};                        

        public:
                /**
                 * @brief 
                 * 
                 */
                void m_print_grind_numbers()
                {
                        for(int i =0;i<16;i++)
                        {
                                for(int j=0; j<16; j++)
                                {
                                        grid = std::to_string(i)+","+std::to_string(j);
                                        Simulator::setText(i,j,grid);
                                }
                        }
                }

                /**
                 * @brief 
                 * 
                 */
                void m_set_outer_walls()
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
                std::array<int,2> m_generate_goal()
                {                      
                        
                        seed = time(0);         // Seed the random number generator
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
                        std::cerr<<"GOAL at : ("<<x<<","<<y<<")"<<std::endl;
                        Simulator::setColor(x,y,'r');
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

};
}//namespace rwa2group19


namespace rwa2group19{

/**
 * @brief 
 * 
 */
class Algorithm{

        private:
                std::vector<std::array<int,2>> s;            //vector to keep record of current position in terms of 2 element 1D array (x,y)        
                std::vector<std::array<int,2>> dead_end;     //vector to keep record of current position in terms of 2 element 1D array (x,y)

                std::vector<char> dir;                       //vector to keep record of direction facing (N,S,E,W)
               // char direction{};                        
                char new_direction{};                       //variable to update direction once the robot turns

                std::vector<std::array<char,2>> dir_vector;     //vector to keep record of both previous and current direction the robot is facing
                
                int x{0};                                   //variable to update position once the robot moves
                int y{0};                                   //variable to update position once the robot moves 

                std::vector<std::array<std::string,4>> cell_info;
                std::string O{""};
                std::string N{""};       

                std::vector<std::array<std::string,4>> cell_info_copy;
                std::vector<char> return_dir;
                std::vector<std::array<int,2>> return_path;

                int x1{0};
                int y1{0};
                int x2{0};
                int y2{0};
                int x_diff{0};
                int y_diff{0};

        public:        
                
                /**
                 * @brief 
                 * 
                 */
                std::vector<std::array<std::string,4>> m_left_wall_follower(std::array<int,2> goal)
                {         
                        s.push_back({x,y});
                        direction = 'N';
                        dir.push_back(direction);
                        
                        std::vector<std::array<char,2>> dir_vector;     //vector to keep record of current direction the robot is facing
                      
                        while ((s.back().at(0) != goal.at(0)) || (s.back().at(1) != goal.at(1)))
                        {   
                                if(Simulator::wallLeft())
                                {
                                        if(Simulator::wallFront())
                                        {
                                                if(Simulator::wallRight())
                                                {
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
                                                                        break;
                                                                case 'S' : new_direction = 'W';
                                                                                x = s.back().at(0)-1; y = s.back().at(1);
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                                case 'E' : new_direction = 'S';
                                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                                case 'W' : new_direction = 'N';
                                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                        }
                                                        Simulator::moveForward();
                                                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');;
                                                }
                                        }
                                        else
                                        {
                                                switch(direction)
                                                {
                                                        case 'N' :  x = s.back().at(0); y = s.back().at(1)+1;  
                                                                        s.push_back({x,y});  
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                        case 'S' :  x = s.back().at(0); y = s.back().at(1)-1;
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});                                                        
                                                                break;
                                                        case 'E' :  x = s.back().at(0)+1; y = s.back().at(1);
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                        case 'W' :  x = s.back().at(0)-1; y = s.back().at(1);
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                }
                                                Simulator::moveForward();
                                                Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                                new_direction = direction;
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
                                                        break;
                                                case 'S' : new_direction = 'E';
                                                                x = s.back().at(0)+1; y = s.back().at(1);
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'E' : new_direction = 'N';
                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'W' : new_direction = 'S';
                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                }

                                direction = new_direction;
                                dir.push_back(direction);
                        }

                        std::cerr<<"## GOAL reached ##\n-- Now back to home --\n"<<std::endl;
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

                        dir_vector.push_back({direction,new_direction});

                        direction = new_direction;

                        for(int i=0;i<s.size();i++)
                        {
                                O = dir_vector.at(i).at(0);
                                N = dir_vector.at(i).at(1);
                                cell_info.push_back({{std::to_string(s.at(i).at(0)),std::to_string(s.at(i).at(1)),O,N}});
                        }

                        return cell_info;
                }//method m_left_wall_follower        

                /**
                 * @brief 
                 * 
                 */
                void  m_return_path(std::vector<std::array<std::string,4>> cell_data)
                {
                        cell_info_copy = cell_data;
                        
                        for(int i = 0;i<cell_data.size();i++)
                        {
                                for(int j = cell_data.size()-1; j >= 0; j--)
                                {
                                        if((cell_data.at(i).at(0) == cell_data.at(j).at(0)) && (cell_data.at(i).at(1)) == cell_data.at(j).at(1) && i!=j)
                                        {
                                                cell_data.erase(cell_data.begin()+i,cell_data.begin()+j);

                                                if(i > cell_data.size() || j > cell_data.size())
                                                {
                                                        break;
                                                }
                                        }
                                }
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
   

                        for(int k = cell_data.size()-1; k >= 0 ; k--)
                        {
                                switch(cell_data.at(k).at(2).at(0))
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
                        
                        for(int k = cell_data.size()-1; k >= 0 ; k--)
                        {
                                return_path.push_back({stoi(cell_data.at(k).at(0)),stoi(cell_data.at(k).at(1))});
                        }

                        for(int i = 0; i<return_path.size(); i++)
                        {
                                Simulator::setColor(return_path.at(i).at(0), return_path.at(i).at(1), 'G');
                        }

                        direction = new_direction;

                        for(int i=0;i<return_path.size()-1;i++)
                        {
                                x1 = return_path.at(i).at(0);
                                y1 = return_path.at(i).at(1);

                                x2 = return_path.at(i+1).at(0);
                                y2 = return_path.at(i+1).at(1);

                                x_diff = x2-x1;
                                y_diff = y2-y1;

                                Simulator::setColor(return_path.at(i).at(0),return_path.at(i).at(1), 'c');

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

                        std::cerr<<"## BACK HOME ##"<<std::endl;
                }//method m_return_path

        };//class Algorithm

}//namespace rwa2group19



int main(int argc, char *argv[])
{

        rwa2group19::SetMaze M;
        rwa2group19::Algorithm A;
        
        M.m_set_outer_walls();
        M.m_print_grind_numbers();
        
        std::array<int,2> goal{M.m_generate_goal()};      // goal variable to store x and y coordinates of goal; and initialize it accessing m_goal_generate method
       
        std::vector<std::array<std::string,4>> cell_data;

        cell_data = A.m_left_wall_follower(goal);
        A.m_return_path(cell_data);
        
        return 0;
}

                int x{0};                                   //variable to update position once the robot moves
                int y{0};                                   //variable to update position once the robot moves 

                std::vector<std::array<std::string,4>> cell_info;
                std::string O{""};
                std::string N{""};       


        public:        
                
                /**
                 * @brief 
                 * 
                 */
                std::tuple<std::vector<std::array<std::string,4>>, char > m_left_wall_follower(std::array<int,2> goal)
                {         
                        s.push_back({x,y});
                        direction = 'N';
                        dir.push_back(direction);
                        
                        std::vector<std::array<char,2>> dir_vector;     //vector to keep record of current direction the robot is facing
                      
                        while ((s.back().at(0) != goal.at(0)) || (s.back().at(1) != goal.at(1)))
                        {   
                                if(Simulator::wallLeft())
                                {
                                        if(Simulator::wallFront())
                                        {
                                                if(Simulator::wallRight())
                                                {
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
                                                                        break;
                                                                case 'S' : new_direction = 'W';
                                                                                x = s.back().at(0)-1; y = s.back().at(1);
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                                case 'E' : new_direction = 'S';
                                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                                case 'W' : new_direction = 'N';
                                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                                s.push_back({x,y});
                                                                                dir_vector.push_back({direction,new_direction});
                                                                        break;
                                                        }
                                                        Simulator::moveForward();
                                                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');;
                                                }
                                        }
                                        else
                                        {
                                                switch(direction)
                                                {
                                                        case 'N' :  x = s.back().at(0); y = s.back().at(1)+1;  
                                                                        s.push_back({x,y});  
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                        case 'S' :  x = s.back().at(0); y = s.back().at(1)-1;
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});                                                        
                                                                break;
                                                        case 'E' :  x = s.back().at(0)+1; y = s.back().at(1);
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                        case 'W' :  x = s.back().at(0)-1; y = s.back().at(1);
                                                                        s.push_back({x,y});
                                                                        dir_vector.push_back({direction,direction});
                                                                break;
                                                }
                                                Simulator::moveForward();
                                                Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                                new_direction = direction;
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
                                                        break;
                                                case 'S' : new_direction = 'E';
                                                                x = s.back().at(0)+1; y = s.back().at(1);
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'E' : new_direction = 'N';
                                                                x = s.back().at(0); y = s.back().at(1)+1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                                case 'W' : new_direction = 'S';
                                                                x = s.back().at(0); y = s.back().at(1)-1;
                                                                s.push_back({x,y});
                                                                dir_vector.push_back({direction,new_direction});
                                                        break;
                                        }
                                        Simulator::moveForward();
                                        Simulator::setColor(s.back().at(0),s.back().at(1), 'c');
                                }

                                direction = new_direction;
                                dir.push_back(direction);
                        }

                        std::cerr<<"## GOAL reached ##\n-- Now back to home --\n"<<std::endl;
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

                        dir_vector.push_back({direction,new_direction});

                        direction = new_direction;

                        for(int i=0;i<s.size();i++)
                        {
                                O = dir_vector.at(i).at(0);
                                N = dir_vector.at(i).at(1);
                                cell_info.push_back({{std::to_string(s.at(i).at(0)),std::to_string(s.at(i).at(1)),O,N}});
                        }

                        return make_tuple(cell_info,direction);
                }
};

}//namespace rwa2group19


namespace rwa2group19{

class return_path{
        private:
                std::vector<std::array<std::string,4>> cell_info_copy;
                char new_direction;
                std::vector<char> return_dir;
                std::vector<std::array<int,2>> return_path;

        public:
                void m_return_path(std::vector<std::array<std::string,4>> cell_info, char direction)
                {
                        cell_info_copy = cell_info;
                        
                        for(int i = 0;i<cell_info.size();i++)
                        {
                                for(int j = cell_info.size()-1; j >= 0; j--)
                                {
                                        if((cell_info.at(i).at(0) == cell_info.at(j).at(0)) && (cell_info.at(i).at(1)) == cell_info.at(j).at(1) && i!=j)
                                        {
                                                cell_info.erase(cell_info.begin()+i,cell_info.begin()+j);

                                                if(i > cell_info.size() || j > cell_info.size())
                                                {
                                                        break;
                                                }
                                        }
                                }
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
   

                        for(int k = cell_info.size()-1; k >= 0 ; k--)
                        {
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

                        for(int i=0;i<return_path.size()-1;i++)
                        {
                                int x1{return_path.at(i).at(0)};
                                int y1{return_path.at(i).at(1)};

                                int x2{return_path.at(i+1).at(0)};
                                int y2{return_path.at(i+1).at(1)};

                                int x_diff{x2-x1};
                                int y_diff{y2-y1};

                                Simulator::setColor(return_path.at(i).at(0),return_path.at(i).at(1), 'c');

                                /**
                                 * @brief 
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

                        std::cerr<<"## BACK HOME ##"<<std::endl;
                }


};

}//namespace rwa2group19





int main(int argc, char *argv[])
{

        rwa2group19::SetMaze SM;
        rwa2group19::Algorithm A;
        rwa2group19::return_path RP;
        
        SM.m_set_outer_walls();
        SM.m_print_grind_numbers();
        
        std::array<int,2> goal{SM.m_generate_goal()};      // goal variable to store x and y coordinates of goal; and initialize it accessing m_goal_generate method


        char direction{};
        std::vector<std::array<std::string,4>> cell_info;

        tie(cell_info, direction) = A.m_left_wall_follower(goal);
        RP.m_return_path(cell_info,direction);
        
        return 0;
}
