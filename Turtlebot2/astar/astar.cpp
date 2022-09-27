#include "astar.hpp"
#include <iostream>
#include <list>
#include <map>
#include <fstream>

#define INITIALX 160
#define INITIALY 245
#define FINALX 160
#define FINALY 400

using namespace cv;
using namespace std;

Astar::Astar(string pathToMap){
	image = imread(pathToMap, 1); //440 x 220 = 96800    

	if(image.empty()){ // check the image 
		cout << "can't read the image!\n";
	}else{
		cout << "image ok!\n";
	}

	width = image.cols;		 //220
  	height = image.rows;   //440

	width = width; // pixel -> metros
	height = height; // pixel -> metros

	//map<int, int> diffPixels;
  	nodes = new Node[width*height];

  	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			nodes[y * width + x].x = x; //...because we give each node its own coordinates
			nodes[y * width + x].y = y;
			nodes[y * width + x].parent = nullptr;
			nodes[y * width + x].visited = false;
				if(image.at<Vec3b>(y, x)[0] == 255){
					nodes[y * width + x].obstacle = true;
				}
				else{
					nodes[y * width + x].obstacle = false;
				}
		}
	}
	//Create connections - in this case nodes are on a regular grid
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			if(y > 0)
				nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x + 0)]);
			if(y < height - 1)
				nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x + 0)]);
			if (x > 0)
				nodes[y*width + x].neighbours.push_back(&nodes[(y + 0) * width + (x - 1)]);
			if(x < width - 1)
				nodes[y*width + x].neighbours.push_back(&nodes[(y + 0) * width + (x + 1)]);

			// We can also connect diagonally
			if (y > 0 && x > 0)
				nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x - 1)]);
			if (y < height - 1 && x > 0)
				nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x - 1)]);
			if (y > 0 && x < width - 1)
				nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x + 1)]);
			if (y < height - 1 && x < width - 1)
				nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x + 1)]);
		}
	}
	//circle(image, Point(0,219),0, Scalar(255,0,0));
}

void Astar::setStartnEnd(int x1, int y1, int x2, int y2){
	start = &nodes[y1*width + x1];
	circle(image, Point(x1,y1), 2, Scalar(0,255,0));//set initial point on image

	end = &nodes[y2*width + x2];
	circle(image, Point(x2,y2), 2, Scalar(0,0,255));//set final point on image
	imwrite("/home/pedrolucas/pibiclaser/maps/mazeSolved.png", image);//image to use
}

void Astar::solveAstar(){
	auto distance = [](Node* a, Node* b){  // For convenience
		return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	};

	auto heuristic = [distance](Node* a, Node* b){  // So we can experiment with heuristic
		return distance(a, b);
	};


	Node *nodeCurrent = start;
	start->localGoal = 0.0f;
	start->globalGoal = heuristic(start, end);
	list<Node*> listNotTestedNodes;
	listNotTestedNodes.push_back(start);

	
	while (!listNotTestedNodes.empty() && nodeCurrent != end){
		listNotTestedNodes.sort([](const Node* lhs, const Node* rhs){ 
			return lhs->globalGoal < rhs->globalGoal; 
		});
		// Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...

		while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->visited){
			listNotTestedNodes.pop_front(); 
		}
		// ...or abort because there are no valid nodes left to test

		if (listNotTestedNodes.empty())
			break;

		
		nodeCurrent = listNotTestedNodes.front();

		nodeCurrent->visited = true; // We only explore a node once

		for (auto nodeNeighbour : nodeCurrent->neighbours){
			// ... and only if the neighbour is not visited and is 
			// not an obstacle, add it to NotTested List

			if (!nodeNeighbour->visited && nodeNeighbour->obstacle == 0){
				listNotTestedNodes.push_back(nodeNeighbour);
			}
			
			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->localGoal + distance(nodeCurrent, nodeNeighbour);

			// If choosing to path through this node is a lower distance than what 
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set its distance scores as necessary
			
			if (fPossiblyLowerGoal < nodeNeighbour->localGoal){
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->localGoal = fPossiblyLowerGoal;
				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->globalGoal = nodeNeighbour->localGoal + heuristic(nodeNeighbour, end);
			}
		}
	}

	vector<int> xs, ys;
	vector<pair <int,int>> coordinates;
	set<pair <int,int>> finalCoordinates;

	//DESENHAR
	if (end != nullptr){
		Node *p = end;

			while(p->parent != nullptr){
				circle(image, Point(p->x,p->y),0, Scalar(255,0,0));
				// Set next node to this node's parent
				xs.insert(xs.begin(),p->x);
				ys.insert(ys.begin(),p->y);
				p = p->parent;
			}

		imwrite("/home/pedrolucas/pibiclaser/maps/mazeSolved.png", image); //desenhar
		  
		for(int i = 0; i < xs.size(); i++){
			coordinates.push_back(make_pair(xs[i], ys[i]));
		}
		

		if(coordinates.empty()){
			cout << "not solved." << endl;
		}else{
			cout << "solved." << endl;
		}
		
		for (int i = 0; i < coordinates.size(); i++){
			coordinates[i].first = round(coordinates[i].first *  0.05);
			coordinates[i].second = round(coordinates[i].second *  0.05);
		}
		
		for(int i = 0; i < coordinates.size(); i++){
			finalCoordinates.insert(make_pair(coordinates[i].first, coordinates[i].second));
		}

		//arquivo
		ofstream file;
		file.open("/home/pedrolucas/pibiclaser/maps/coords.csv"); 
		if(file.is_open()){

		file << "X" << "," << "Y" << endl;

			for(auto iterator : finalCoordinates){
				file << iterator.first << "," << iterator.second << endl;
			}

			file.close();	
		}else{
			cout << "Unable to open file";
		} 
	}
}

int main(){

	Astar pathLab = Astar("/home/pedrolucas/pibiclaser/maps/trueMaze.png");
		
	pathLab.setStartnEnd(INITIALX, INITIALY, FINALX, FINALY); // pos initialX, pos intialY, pos finalX, pos finalY 
	pathLab.solveAstar();		
		
  	//g++ astar.cpp -o astar `pkg-config --cflags --libs opencv4` 
	return 0;
}
