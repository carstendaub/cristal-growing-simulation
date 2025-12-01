//
//  main.cpp
//  cristal-growing-simulation
//
//  Created by Carsten Daub on 2025-08-20.
//

#include <iostream>
#include <random>
#include <vector>

#include <unistd.h>
#include <limits.h>

// for command line arguments
#include <cstring> // for strcmp
#include <cstdlib> // for atoi

// for file writing
#include <fstream>

// Function to generate a random number
int randomNumber() {
    static std::random_device rd;
    //static std::mt19937 gen(rd());
    static std::mt19937 gen(12341); // Set your desired seed here
    static std::uniform_int_distribution<> distrib(0, 3); // Adjust the range as needed
    return distrib(gen);
}

// Function to check if any position has been occupied before
bool hasAnyPositionBeenOccupied(int x, int y, const std::vector<int>& posX, const std::vector<int>& posY) {
    // x and y are the new positions to check
    // posX and posY are the vectors containing all previous positions
    for (size_t i = 0; i < posX.size(); ++i) {
        if (posX[i] == x && posY[i] == y) {
            return true;
        }
    }
    return false;
}
    



bool runSimulation(int& numberOfSteps, int& countCrystalNotGrowing) {
    // this function runs the simulation of the crystal growth

    bool printToFile = true; // flag to control file output
    
    
    // the current positions of the cristal
    // make initial groth step x+1
    std::vector <int> crystalPositionX = {0,1}; // first growth step in dirextion x+1
    std::vector <int> crystalPositionY = {0,0}; // first growth step in dirextion y+0

    int myRand; //for storing the current random number
    std::vector<int> crystalMove(0); // vector to store the crystal groth direction from random number
    
    // loop for the crystal growth steps
    for (int randLoop = 0; randLoop < numberOfSteps - 1; ++randLoop) {
        // check if the current position is completely surrounded, if so, break the loop
        int currentPositionX = crystalPositionX.at(crystalPositionX.size() - 1); // get the last position of the crystal in x direction
        int currentPositionY = crystalPositionY.at(crystalPositionY.size() - 1);
        
        bool upOccupied = hasAnyPositionBeenOccupied(currentPositionX, currentPositionY + 1, crystalPositionX, crystalPositionY);
        bool downOccupied = hasAnyPositionBeenOccupied(currentPositionX, currentPositionY - 1, crystalPositionX, crystalPositionY);
        bool leftOccupied = hasAnyPositionBeenOccupied(currentPositionX - 1, currentPositionY, crystalPositionX, crystalPositionY);
        bool rightOccupied = hasAnyPositionBeenOccupied(currentPositionX + 1, currentPositionY, crystalPositionX, crystalPositionY);
        if (upOccupied && downOccupied && leftOccupied && rightOccupied) {
            //std::cout << "Crystal is completely surrounded at position (" << currentPositionX << ", " << currentPositionY << "). Stopping growth.\n";
            break;
        }
        
        
        myRand = randomNumber();
        
        // if we move in x-direction, which means myRand is 0 or 1
        if(myRand==0 || myRand==1) {
            // move in direction x+1
            
            // the new position of the crystal is the last position + 1 in this case 0
            int newPositionX;
            if(myRand==0){
                newPositionX = currentPositionX + 1;
            }
            else if(myRand==1)
            {
                newPositionX = currentPositionX - 1;
            }
            else
            {
                return 1; // this should never happen
            }
            
            // check if we are coming from the same direction, if not, update the position
            // returns FALSE if the position has not been occupied before
            // returns TRUE if the position has been occupied before
            bool positionOccupied = hasAnyPositionBeenOccupied(newPositionX, currentPositionY, crystalPositionX, crystalPositionY);
            //std::cout << "Position Occupied: " << positionOccupied << "\n";
            
            if (positionOccupied == false) {
                // crystal grows
                crystalPositionX.push_back(newPositionX); // add new position to crystalPositionX
                crystalPositionY.push_back(currentPositionY); // keep y position
                
                //std::cout << "Crystal grows in x-direction\n";
            }
            else {
                // crystal does not grow
                --randLoop; // decrement randLoop to retry this step
                
                //std::cout << "Crystal does not grow.\n";
                countCrystalNotGrowing++; // increment the counter if the crystal does not grow
            }
        }
        // if we move in y-direction, which means myRand is 2 or 3
        else if(myRand==2 || myRand==3) {
            // move in y-direction
            
            // the new position of the crystal is the last position + 1 in this case 2
            int newPositionY;
            if(myRand==2){
                newPositionY = currentPositionY + 1;
            }
            else if(myRand==3)
            {
                newPositionY = currentPositionY - 1;
            }
            else
            {
                return 1; // this should never happen
            }
            
            // check if we are coming from the same direction, if not, update the position
            // returns FALSE if the position has not been occupied before
            // returns TRUE if the position has been occupied before
            bool positionOccupied = hasAnyPositionBeenOccupied(currentPositionX, newPositionY, crystalPositionX, crystalPositionY);
            //std::cout << "Position Occupied: " << positionOccupied << "\n";
            
            if (positionOccupied == false) {
                // crystal grows
                crystalPositionX.push_back(currentPositionX); // keep x position
                crystalPositionY.push_back(newPositionY); // add new position to crystalPositionY
                
                //std::cout << "Crystal grows in y-direction\n";
            }
            else {
                // crystal does not grow
                --randLoop; // decrement randLoop to retry this step
                
                //std::cout << "Crystal does not grow.\n";
                countCrystalNotGrowing++; // increment the counter if the crystal does not grow
            }
        }
        else {
            std::cerr << "Error: Invalid random number generated: " << myRand << "\n";
            return 1; // exit with error
        }
    }
    
    //std::cout << "unsuccessfull growing steps: " << countCrystalNotGrowing << "\n";
    
    int totalCtystalSteps = static_cast<int>(crystalPositionX.size());
    std::cout << "Total crystal growing steps: " << totalCtystalSteps << "\n";
    
    // here we print the full path of the crystal
    //std::cout << "Full Crystal Path:\n";
    //for (size_t i = 0; i < crystalPositionX.size(); ++i) {
    //    std::cout << "(" << crystalPositionX[i] << ", " << crystalPositionY[i] << ")\n";
    //}
    
    if(printToFile){
        // write the crystal path to a CSV file for further analysis or plotting
        std::ofstream outFile("/Users/carsten.daub/Downloads/crystal_path.csv");
        //std::ofstream outFile("crystal_path.csv");
        if (outFile.is_open()) {
            outFile << "x,y\n"; // header
            for (size_t i = 0; i < crystalPositionX.size(); ++i) {
                outFile << crystalPositionX[i] << "," << crystalPositionY[i] << "\n";
            }
            outFile.close();
            //std::cout << "Crystal path written to crystal_path.csv\n";
        } else {
            std::cerr << "Failed to open crystal_path.csv for writing.\n";
        }
    }
    // the statistical analysis of the crystal growth can be done here
    // e.g., calculating the distance from the origin, number of direction changes, etc.
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    //global variables
    int countCrystalNotGrowing = 0; // counter for the number of times the crystal does not grow
    int numberOfSteps = 10; // default argument for number of growth steps for the crystal, overwritten by command line argument if provided
    
    // parse command line arguments
    for (int i = 1; i < argc - 1; ++i) {
        if (std::strcmp(argv[i], "-iterations") == 0) {
            numberOfSteps = std::atoi(argv[i + 1]);
        }
    }
    // for debugging purposes print the number of steps
    std::cout << "numSteps from command line: " << numberOfSteps << "\n";
    
    for(int i=0; i<100; i++)
        runSimulation(numberOfSteps, countCrystalNotGrowing);

    return 0;
}
