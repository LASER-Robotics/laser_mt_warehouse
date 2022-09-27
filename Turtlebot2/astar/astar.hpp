#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <math.h>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Astar{
  private:
    Mat image;

    struct Node{
      bool obstacle = false;
      bool visited = false;
      float globalGoal = INFINITY;
      float localGoal = INFINITY;
      int x = 0;
      int y = 0;
      vector <Node*> neighbours;
      Node* parent = nullptr;
    };

    Node *nodes = nullptr;
    Node *start = nullptr;
    Node *end = nullptr;

  public:
    int width;
    int height;
    Astar(string pathToMap);
    void setStartnEnd(int x1, int y1, int x2, int y2);
    void solveAstar();

    float expor(){
      return nodes[0].visited;
    }
};


#endif