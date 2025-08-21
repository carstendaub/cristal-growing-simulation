//
//  main.cpp
//  cristal-growing-simulation
//
//  Created by Carsten Daub on 2025-08-20.
//

#include <iostream>
#include <random>
#include <vector>

// Function to generate a random number
int randomNumber() {
    static std::random_device rd;
    //static std::mt19937 gen(rd());
    static std::mt19937 gen(12345); // Set your desired seed here
    static std::uniform_int_distribution<> distrib(0, 1); // Adjust the range as needed
    return distrib(gen);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    
    // the current positions of the cristal
    // make initial groth step x+1
    std::vector <int> crystalPositionX = {0,1}; // first growth step in dirextion x+1
    std::vector <int> crystalPositionY = {0,0}; // first growth step in dirextion y+0
    
    int myRand; //for storing the current random number
    std::vector<int> crystalMove(0); // vector to store the crystal groth direction from random number
    
    // start the growth of the crystal after initial step
    for (int randLoop = 0; randLoop < 5; ++randLoop) {
        myRand = randomNumber();
        //crystalMove(myRand);
        std::cout << "Random Number: " << myRand << "\n";
        //std::cout << "crystalPositionX.size(): " << crystalPositionX.size() << "\n";
        int currentPositionX = crystalPositionX.at(crystalPositionX.size() - 1); // get the last position of the crystal in x direction
        int currentPositionY = crystalPositionY.at(crystalPositionY.size() - 1);
        
        int previousPositionX = crystalPositionX.at(crystalPositionX.size() - 2); // get the previous position of the crystal in x direction
        int previousPositionY = crystalPositionY.at(crystalPositionY.size() - 2);

        if(myRand==0) {
                // move in direction x+1

                // the new position of the crystal is the last position + 1 in this case 0
                int newPositionX = currentPositionX + 1;

                // check if we are coming from the same direction, if not, update the position
                if (newPositionX != previousPositionX) {
                    crystalPositionX.push_back(newPositionX); // add new position to crystalPositionX
                    crystalPositionY.push_back(currentPositionY); // keep y position

                    std::cout << "Crystal grows to x+1.\n";
                }
                else {
                    std::cout << "Crystal does not grow.\n";
                }
        }
        else if(myRand==1) {
                // move in direction x-1
//
                // the new position of the crystal is the last position + 1 in this case 0
                int newPositionX = currentPositionX - 1;

                // check if we are coming from the same direction, if not, update the position
                if (newPositionX != previousPositionX) {
                    crystalPositionX.push_back(newPositionX); // add new position to crystalPositionX
                    crystalPositionY.push_back(currentPositionY); // keep y position

                    std::cout << "Crystal grows to x-1.\n";
                }
                else {
                    std::cout << "Crystal does not grow.\n";
                }

            // add new position to crystalPositionX
            std::cout << "Crystal grows to x-1.\n";
         }
        else if(myRand==2) {
            // move in direction y+1
            
            // the new position of the crystal is the last position + 1 in this case 0
            int newPositionY = currentPositionY + 1;
            
            // check if we are coming from the same direction, if not, update the position
            if (newPositionY != previousPositionY) {
                crystalPositionX.push_back(currentPositionX); // keep x position
                crystalPositionY.push_back(newPositionY); // add new position to crystalPositionY
                
                std::cout << "Crystal grows to y+1.\n";
            }
            else {
                std::cout << "Crystal does not grow.\n";
            }
        }
        else if(myRand==3) {
            std::cout << "Crystal grows y-1.\n";
            // the new position of the crystal is the last position + 1 in this case 0
            int newPositionY = currentPositionY - 1;
            
            // check if we are coming from the same direction, if not, update the position
            if (newPositionY != previousPositionY) {
                crystalPositionX.push_back(currentPositionX); // keep x position
                crystalPositionY.push_back(newPositionY); // add new position to crystalPositionY
                
                std::cout << "Crystal grows to y-1.\n";
            }
            else {
                std::cout << "Crystal does not grow.\n";
            }
        }
//        else {
//                std::cout << "Invalid crystal growth direction.\n";
//                exit(1);
//        }

//    }
    }
    
    return 0;
    }
