#ifndef CONNECTEDCITIES_H
#define CONNECTEDCITIES_H

#include <ctype.h>  // character manipualtion, e.g. tolower()
#include <stdio.h> 
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;


class CityNode {
private:     
  string city;
  vector<string> directRoutedCities;
  vector<string> reachableCities;
  // unordered_set helps with preventing duplicates, used as intermediate to then we copied into reachableCities
  unordered_set<string> reachableDummies;
  // determines if a node's memoization should be saved (there are some cases where it shouldn't be saved)
  bool memo = true;

public:
  CityNode(string city) {
    this->city = city;
  }

  inline string getCity() {
    return city;
  }

  inline vector<string> getDirectRoutedCities() {
    return directRoutedCities;
  }

  inline vector<string> getReachableCities() const {
    return reachableCities;
  }
  
  inline unordered_set<string> getReachableDummies() const {
    return reachableDummies;
  }

  inline bool getMemo() {
    return memo;
  }

  inline void addADirectRoutedCity(string city) {
    directRoutedCities.push_back(city);
  }

  inline void addReachableCity(string city) {
    reachableCities.push_back(city);
  }
  
  inline void addReachableDummy(string city) {
    reachableDummies.insert(city);
  }

  inline void setReachableCities(vector<string> rCities) {
    reachableCities = rCities;
  }

  inline void setMemo(bool boolean) {
    memo = boolean;
  }
};


class ConnectedCities {
    
public:
  
  /**
  * <p>
  * Part A 
  * ---------------------------------------------------------------------------------------
  * For each city in a city list, find the list of reachable cities starting from the city 
  * following the train routes, and sort the cities in the descending order based on the 
  * number of their reachable cities.  
  * 
  * Required specifications - 
  *
  * Given a list of cities, and a list of one-way train routes from one city to another:
  *
  * 1) Create a graph with each node in the graph as an instance of the CityNode class,
  *    the graph can use any STL collection by your choice.
  *
  * 2) Populate the direct routes information to each CityNode's directRoutedCities collection.
  *
  * 3) For each city node in the graph, use Depth First Search algorithm to find all reachable 
  *    cities starting from the city following the train routes and store those reachable cities to 
  *    the CityNode's reachableCities collection. 
  *
  *    IMPORTANT: The reachable cities must include the starting city itself.  
  *
  *    Note: The train route can go from the starting city and stop at several cities 
  *          before reaching the destination city, all cities including the starting city and 
  *          the destination city along the path would be counted as reachable cities from 
  *          the city where the train starts.
  *
  * 4) Sort the cities in the descending order based on the number of their reachable cities,
  *    so that after sorting, starting from the first city in the sorted order, the train can 
  *    reach the greatest number of destination cities following the given one-way routes. 
  *
  * 5) You must use a RECURSIVE algorithm to implement the Depth First Search part to find
  *    all reachable cities from a starting city given the train routes, using an iterative 
  *    approach would result in a 30% penalty to your assignment 4 grade.  
  *
  * 6) You may add necessary helper functions as needed. Follow the comments for hints.
  * 
  * Assumptions - 
  * 1) Each city is represented by a unique two-letter code like "SD", "LA", 
  *    "SF", "SJ", "NY", etc.
  * 2) Each one-way train route is represented by a pair of city codes; for example, 
  *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to 
  *    Los Angeles (LA). 
  *
  * <p>
  * Part B
  * ---------------------------------------------------------------------------------------
  * Show the upper bound of the time complexity of this function would be O(c^2 + c * r) 
  * where:
  * c is the number of cities
  * r is the number of direct routes between cities
  * 
  * ---------------------------------------------------------------------------------------
  * @param  cities  a list of cities with each city identified by a unique two letter code
  * @param  routes  pairs of one-way train routes with each one-way train route represented 
  *                 by a pair of city codes; for example, route {"SD", "LA"} means train 
  *                 can go one-way from San Diego (SD) to Los Angeles (LA).
  *
  *                 NOTE: examples of routes are { {"SD", "LA"},
  *                                                {"LA", "SJ"},
  *                                                {"SJ", "SF"}
  *                                              }   
  *                       refer to driver.cpp for more examples.  
  *
  * @return       A list of CityNodes in descending order of number of reachable cities and 
  *               using ascending alphabetical order of the city code as the tiebreaker.
  * @see         
  */

  // result generated through steps in below helper functions
  static vector<CityNode> citiesSortedByNumOf_Its_ReachableCities_byTrain(
                            vector<string> cities, 
                            vector<pair<string, string>> trainRoutes);


 /* 
  * Below Functions Are Helpers Of citiesSortedByNumOf_Its_ReachableCities_byTrain Function
  * 
  * For Implementation Details, See CPP File, Function Logic Described In Header 
  */


  /* 
   * We are given strings in our input function, to describe the relationships between these strings, we will use a
   * hashmap (unordered_map) that will map these string values to CityNode objects, function will return this map to be used
   * as our graph representation for the rest of the program
   */
  static unordered_map<string, CityNode> createGraphSkeleton(vector<string> &cities);


  // using trainRoute pairs, fill our hashmap of cities with adjacent nodes
  static void fillAdjacents(vector<pair<string, string>>& trainRoutes, unordered_map<string, CityNode>& graph);


  // fill each node of graph with reachable nodes using graph traversal helper functions
  static void fillReachables(unordered_map<string, CityNode>& graph);


  // helps with set up for recursive DFSHelper function and transplants returned unordered_set into CityNode object
  static void buildReachables(CityNode* head, unordered_map<string, CityNode>& graph);


  // traversal function that recursively adds nodes and their children to dummyReachableNodes unordered_set 
  static unordered_set<string> DFSHelper(CityNode* nodePtr, unordered_map<string, CityNode>& graph, unordered_set<string> visited);


  // answer has to be returned as vector of CityNodes, puts nodes from hashmap into vector
  static vector<CityNode> populateAnswerVector(unordered_map<string, CityNode>& graph);


  // sorts vector of CityNodes by desired parameters before returning answer
  static void sortByReachablePaths(vector<CityNode>& cityNodes);


  // helper function to visualize graph
  static void printGraph(unordered_map<string, CityNode> graph);


  // helper function to visualize vector
  static void printVector(vector<CityNode>& cityNodes);
};

#endif