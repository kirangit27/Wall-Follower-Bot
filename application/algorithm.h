/**
 * @file algorithm.h
 * @author Kiran Suvas Patil
 * @brief 
 * @version 0.9
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__
#include <iostream>
#include <string>
#include <vector>
#include <array>
#pragma once

namespace rwa2group19{

/**
 * @brief  
 * @class 
 * 
 */
class Algorithm{

        private:
                std::vector<std::array<int,2>> s;            //vector to keep record of current position in terms of 2 element 1D array (x,y)        
                std::vector<std::array<int,2>> dead_end;     //vector to keep record of current position in terms of 2 element 1D array (x,y)

                std::vector<char> dir;                       //vector to keep record of direction facing (N,S,E,W)                      
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
                 * @param[in]
                 * 
                 */
                std::vector<std::array<std::string,4>> m_left_wall_follower(std::array<int,2> goal);
                       

                /**
                 * @brief 
                 * 
                 */
                std::vector<std::array<std::string,4>> m_right_wall_follower(std::array<int,2> goal);       

                               
                /**
                 * @brief 
                 * 
                 */
                void  m_return_path(std::vector<std::array<std::string,4>> cell_data);           

    };//class Algorithm

}//namespace rwa2group19


#endif
