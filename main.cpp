#include <iostream>
#include <vector>
#include <limits>
#include<queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> vertPair;

class Graphs_P3
{
    struct vertexNode {
        bool headNode;
        vertexNode *next;
        int name;
        int weight;
        int numEdges = 0;

        vertexNode() = default;

        vertexNode(int value, bool isHead, int weight, vertexNode* next){
            this->name = value;
            headNode = isHead;
            this->weight = weight;
            this->next = next;
        }
    };

private:
    const int INF = std::numeric_limits<int>::max();
    const static int MAX_NUM_VERTICIES = 51;
    vertexNode vertArray[MAX_NUM_VERTICIES];
    int numVerticies = 0;
    int checkForVertex[MAX_NUM_VERTICIES];
public:
    /* constructor */

    Graphs_P3(){
        for(int i = 0; i < MAX_NUM_VERTICIES; i++){
            checkForVertex[i] = 0;
        }
    }

    /*primary methods*/

    void insertVertex(int vertex); //inserts new vertex in graph
    void insertEdge(int from, int to, int weight);  //inserts new edge in graph
    bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
    int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
    vector<int> getAdjacent(int vertex);  //return an array of integers representing vertices adjacent to vertex
    void printDijkstra(int source);  //prints result of running Dijkstra algorithm with source vertex
    void printGraph(); //prints graph in a format sorted by ascending vertex and edge list\

    /* helper methods*/

    bool isVertex(int vertex);
};

void Graphs_P3::insertVertex(int vertex) {
    vertArray[vertex] = vertexNode(vertex, true, -999, nullptr);
    checkForVertex[vertex] = 1;
    numVerticies++;
}

bool Graphs_P3::isVertex(int vertex) {
    if (checkForVertex[vertex] == 0){
        return false;
    }

    else {
        return true;
    }
}

void Graphs_P3::insertEdge(int from, int to, int weight) {
    if(!isVertex(from)){
        insertVertex(from);
    }

    if (!isVertex(to)){
        insertVertex(to);
    }

    vertexNode *head = &vertArray[from];
    vertexNode *current = head;
    vertexNode *newEdge = new vertexNode(to, false, weight, nullptr);

    while (current->next != nullptr){
        current = current->next;
    }

    current->next = newEdge;
    head->numEdges = head->numEdges + 1;

    /*
    //comment out the following code to make directed graphs
    vertexNode *head2 = &vertArray[to];
    vertexNode *current2 = head2;
    vertexNode *newEdge2 = new vertexNode(to, false, weight, nullptr);

    while (current2->next != nullptr){
        current2 = current2->next;
    }

    current2->next = newEdge2;
    head2->numEdges = head2->numEdges + 1;
    */
}

bool Graphs_P3::isEdge(int from, int to) {
    vertexNode *current = &vertArray[from];

    while(current != nullptr){
        if(current->name == to){
            return true;
        }
        current = current->next;
    }

    return false;
}

// FIXME getweight() causes segfault when checking weight of an edge that doesn't exist
int Graphs_P3::getWeight(int from, int to) {
    vertexNode *current = &vertArray[from];

    while (current != nullptr){
        if(current->name == to){
            return current->weight;
        }
        current = current->next;
    }

    return std::numeric_limits<int>::max();
}

vector<int> Graphs_P3::getAdjacent(int vertex) {
    vertexNode *curr = &vertArray[vertex];
    vector<int> arr;
    curr = curr->next;
    int i = 0;

    while (curr != nullptr) {
        arr.push_back(curr->name);
        curr = curr->next;
    }

    sort(arr.begin(), arr.end());

    return arr;
}

void Graphs_P3::printDijkstra(int source) {
    priority_queue<vertPair, vector<vertPair>, greater<vertPair>> minHeap; //Minheap of pairs contraining (weight from source, vertex name)
    vector<int> weights(MAX_NUM_VERTICIES, INF); // vector of weights from source for each vert (weights[vert1->name] = weight1), all weights start at INF
    string pathBase = to_string(source);
    vector<string> paths(MAX_NUM_VERTICIES, pathBase); // vector of paths from source to vert (paths[vert1->name] = Vert1PathToSourceString), all paths initialized as toString(source)

    minHeap.push(make_pair(0, source)); //adds source vertex to minheap with weight 0
    weights[source] = 0;

    // on each iteration: takes the vertex with the lowest weight from source and assigns it to *top (will always be the top item of the minheap), removes that vertex from the minheap
    // and then checks all adjacent nodes (represented as variable "adjToTop") to *top to see if there is a path to source through *top that is shorter than adjToTop's current shortest path
    // from source (which is stored in weights[adjToTop->name]).
    // if a shorter path to source is found through *top, adjToTop's weight-to-source name is updated in weight[adjToTop->name], and a new pair(weights[adjToTop], adjToTop->name) is added
    // to minHeap, so vertices adjacent to "adjToTop" can be checked for a shorter path from source.
    //*top is always the source vertex on the first iteration, and Weights are always updated when they are reached for the first time because weights are initialized to INF.
    while(!minHeap.empty()){
        int D = minHeap.top().second; // sets D to name of vertex in the minheap with smallest distance to source
        minHeap.pop(); // removes D (from previous line) from minheap
        vertexNode *top = &vertArray[D]; // vertexNode of vertexName from top of minheap
        vertexNode *adjToTop = top->next; // first node in adjacency list with head "*top"

        while(adjToTop != nullptr){
            if (weights[adjToTop->name] > weights[top->name] + adjToTop->weight){ // checks if there is a path through *top that is shorter than adjToTop's current smallest path from source
                weights[adjToTop->name] = weights[top->name] + adjToTop->weight;
                paths[adjToTop->name] = paths[top->name] + "-" + to_string(adjToTop->name);
                minHeap.push(make_pair(weights[adjToTop->name], adjToTop->name));
            }
            adjToTop = adjToTop->next;
        }
    }

    int counter = 1;
    cout<< "V D P\n";
    for (int i = 0; i < MAX_NUM_VERTICIES; ++i) {
        if (i != source) {
            if(checkForVertex[i] == 1) {
                cout << i << " " << weights[i] << " " << paths[i];
                counter++;
                if (counter != numVerticies){
                    cout << "\n";
                }
            }
        }
    }
}

void Graphs_P3::printGraph() {
    int counter = 0;
    for (int i = 0; i < MAX_NUM_VERTICIES; i ++){
        if (checkForVertex[i] == 1) {
            cout << vertArray[i].name;
            vector<int> adjacent = getAdjacent(vertArray[i].name);
            int size = adjacent.size();
            int j;
            j=0;
            while(j<size)
            {
                cout<< " " << adjacent[j];
                j++;
            }
            counter++;
            if (counter != numVerticies) {
                cout << "\n";
            }
        }
    }
}

int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    int noOfLines, operation, vertex, to, fro, weight,source,j;
    vector<int> arr;
    int arrSize;
    Graphs_P3 g;
    cin>>noOfLines;
    for(int i=0;i<noOfLines;i++)
    {
        cin>>operation;
        switch(operation)
        {
            case 1:
                cin>>vertex;
                g.insertVertex(vertex);
                break;
            case 2:
                cin>>fro;
                cin>>to;
                cin>>weight;
                g.insertEdge(fro,to,weight);
                break;
            case 3:
                cin>>fro;
                cin>>to;
                cout<<g.isEdge(fro,to)<<"\n";
                break;
            case 4:
                cin>>fro;
                cin>>to;
                cout<<g.getWeight(fro,to)<<"\n";
                break;
            case 5:
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                arrSize = arr.size();
                j=0;
                while(j<arrSize)
                {
                    cout<<arr[j]<<" ";
                    j++;
                }
                cout<<"\n";
                break;
            case 6:
                cin>>source;
                g.printDijkstra(source);
                cout<<"\n";
                break;
            case 7:
                g.printGraph();
                cout<<"\n";
                break;
        }
    }
}