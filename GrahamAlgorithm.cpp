/* 
    Graham algorithm - find points creating border of points group.
    
    Created by Łukasz Szarkowicz
    email: szarkowicz@gmail.com
*/

#include <iostream>
#include <stack>
using namespace std;

// Point class methods
class Point 
{
    public:
        Point(float xVal, float yVal);
        float x,y;

        void printPoint(void);
        
};

// pointer to Root Point - the lowest and the most left point
Point *rootPoint;

// constructor
Point::Point(float xVal, float yVal)
{
    x = xVal;
    y = yVal;

    cout << "\nConstruct Point x: " << xVal << " and y: " << yVal;
}

// print point's data on screen
void Point::printPoint ( void )
{
    cout << "\n{ " << x << ", " << y << " }, ";
}

// get the next to top point on stack
Point* beforeTopPoint(stack<Point *> &stackPointer)
{
    Point *p = stackPointer.top();

    // if there is only one Point on stack, return this point
    if (stackPointer.size() > 1)
    { 
        stackPointer.pop();
        Point *result = stackPointer.top();
        stackPointer.push(p);
        return result;
    }

    return p;
}

/* check order of points
    
    returns:
    0  : points are collinear
    1  : points a,b,c are in clockwise order
    2  : points a,b,c are in counter-clockwise order
*/
int pointOrder(Point *a, Point *b, Point *c) 
{
    int area = (b->y - a->y) * (c->x - b->x) - (b->x - a->x) * (c->y - b->y);
    if (area > 0)
        return 1;
    else if (area < 0)
        return 2;
    return 0;
}

// get distance between two points
float distance(Point *a, Point *b)  {
    float xLength = a->x - b->x;
    float yLength = a->y - b->y;
    return xLength * xLength + yLength * yLength;
}

// change two points with their places in array with points
void changePlaces(Point* pointsArray[], int positionA, int positionB)
{
    Point *tmp = pointsArray[positionA];
    pointsArray[positionA] = pointsArray[positionB];
    pointsArray[positionB] = tmp;
}

// get Point's index in array
int elementPositionInArray(Point* pointsArray[], int size, Point *point)
{
    for (int i = 0; i < size; ++i)
    {
        if (pointsArray[i] == point)
        {
            return i;
        }
    }

    return -1;
}

// find the lowest point - Root Point
void findTheLowestPoint(Point* arr[], int size)
{
    Point *theLowestPoint = arr[0];
    for (int i = 0; i < size; i++)
    {
         if (theLowestPoint->y > arr[i]->y || (theLowestPoint->y == arr[i]->y && theLowestPoint->x > arr[i]->x)) 
            theLowestPoint = arr[i];
    }

    rootPoint = theLowestPoint;

    int rootPosition = elementPositionInArray(arr, size, rootPoint);

    if (rootPosition == -1)
    {
        cout << "\nBad root position";

    } else {
        //put rootPosition on 0 index in table
        changePlaces(arr, 0,rootPosition);
    }
}

// print all points in table in order on screen
void printTable(Point* arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i]->printPoint();
    }
}

// sort array of Points
void sortArray(Point* pointsArray[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int y = i+1; y < size; ++y)
        {
            Point *point1 = pointsArray[i];
            Point *point2 = pointsArray[y];
            int order = pointOrder(rootPoint, point1, point2);
            if (order == 0) {
                if (distance(rootPoint, point2) <= distance(rootPoint, point1)) 
                {
                    changePlaces(pointsArray, i,y);

                }
            } else if (order == 1)
            {
                changePlaces(pointsArray, i,y);
            }
        }
    }
}

int main()
{
    int z;
    // init points
    Point *pointsTable[12] = {
                            new Point(0.0, 0.0),
                            new Point(1.0, 0.0),
                            new Point(2.0, 0.0),
                            new Point(3.0, 0.0),
                            new Point(0.0, 1.0),
                            new Point(1.0, 1.0),
                            new Point(2.0, 1.0),
                            new Point(3.0, 1.0),
                            new Point(0.0, 2.0),
                            new Point(1.0, 2.0),
                            new Point(2.0, 2.0),
                            new Point(3.0, 2.0),
    }; 

    // count element numbers of pointsTable
    int elementsNumber = sizeof( pointsTable ) / sizeof( pointsTable[0] );
    
    findTheLowestPoint(pointsTable, elementsNumber);
    sortArray(pointsTable, elementsNumber);

    cout << "\nAFTER SORT:";
    printTable(pointsTable, elementsNumber);

    // put 3 points from pointsTable start on stack
    stack<Point *> points;
    points.push(pointsTable[0]);
    points.push(pointsTable[1]);
    points.push(pointsTable[2]);

    for (int i = 3; i < elementsNumber; i++)
    {
      while ( pointOrder(beforeTopPoint(points), points.top(), pointsTable[i]) != 2 && points.size() > 1)
         points.pop();
      
      points.push(pointsTable[i]);
    }

    cout << "\nPoints creating border of points group: ";
    while (!points.empty())
    {
        Point *p = points.top();
        p->printPoint();
        points.pop();
    }

    // pause program
    cin >> z;
    return 0;
}
