//
//  main.cpp
//  cristal-growing-simulation
//
//  Created by Carsten Daub on 2025-08-20.
//

#include <iostream>
#include <random>

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
    
    int myRand = randomNumber();
    std::cout << "Random Number: " << myRand << "\n";

    return 0;
}
