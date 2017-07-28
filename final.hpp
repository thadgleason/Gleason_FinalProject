/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   final.hpp
 * Author: thad
 *
 * Created on July 27, 2017, 5:11 PM
 */
using namespace std;
#ifndef FINAL_HPP
#define FINAL_HPP

struct vertex;

struct adjVertex
{
    vertex* v;
    int weight;
    string route;
};

struct vertex
{
    string name;
    vector <adjVertex> adj;
    bool visited;
    int distance;
    vertex* parent;
};

struct node
{
    string name;
    string parentPath;
    string childPath;
    int parentDist;
    int childDist;
    node* parent;
    node* child;
};

class graph
{
    public:
        graph();
        ~graph();
        void addEdge(string v1, string v2, int weight, string r);
        void addVertex(string n);
        void displayEdges();
        void buildNetwork();
        vertex* shortestPath(string first, string second);
    private:
        vertex* search(string name);
        vector<vertex*> vertices;
};

class list
{
private:
    node* root;
public:
    list();
    node* search();
    void calcFuel();
    void calcCost();
    int calcDist();
    void calcTime();
    void printList();
    void buildList(vertex* temp);
};


#endif /* FINAL_HPP */

