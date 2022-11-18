#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>    //For instantiating class object using smart pointers, in order to store object on heap
#include "simulator/simulator.h"
#include "algorithm.h"
#include "maze.h"



int main(int argc, char *argv[])
{

        //rwa2group19::SetMaze M;
        //rwa2group19::Algorithm A;

        auto maze = std::make_unique<rwa2group19::SetMaze>();
        auto algo = std::make_unique<rwa2group19::Algorithm>();
        
       // M.m_set_outer_walls();
        //M.m_print_grind_numbers();

        maze->m_set_outer_walls();
        maze->m_print_grind_numbers();
        
        std::array<int,2> goal{maze->m_generate_goal()};      // goal variable to store x and y coordinates of goal; and initialize it accessing m_goal_generate method
       
        std::vector<std::array<std::string,4>> cell_data;

        cell_data = algo->m_left_wall_follower(goal);
        algo->m_return_path(cell_data);
        
        return 0;
}
