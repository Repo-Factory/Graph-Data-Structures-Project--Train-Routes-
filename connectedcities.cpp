#include "connectedcities.h"

/**
 * 
 * Single Programmer Affidavit
 * I the undersigned promise that the submitted assignment is my own work. While I was 
 * free to discuss ideas with others, the work contained is my own. I recognize that 
 * should this not be the case; I will be subject to penalties as outlined in the course 
 * syllabus. 
 * Name: Conner Sommerfield
 * Red ID: 824769654
 * 
 *
 * Given a list of cities, and a list of one-way train routes from one city to another:
 *
 * ---------------------------------------------------------------------------------------
 * @param  cities  a list of cities with each city identified by a two letter code
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
 * @return       A list of CityNode in the descending order based on the number of their 
 *               reachable cities following the train routes
 
* @see         
*/


// parent function executed with steps from helper functions
vector<CityNode> ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain
(
    vector<string> cities, 
    vector<pair<string, string>> trainRoutes                     
)                    

{   
    // make a hashmap with structure string: CityNode
    unordered_map<string, CityNode> graph = ConnectedCities::createGraphSkeleton(cities);

    // fill each CityNode directRoute vector using trainRoute city pairs
    ConnectedCities::fillAdjacents(trainRoutes, graph);
    
    // fill each CityNode reachables (calls buildReachables and DFSHelper helper functions)
    ConnectedCities::fillReachables(graph);

    // place nodes from hashmap into a vector
    vector<CityNode> answer = ConnectedCities::populateAnswerVector(graph);

    // sort vector by size of CityNode reachables and then by alphabetical order
    ConnectedCities::sortByReachablePaths(answer);

    return answer; 
}
 

/* constructs and returns hashmap skeleton - graph will look like the following
 * LA: CityNode(LA)
 * SD: CityNode(SD)
 * SF: CityNode(SF)
*/
unordered_map<string, CityNode> ConnectedCities::createGraphSkeleton(vector<string>& cities) {
    unordered_map<string, CityNode> graph;
    for (string city : cities) {
        CityNode node(city); // call constructor for each city node to insert into graph 
        graph.insert({city, node}); // string is key, CityNode object is value
    }
    return graph; // use this graph throughout program
}


// given all trainRoute pairs, populate directRoute vectors of each node
void ConnectedCities::fillAdjacents(vector<pair<string, string>>& trainRoutes, unordered_map<string, CityNode>& graph) {
    
    // trainRoute looks like {SD, LA}, this means for node SD in our map, we need to add LA as directRoute
    
    for (pair<string, string> trainRoute : trainRoutes) { // apply above process to each trainRoute
        CityNode* nodePtr = &graph.at(trainRoute.first); // use first string of pair to get pointer to node from graph
        nodePtr->addADirectRoutedCity(trainRoute.second); // add the second string to that node's directRoutes
    }
}


// helper to call buildReachables on each node
void ConnectedCities::fillReachables(unordered_map<string, CityNode>& graph) {
    
    // row will be each entry in our graph, LA: CityNode(LA) <- grab CityNode at row.second at call buildReachables
    for (auto &row : graph) {
        CityNode* nodePtr = &row.second;
        ConnectedCities::buildReachables(nodePtr, graph);
    }
}


// recursive DFSHelper function will populate only the unordered_set reachableDummies member of class, 
// buildReachables will move answers to vector after recursive calls are complete
void ConnectedCities::buildReachables(CityNode* nodePtr, unordered_map<string, CityNode>& graph) {
    unordered_set<string> visited; // will be passed to DFSHelper

    unordered_set<string> dummyset = ConnectedCities::DFSHelper(nodePtr, graph, visited);
    nodePtr->setMemo(true); // if a route is explicitly found, its value is valid

    for (string dummy : dummyset) {      // answer from DFSHelper given as unordered_set, but the answer needs
        nodePtr->addReachableCity(dummy); // to be a vector, so we must copy the values over
    }
}


/* Recursive function to fill unordered dummyset with reachable nodes
 *
 * Think of this edge case to understand memo boolean
 * 
 * 
 * HT ------> NH  -------> could be anything
 * ^           |
 * |           |
 * SF <--------
 * 
 * 
 * DFSHelper naturally memoizes itself, meaning that if a node already has values in reachableCities, it just
 * returns that value. However if we look at the case above we have an infinite loop. If we call this function
 * on NH, it will recurse down to SF and HT and have to stop at NH to not get stuck in the loop. However,
 * SF and HT will populate themselves along the way meaning they will have incomplete reachableCities vectors
 * because we don't know what is beyond NH. We will reach a point where HT realizes its in a loop because it 
 * won't add NH to its reachableCities list, but it will have NH as a child. Because the node is missing info
 * it has to send a message (the memo boolean) to not memoize to the other nodes that were called before it 
 *  to make sure their values aren't retrieved from memoization
 * 
 * 
 * In a graph without a loop, like SF --> HT --> NH, memo will never become false because each node with children
 * will add those children to its reachableCities vector, so there will be no node with children but only one
 * reachableCity (remember it always adds itself)
 * 
 */ 
unordered_set<string> ConnectedCities::DFSHelper(CityNode* nodePtr, unordered_map<string, CityNode>& graph, unordered_set<string> visited) {

    visited.insert(nodePtr->getCity()); // prevent infinite loop

    if (nodePtr->getReachableDummies().size() != 0 && nodePtr->getMemo() == true) { // memoized base case, don't find answer to subproblem if already found
        return nodePtr->getReachableDummies(); // if memo is false, memoized value is incomplete and not useable
    }

    nodePtr->addReachableDummy(nodePtr->getCity()); // add current node to its own reachables

    // then for each adjacent node (child), get its reachables and add them to current nodes reachables
    // this is an implicit base case because eventually a child will have no children
    // meaning the loop will be skipped and the program will continue
    for (string child : nodePtr->getDirectRoutedCities()) {  // for each adjacent node
        if (visited.count(graph.at(child).getCity()) == 0) { // if it has not been seen
            unordered_set<string> childReachables = ConnectedCities::DFSHelper(&graph.at(child), graph, visited); // get its reachables
            for (string childReachable : childReachables) { // for each of those reachables
                nodePtr->addReachableDummy(childReachable); // add it to the current node's reachables
            }
        }
        else {
           nodePtr->setMemo(false); // base case to not memoize is when node recognizes it's in infinite loop
        }                           // set memoize to false if a node sees a node it has already seen
    }

    // if any children have memo as false, they have unreliable information, meaning the current node's 
    //information is unreliable and its memo value must also be set to false
    for (string child : nodePtr->getDirectRoutedCities()) {
        if (graph.at(child).getMemo() == false) {
            nodePtr->setMemo(false);
        }
    }

    return nodePtr->getReachableDummies();
}


// all our information is sitting in our hashmap, but we need to put those CityNodes into a vector to return as our answer
vector<CityNode> ConnectedCities::populateAnswerVector(unordered_map<string, CityNode>& graph) {
     vector<CityNode> answer;

     // for each CityNode in graph, place in answer vector
     for (auto &row : graph) { 
        CityNode* nodePtr = &row.second; // row.second refers to each node of graph
        answer.push_back(*nodePtr); // use pointer so you don't just insert a copied node with no info
    }
    return answer;
}


// sort CityNodes by size of their reachableCities vectors and then by alphabetical order
void ConnectedCities::sortByReachablePaths(vector<CityNode>& cityNodes) {
    std::sort
    (
        cityNodes.begin(), 
        cityNodes.end(), 
        [](CityNode& a, CityNode& b)
        { 
            int size1 = a.getReachableCities().size(); // store number of reachable cities for each node
            int size2 = b.getReachableCities().size();

            if ( size1 == size2 )                  // if same number of reachable cities
                {return a.getCity() < b.getCity();} // sort by the city name aphabetically
            else 
                {return size1 > size2;} // else sort by size of reachableCities
        }
    );
}


// We can visualize each row of the graph as:
//          nodeString: [adjacents] [reachables]
void ConnectedCities::printGraph(unordered_map<string, CityNode> graph) {
    for (auto const& row : graph) {  // row is a pair in the graph with row.first as keys (node strings) and row.second as values (node Objects)
        CityNode node = row.second; // get each node object of graph 
        
        std::string adjacents = ""; 
        std::string reachables = "";

        for (string adjacent : node.getDirectRoutedCities()) { // build string of adjacents by using each entry in the directRoutes vector
            adjacents += adjacent + " ";
        }
        for (string reachable : node.getReachableCities()) { // build string of reachables by using each entry in the reachableCities vector
            reachables += reachable + " ";
        }

        std::cout << row.first << ": " << "adjacents: [" << adjacents << "] reachables: [" << reachables << "] " << std::endl;
    }
}

// helper function to visualize answer vector
void ConnectedCities::printVector(vector<CityNode>& cityNodes) {
    for (CityNode node : cityNodes) {
        cout << node.getCity() << " | ";
    }
}







