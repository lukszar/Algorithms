//
//  Find PI Algorithm
//  Algorithm searches PI value by monte carlo.
//
//  Created by Lukasz Szarkowicz on 24.11.2014.
//  Copyright (c) 2014 Lukasz Szarkowicz. All rights reserved.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>

#define MAX_LOOP 100000
#define SQUARE_SIZE INT_MAX

using namespace std;

// Point class methods
class Point
{
public:
    Point(float xVal, float yVal);
    float x,y;
    
    void printPoint();
};

Point::Point(float xVal, float yVal)
{
    x = xVal;
    y = yVal;
}

// print point's data on screen
void Point::printPoint()
{
    cout << "\n{ " << x << ", " << y << " }, ";
}

class ComputePi {
    
    public:
        int square; // point with (square, square) coordinates making square
        Point circleRoot = Point(0.0, 0.0); // middle of the circle
        Point randomPoint = Point(0.0, 0.0);
        float piValue;
        int simulateCounter = 0;
    
        long int pointsNumberInSquare = 0;
        long int pointsNumberInCircle = 0;
    
    ComputePi(int value) {
        square = value;
        circleRoot.x = (float)value/2.0;
        circleRoot.y = (float)value/2.0;
    };
    
    int generateRandom() {
        /* generate number between 0 and square value: */
        
        int randomNumber = rand() % (square + 1);
        return randomNumber;
    };
    
    float countDistanceFromRootPointToPoint(Point point) {
        
        float xLength = circleRoot.x - point.x;
        float yLength = circleRoot.y - point.y;
        return sqrt(xLength * xLength + yLength * yLength);
    };
    
    void generateNextPoint() {
        
        randomPoint.x = generateRandom();
        randomPoint.y = generateRandom();
    }
    
    float simulate()
    {
        long int i = 0;
        while (i<MAX_LOOP) // define simulateCounter in while loop for break after n times value doesn't change
        {
            generateNextPoint();
            float distance = countDistanceFromRootPointToPoint(randomPoint);
            
            if (distance <= (float)square/2) {
                pointsNumberInCircle++;
            }
            
            pointsNumberInSquare++;
            float newPiValue = ((float)pointsNumberInCircle/(float)pointsNumberInSquare)*4.0;
            
            if (newPiValue != piValue) {
                simulateCounter = 0;
                piValue = newPiValue;
            } else {
                simulateCounter ++;
            }
            
            cout << "\n" << i << ". Value of pi = " << piValue << " with difference from real PI value: " << piValue-M_PI;
            i++;
        }
        return piValue;
    }
};

int main(int argc, const char * argv[]) {

    ComputePi compute(SQUARE_SIZE);
    
    /* initialize random seed: */
    srand ((unsigned int)time(NULL));

    float pi = compute.simulate();
    
    cout << "\nThe result of computing is: " << pi;
    
    getchar();
    return 0;
}
