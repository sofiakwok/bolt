/**
 * \file bolt.cpp
 * \brief Execute the main program to control the bolt
 * \author Maximilien Naveau
 * \date 2018
 *
 * DynamicGraphManager for bolt main executable.
 */

#include <fstream>
#include "bolt/dgm_bolt_rw.hpp"

int main(int, char*[])
{
    // Get the dynamic_graph_manager config file.
    std::string yaml_path = DYNAMIC_GRAPH_MANAGER_RW_YAML_PATH;

    std::cout << "dgm_bolt_rw: Loading parameters from " << yaml_path << std::endl;
    
    std::ifstream f(yaml_path.c_str());
    if (!f.good())
    {
        throw std::runtime_error("Error: " + yaml_path + " not found!");
    }
    YAML::Node param = YAML::LoadFile(yaml_path);
    // Create the dgm.
    bolt::DGMBoltRW dgm;

    // Initialize and run it.
    dgm.initialize(param);
    dgm.run();
//    dgm.run_single_process();
}