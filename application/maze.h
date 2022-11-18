/**
 * @file maze.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MAZE_H__
#define __MAZE_H__

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For the time()


namespace rwa2group19{

        /**
         * @brief 
         * 
         */
        class SetMaze{
                private:
                        std::string grid;
                        int x{};
                        int y{};
                        unsigned seed{};                        

                public:
                        /**
                         * @brief 
                         * 
                         */
                        void m_print_grind_numbers();


                        /**
                         * @brief 
                         * 
                         */
                        void m_set_outer_walls();
        

                        /**
                         * @brief 
                         * 
                         */
                        std::array<int,2> m_generate_goal();
        
        };//class SetMaze
}//namespace rwa2group19


#endif
