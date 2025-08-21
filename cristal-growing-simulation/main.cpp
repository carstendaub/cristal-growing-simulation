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
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 5);
    return distrib(gen);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    int myRand; //for storing random number
    std::vector <int> cristalPosition; //for storing the positions of the crystal
    
    for (int randLoop = 0; randLoop < 10; ++randLoop) {
        myRand = randomNumber();
        cristalPosition.push_back(myRand);
        std::cout << "Random Number: " << myRand << "\n";
        
        switch (myRand) {
            case 0:
                std::cout << "Crystal grows to the left.\n";
                break;
            case 1:
                std::cout << "Crystal grows to the right.\n";
                break;
            case 2:
                std::cout << "Crystal grows upwards.\n";
                break;
            case 3:
                std::cout << "Crystal grows downwards.\n";
                break;
            case 4:
                std::cout << "Crystal grows diagonally left.\n";
                break;
            case 5:
                std::cout << "Crystal grows diagonally right.\n";
                break;
            default:
                std::cout << "Invalid crystal growth direction.\n";
                exit(1);
                
        }
    }
    
    // Iterate over vector to print crystal positions
    for (size_t i = 0; i < cristalPosition.size(); ++i)
        std::cout << "Crystal Position " << i << ": " << cristalPosition[i] << "\n";
    
    return 0;
    }
