#include <iostream>
#include <vector>
#include <list>
#include <limits>
using namespace std;



class Graphs_P3
{
    struct vertexNode {
        bool headNode;
        vertexNode *next;
        int value;
        int weight;

        vertexNode() = default;

        vertexNode(int value, bool isHead, int weight, vertexNode* next){
            this->value = value;
            headNode = isHead;
            this->weight = weight;
            this->next = next;
        }
    };

private:
    const static int MAX_NUM_VERTICIES = 51;
    vertexNode vertArray[51];
    int numVerticies = 0;
    int checkForVertex[51];
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
    //int * getAdjacent(int vertex);  //return an array of integers representing vertices adjacent to vertex
    //void printDijkstra(int source);  //prints result of running Dijkstra algorithm with source vertex
    //void printGraph(); //prints graph in a format sorted by ascending vertex and edge list\

    /* helper methods*/

    bool isVertex(int vertex);;
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
}

bool Graphs_P3::isEdge(int from, int to) {
    vertexNode *current = &vertArray[from];

    while(current != nullptr){
        if(current->value == to){
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
        if(current->value == to){
            return current->weight;
        }
        current = current->next;
    }

    return std::numeric_limits<int>::max();
}

int main()
{

    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    int noOfLines, operation, vertex, to, fro, weight,source,j;
    int *arr;
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
/*
            case 5:
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                j=0;
                while((arr+j)!=nullptr)
                {
                    cout<<*(arr+j);
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
*/
        }
    }

}