#include <iostream>
#include <vector>
#include <climits>

#include "final.hpp"

using namespace std;
graph::graph() { }
graph::~graph() { }
vertex* graph::search(string name)
{
    for (int i = 0; i < vertices.size(); i++)
        if (vertices[i]->name == name)
            return vertices[i];
}
void graph::addEdge(string v1, string v2, int weight, string r)
{

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == v1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j]->name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = vertices[j];
                    av.weight = weight;
                    av.route = r;
                    vertices[i]->adj.push_back(av);
                }
            }
        }
    }
}
void graph::addVertex(string n)
{
    bool found = false;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == n)
        {
            found = true;
            cout << vertices[i]->name << " found.\n";
        }
    }
    if (found == false)
    {
        vertex* v = new vertex;
        v->name = n;
        v->visited = false;
        vertices.push_back(v);
    }
}
void graph::buildNetwork()
{
    addVertex("Denver");
    addVertex("Colorado Springs");
    addVertex("Pueblo");
    addVertex("Red Table");
    addVertex("Garfield CO");
    addVertex("Montrose");
    addVertex("Grand Junction");
    addVertex("Hanksville");
    addVertex("Mc Elroy");
    addVertex("Gunnison");
    addVertex("Carbon CO");
    addVertex("Rocky Mountain Metro");
    addEdge("Denver", "Colorado Springs", 51, "V389 to V611");
    addEdge("Denver", "Pueblo", 86, "V389");
    addEdge("Denver", "Red Table", 121, "V356");
    addEdge("Denver", "Mc Elroy", 86, "V8");
    addEdge("Denver", "Gunnison", 139, "V160");
    addEdge("Colorado Springs", "Denver", 51, "V611 to V389");
    addEdge("Colorado Springs", "Pueblo", 41, "V81");
    addEdge("Colorado Springs", "Red Table", 119, "V108");
    addEdge("Colorado Springs", "Rocky Mountain Metro", 64, "V81");
    addEdge("Pueblo", "Denver", 86, "V389");
    addEdge("Pueblo", "Colorado Springs", 41, "V81");
    addEdge("Pueblo", "Gunnison", 126, "V244");
    addEdge("Red Table", "Denver", 121, "V356");
    addEdge("Red Table", "Colorado Springs", 119, "V108");
    addEdge("Red Table", "Garfield CO", 47, "V108 to V8");
    addEdge("Red Table", "Montrose", 74, "V361");
    addEdge("Red Table", "Grand Junction", 93, "V134");
    addEdge("Red Table", "Mc Elroy", 41, "V361");
    addEdge("Red Table", "Gunnison", 61, "V421");
    addEdge("Garfield CO", "Red Table", 47, "V8 to V108");
    addEdge("Garfield CO", "Grand Junction", 59, "V8");
    addEdge("Garfield CO", "Mc Elroy", 67, "V8");
    addEdge("Montrose", "Red Table", 74, "V361");
    addEdge("Montrose", "Grand Junction", 54, "V26");
    addEdge("Montrose", "Hanksville", 135, "V244");
    addEdge("Grand Junction", "Red Table", 93, "V134");
    addEdge("Grand Junction", "Garfield CO", 59, "V8");
    addEdge("Grand Junction", "Montrose", 54, "V26");
    addEdge("Grand Junction", "Hanksville", 99, "V8");
    addEdge("Grand Junction", "Gunnison", 92, "V484");
    addEdge("Grand Junction", "Carbon CO", 99, "V134");
    addEdge("Hanksville", "Montrose", 135, "V244");
    addEdge("Hanksville", "Grand Junction", 99, "V8");
    addEdge("Hanksville", "Carbon CO", 73, "V208");
    addEdge("Mc Elroy", "Denver", 86, "V8");
    addEdge("Mc Elroy", "Red Table", 41, "V361");
    addEdge("Mc Elroy", "Garfield CO", 67, "V8");
    addEdge("Gunnison", "Denver", 139, "V160");
    addEdge("Gunnison", "Pueblo", 126, "V244");
    addEdge("Gunnison", "Red Table", 61, "V421");
    addEdge("Gunnison", "Grand Junction", 92, "V484");
    addEdge("Carbon CO", "Grand Junction", 99, "V134");
    addEdge("Carbon CO", "Hanksville", 73, "V208");
    addEdge("Rocky Mountain Metro", "Colorado Springs", 64, "V81");
}
void graph::displayEdges()
{
    //loop through all vertices and adjacent vertices
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i]->name << "-->";
        for (int j = 0; j < vertices[i]->adj.size(); j++)
        {
            //i = j;
            cout << vertices[i]->adj[j].v->name << "***";
        }
        cout << endl;
    }
}
vertex* graph::shortestPath(string first, string second)
{
    vertex* one = search(first);
    vertex* two = search(second);
    two->visited = true;
    two->distance = 0;
    two->parent = nullptr;
    vertex* parent = nullptr;
    vector <vertex*> solved = {two};
    while (!one->visited)
    {
        int minDist = INT_MAX;
        vertex* solvedV = new vertex;
        for (int i = 0; i < solved.size(); i++)
        {
            vertex* s = solved[i];
            for (int j = 0; j < s->adj.size(); j++)
            {
                if (!s->adj[j].v->visited)
                {
                    int dist = s->distance + s->adj[j].weight;
                    if (dist < minDist)
                    {
                        solvedV = s->adj[j].v;
                        minDist = dist;
                        parent = s;
                    }
                }
            }
        }
        solvedV->distance = minDist;
        solvedV->parent = parent;
        solvedV->visited = true;
        solved.push_back(solvedV);
    }
    return one;
}
/*vertex* graph::shortestPath(string first, string second) //Breadth first method
{
    vertex* one = search(first);
    vertex* two = search(second);
    one->visited = true;
    one->distance = 0;
    one->parent = nullptr;
    queue <vertex*> q;
    q.push(one);
    while(!q.empty())
    {
        vertex* n = q.front();
        q.pop();
        for(int i = 0; i < n->adj.size(); i++)
        {
            if(!n->adj[i].v->visited)
            {
                n->adj[i].v->distance = n->distance + n->adj[i].weight;
                n->adj[i].v->parent = n;
                if(n->adj[i].v == two)
                    return n->adj[i].v;
                else
                {
                    n->adj[i].v->visited = true;
                    q.push(n->adj[i].v);
                }
            }
        }
    }
}*/

list::list() { }
void list::buildList(vertex* temp)
{
    root = new node;
    node* newNode = root;
    root->parentPath = "";
    root->parentDist = 0;
    root->parent = nullptr;
    while (temp->parent != nullptr)
    {
        newNode->child = new node;
        node* child = newNode->child;
        child->parent = newNode;
        newNode->name = temp->name;
        for (int i = 0; i < temp->adj.size(); i++)
        {
            if (temp->adj[i].v == temp->parent)
            {
                newNode->childDist = temp->adj[i].weight;
                child->parentDist = newNode->childDist;
                newNode->childPath = temp->adj[i].route;
                child->parentPath = newNode->childPath;
            }
        }
        newNode = child;
        temp = temp->parent;
    }
    newNode->name = temp->name;
    newNode->child = nullptr;
    newNode->childPath = "";
    newNode->childDist = 0;
    newNode->parentPath = newNode->parent->childPath;
    newNode->parentDist = newNode->parent->childDist;
}
int list::calcDist()
{
    node* temp = root;
    int dist = 0;
    while (temp->child != nullptr)
    {
        dist += temp->childDist;
        temp = temp->child;
    }
    return dist;
}
void list::calcFuel()
{
    int fuelFlow;
    cout << "Enter Fuel Flow Rate: ";
    cin >> fuelFlow;
    double fuelCost;
    int velocity;
    cout << "Enter Your Cruise Velocity: ";
    cin >> velocity;

    node* temp = root;
    double gallons;
    while (temp->child != nullptr)
    {
        gallons = ((double) temp->childDist / velocity) * (double) fuelFlow;
        cout << "From " << temp->name << " to " << temp->child->name << " will burn " << gallons << " gallons" << endl;
        temp = temp->child;
    }
    gallons = ((double) calcDist() / (double) velocity) * fuelFlow;
    cout << "Total fuel burned: " << gallons << " gallons" << endl;
}
void list::calcCost()
{
    int fuelFlow;
    cout << "Enter Fuel Flow Rate: ";
    cin >> fuelFlow;
    double fuelCost;
    cout << "Enter Price of Fuel: ";
    cin >> fuelCost;
    int velocity;
    cout << "Enter Your Cruise Velocity: ";
    cin >> velocity;

    node* temp = root;
    double cost;
    while (temp->child != nullptr)
    {
        cost = ((double) temp->childDist / (double) velocity) * (double) fuelFlow * fuelCost;
        cout << "From " << temp->name << " to " << temp->child->name << " will cost $" << cost << endl;
        temp = temp->child;
    }
    cost = ((double) calcDist() / (double) velocity) * (double) fuelFlow * fuelCost;
    cout << "Total cost of trip: $" << cost << endl;
}
void list::calcTime()
{
    double velocity;
    cout << "Enter Your Cruise Velocity: ";
    cin >> velocity;
    velocity /= 60;

    node* temp = root;
    double time;
    while (temp->child != nullptr)
    {
        time = ((double) temp->childDist / velocity);
        cout << "From " << temp->name << " to " << temp->child->name << " will take " << time << " minutes" << endl;
        temp = temp->child;
    }
    time = (calcDist() / velocity);
    cout << "Total time: " << time << " minutes" << endl;
}
void list::printList()
{
    node* temp = root;
    while (temp->child != nullptr)
    {
        cout << "Fly from " << temp->name << " on " << temp->childPath << " for " << temp->childDist << " miles to " << temp->child->name << endl;
        temp = temp->child;
    }
    cout << "Total distance of travel: " << calcDist() << endl;
}
int main()
{


    cout << "Welcome to VOR Flight Planner - Denver North Sectional\n";
    graph denverN = graph();
    denverN.buildNetwork();
    cout << "1. Denver\n2. Colorado Springs\n3. Pueblo\n4. Red Table\n";
    cout << "5. Garfield CO\n6. Montrose\n7. Grand Junction\n8. Hanksville\n9. Mc Elroy\n";
    cout << "10. Gunnison\n11. Carbon CO\n12. Rocky Mountian Metro\nEnter Your Home Airport: ";

    string names[] = {"Denver", "Colorado Springs", "Pueblo", "RedTable", "Garfield CO", "Montrose", "Grand Junction",
        "Hanksville", "Mc Elroy", "Gunnison", "Carbon CO", "Rocky Mountain Metro"};
    int start;
    cin >> start;

    int end;
    cout << "Pick Destination Airport: ";
    cin >> end;

    vertex* last = denverN.shortestPath(names[start - 1], names[end - 1]);
    list path = list();
    path.buildList(last);

    int option = 0;
    while (option != 5)
    {
        cout << "1. Calculate Time of Travel\n2. Calculate Fuel Used\n3. Calculate Fuel Costs\n";
        cout << "4. Print Directions\n5. End Program\nSelect an Option: ";
        cin >> option;

        if (option == 1)
            path.calcTime();
        else if (option == 2)
            path.calcFuel();
        else if (option == 3)
            path.calcCost();
        else if (option == 4)
            path.printList();
    }

    cout << "Thank you for using Denver-North flight planner\nDesigned by Thad Gleason";

    return 0;
}

