/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Fall 2022
 * @author Conner Sommerfield
 * @date Nov 2022
 */

#include "connectedcities.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}


/* Construct and test various graph setups
*  Follow console output commands to understand test cases
*  comments ommited after first graph to avoid clutter, all test processes  
*  follow the same pattern as the one used on Graph One
*
*  To show more organized output, the individual functions of citiesSortedByNumOf_Its_ReachableCities_byTrain
*  are tested individually instead of testing the whole parent function all at once.
*/
int main(int argc, char **argv) {
       
    std::cout << endl << endl << endl << "Building Graph One - Driver Graph" << endl << "_______________________________________________________" << endl << endl;
    
    /* 
        *    SD ---> DL <--------         
        *    ^                   |
        *    |                   |
        *    OD <--- JL <--------|--
        *                        |  |
        *    BV <---             |  |
        *    --->  LA ---> BU    |  |
        *          ^             |  |
        *          |             |  |
        *  SJ ---> SK ---> IV ---|  |
        *                           |
        *  <---------------         |
        *  SF ---> HT ---> NH ------|
        * */

    vector<string> cities_1 {"SD", "LA", "SK", "IV", "JL", "SF", 
                             "DL", "HT", "OD", "NH", "BV", "SJ", "BU"}; // Graph vertices constructed with given city strings

    vector<pair<string, string>> trainRoutes; // trainRoute indicates there is a direct edge from the city on the left to the city on the right

    trainRoutes.emplace_back("JL", "OD");
    trainRoutes.emplace_back("OD", "SD");
    trainRoutes.emplace_back("SD", "DL");
    trainRoutes.emplace_back("BV", "LA");
    trainRoutes.emplace_back("LA", "BV");
    trainRoutes.emplace_back("LA", "BU");
    trainRoutes.emplace_back("SK", "IV");
    trainRoutes.emplace_back("SK", "LA");
    trainRoutes.emplace_back("SJ", "SK");

    trainRoutes.emplace_back("IV", "DL");
    
    trainRoutes.emplace_back("SF", "HT");
    trainRoutes.emplace_back("HT", "NH");
    trainRoutes.emplace_back("NH", "SF");
    trainRoutes.emplace_back("NH", "JL"); 


    // build hashmap with format nodeString : CityNode
    unordered_map<string, CityNode> graph = ConnectedCities::createGraphSkeleton(cities_1);

    // fill each CityNode directRoute vector (adjacency list) using trainRoute city pairs
    ConnectedCities::fillAdjacents(trainRoutes, graph);
    
    // fill each CityNode reachables (calls buildReachables and DFSHelper helper functions)
    ConnectedCities::fillReachables(graph);

    // view graph for visual
    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    vector<CityNode> answer = ConnectedCities::populateAnswerVector(graph); // place CityNodes from hashmap to vector

    ConnectedCities::sortByReachablePaths(answer); // sort vector before printing

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer); // visualize vector of city nodes

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    vector<CityNode> cities = answer; // set cities vector as answer before asserts

    //cities returned from the above call are sorted according to 
    //the ascending order of the city names and 
    //the descending order of the size of reachableCities starting from those cities
    
    asserts(cities.at(0).getCity() == "HT", "First city should be HT");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(cities.at(0).getReachableCities().size() == 7, "Train starting from city HT can reach 7 cities"); 
    
    std::cout << endl;

    asserts(cities.at(1).getCity() == "NH", "Second city should be NH");
    //Reachable cities from NH are [NH, SF, HT, JL, OD, SD, DL]
    asserts(cities.at(1).getReachableCities().size() == 7, "Train starting from city NH can reach 7 cities");
    
    std::cout << endl;

    asserts(cities.at(2).getCity() == "SF", "Third city should be SF");
    //Reachable cities from SF are [SF, HT, NH, JL, OD, SD, DL]
    asserts(cities.at(2).getReachableCities().size() == 7, "Train starting from city SF can reach 7 cities");
    
    std::cout << endl;

    asserts(cities.at(3).getCity() == "SJ", "Fourth city should be SJ");
    //Reachable cities from SJ are [SJ, SK, IV, DL, LA, BV, BU]
    asserts(cities.at(3).getReachableCities().size() == 7, "Train starting from city SJ can reach 7 cities");

    std::cout << endl;

    asserts(cities.at(4).getCity() == "SK", "Fifth city should be SK");
    //Reachable cities from SK are [SK, IV, DL, LA, BV, BU]
    asserts(cities.at(4).getReachableCities().size() == 6, "Train starting from city SK can reach 6 cities");
    
    std::cout << endl;

    asserts(cities.at(5).getCity() == "JL", "Sixth city should be JL");
    //Reachable cities from JL are [JL, OD, SD, DL]
    asserts(cities.at(5).getReachableCities().size() == 4, "Train starting from city JL can reach 4 cities");
    
    std::cout << endl;
    
    asserts(cities.at(6).getCity() == "BV", "Seventh city should be BV");
    //Reachable cities from BV are [BV, LA, BU]
    asserts(cities.at(6).getReachableCities().size() == 3, "Train starting from city BV can reach 3 cities");
        
    std::cout << endl;

    asserts(cities.at(7).getCity() == "LA", "Eighth city should be LA");
    //Reachable cities from LA are [LA, BV, BU]
    asserts(cities.at(7).getReachableCities().size() == 3, "Train starting from city LA can reach 3 cities");

    std::cout << endl;

    asserts(cities.at(8).getCity() == "OD", "Ninth city should be OD");
    //Reachable cities from OD are [OD, SD, DL]
    asserts(cities.at(8).getReachableCities().size() == 3, "Train starting from city OD can reach 3 cities");

    std::cout << endl;

    asserts(cities.at(11).getCity() == "BU", "Twelfth city should be BU");
    //Reachable cities from BU are [BU]
    asserts(cities.at(11).getReachableCities().size() == 1, "Train starting from city BU can reach 1 city");

    







    std::cout << endl << endl << endl << "Building Graph Two - Empty Graph" << endl << "_______________________________________________________" << endl << endl;
    

    vector<string> cities_2 {};

    vector<pair<string, string>> trainRoutes_2;


    graph = ConnectedCities::createGraphSkeleton(cities_2);

    ConnectedCities::fillAdjacents(trainRoutes_2, graph);
    
    ConnectedCities::fillReachables(graph);

    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    answer = ConnectedCities::populateAnswerVector(graph);

    ConnectedCities::sortByReachablePaths(answer);

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer);

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    cities = answer;

    asserts(cities.size() == 0, "cities vector should be empty");









 std::cout << endl << endl << endl << "Building Graph Three - One Node Graph" << endl << "_______________________________________________________" << endl << endl;
    

    vector<string> cities_3 {"CA"};

    vector<pair<string, string>> trainRoutes_3;


    graph = ConnectedCities::createGraphSkeleton(cities_3);

    ConnectedCities::fillAdjacents(trainRoutes_3, graph);
    
    ConnectedCities::fillReachables(graph);

    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    answer = ConnectedCities::populateAnswerVector(graph);

    ConnectedCities::sortByReachablePaths(answer);

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer);

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    cities = answer;

    asserts(cities.size() == 1, "cities vector should have 1 item");
    asserts(cities[0].getDirectRoutedCities().size() == 0, "should have no adjacent nodes");
    asserts(cities[0].getReachableCities().size() == 1, "should have 1 reachable node (itself)");








std::cout << endl << endl << endl << "Building Graph Four - Two Node Graph No Loop" << endl << "_______________________________________________________" << endl << endl;
    

    vector<string> cities_4 {"SD", "LA"};

    vector<pair<string, string>> trainRoutes_4;
    trainRoutes_4.emplace_back("SD", "LA");

    graph = ConnectedCities::createGraphSkeleton(cities_4);

    ConnectedCities::fillAdjacents(trainRoutes_4, graph);
    
    ConnectedCities::fillReachables(graph);

    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    answer = ConnectedCities::populateAnswerVector(graph);

    ConnectedCities::sortByReachablePaths(answer);

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer);

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    cities = answer;

    asserts(cities[0].getCity() == "SD", "SD should have one more reachable than LA because of sole train route SD, LA");
    asserts(cities[0].getReachableCities().size() == 2, "SD can reach both itself and LA");

    asserts(cities[1].getCity() == "LA", "LA can only reach itself because no train route connects it to anything");
    asserts(cities[1].getReachableCities().size() == 1, "LA can't reach SD due to directional edge");








std::cout << endl << endl << endl << "Building Graph Five - Two Node Loop Graph" << endl << "_______________________________________________________" << endl << endl;
    

    vector<string> cities_5 {"SD", "LA"};

    vector<pair<string, string>> trainRoutes_5;
    trainRoutes_5.emplace_back("SD", "LA");
    trainRoutes_5.emplace_back("LA", "SD");

    graph = ConnectedCities::createGraphSkeleton(cities_5);

    ConnectedCities::fillAdjacents(trainRoutes_5, graph);

    ConnectedCities::fillReachables(graph);

    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    answer = ConnectedCities::populateAnswerVector(graph);

    ConnectedCities::sortByReachablePaths(answer);

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer);

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    cities = answer;

    asserts(cities[0].getCity() == "LA", "alphabetical order dictates LA comes first");
    asserts(cities[0].getReachableCities().size() == 2, "Both nodes should reach themselves and the other node once");

    asserts(cities[1].getCity() == "SD", "alphabetical order dictates SD comes second");
    asserts(cities[1].getReachableCities().size() == 2, "Both nodes should reach themselves and the other node once");









std::cout << endl << endl << endl << "Building Graph Six - Extensive Graph" << endl << "_______________________________________________________" << endl << endl;



/* Extensive Graph
 *   
 *               ------ DW
 *               |      ^
 *               v      |
 *              FL ---> CA <- BA -> VA <- DA <- HA <- HM -> DL -> PA
 *               ^             ^
 *               |             |
 *               |             |
 *      BL ----> AL  ------- > UT < -- KL
 *      ^         |            |
 *      |         v            v
 *      GA <---- BW            KA <- DN
 * 
 * 
 * 
 *  AL - [AL, FL, CA, DW, UT, BA, VA, KA, BW, GA, DL] 11
 *  BW - [AL, FL, CA, DW, UT, BA, VA, KA, BW, GA, DL] 11
 *  BL - [AL, FL, CA, DW, UT, BA, VA, KA, BW, GA, DL] 11
 *  GA - [AL, FL, CA, DW, UT, BA, VA, KA, BW, GA, DL] 11
 *  KL - [KL, UT, BA, VA, CA, DW, FL, KA] 8
 *  UT - [UT, BA, VA, CA, DW, FL, KA] 7
 *  HM - [HM, HA, DA, VA, DL, PA] 6
 *  BA - [BA, VA, CA, DW, FL] 5
 *  CA - [CA, DW, FL] 3
 *  DW - [DW, FL, CA] 3
 *  FL - [FL, CA, DW] 3
 *  HA - [HA, DA, VA] 3
 *  DA - [DA, VA] 2
 *  DL - [DL, PA] 2
 *  DN - [DN, KA] 2
 *  KA - [KA]
 *  PA - [PA]
 *  VA - [VA]
*/

    

    vector<string> cities_6 {
                            "AL", "BW", "BL", "GA", "KL", "UT", "BA", "CA", "DW", 
                            "FL", "HA", "HM", "DA", "DL", "DN", "KA", "PA", "VA"
                            };

    vector<pair<string, string>> trainRoutes_6;
    trainRoutes_6.emplace_back("BW", "GA");
    trainRoutes_6.emplace_back("GA", "BL");
    trainRoutes_6.emplace_back("BL", "AL");
    trainRoutes_6.emplace_back("AL", "FL");
    trainRoutes_6.emplace_back("AL", "BW");
    trainRoutes_6.emplace_back("AL", "UT");
    trainRoutes_6.emplace_back("FL", "CA");
    trainRoutes_6.emplace_back("CA", "DW");
    trainRoutes_6.emplace_back("DW", "FL");
    trainRoutes_6.emplace_back("UT", "KA");
    trainRoutes_6.emplace_back("UT", "BA");
    trainRoutes_6.emplace_back("KL", "UT");
    trainRoutes_6.emplace_back("DN", "KA");
    trainRoutes_6.emplace_back("BA", "CA");
    trainRoutes_6.emplace_back("BA", "VA");
    trainRoutes_6.emplace_back("DA", "VA");
    trainRoutes_6.emplace_back("HA", "DA");
    trainRoutes_6.emplace_back("HM", "HA");
    trainRoutes_6.emplace_back("HM", "DL");
    trainRoutes_6.emplace_back("DL", "PA");


    graph = ConnectedCities::createGraphSkeleton(cities_6);

    // fill each CityNode directRoute vector using trainRoute city pairs
    ConnectedCities::fillAdjacents(trainRoutes_6, graph);
    
    // fill each CityNode reachables (calls buildReachables and DFSHelper helper functions)
    ConnectedCities::fillReachables(graph);

    // view graph for debugging
    ConnectedCities::printGraph(graph);


    std::cout << "_______________________________________________________" << endl;

    answer = ConnectedCities::populateAnswerVector(graph);

    ConnectedCities::sortByReachablePaths(answer);

    std::cout << endl << endl << "Answer Vector: ";

    ConnectedCities::printVector(answer);

    std::cout << endl << endl << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl;
   
    cities = answer;

    asserts(cities.at(0).getCity() == "AL", "First city should be AL");
    asserts(cities.at(0).getReachableCities().size() == 11, "Train starting from city AL can reach 11 cities"); 
    
    std::cout << endl;

    asserts(cities.at(1).getCity() == "BL", "First city should be BL");
    asserts(cities.at(1).getReachableCities().size() == 11, "Train starting from city BL can reach 11 cities"); 
    
    std::cout << endl;

    asserts(cities.at(2).getCity() == "BW", "First city should be BW");
    asserts(cities.at(2).getReachableCities().size() == 11, "Train starting from city BW can reach 11 cities"); 
    
    std::cout << endl;

    asserts(cities.at(3).getCity() == "GA", "First city should be GA");
    asserts(cities.at(3).getReachableCities().size() == 11, "Train starting from city GA can reach 11 cities"); 
    
    std::cout << endl;

    asserts(cities.at(4).getCity() == "KL", "First city should be KL");
    asserts(cities.at(4).getReachableCities().size() == 8, "Train starting from city KL can reach 8 cities"); 
    
    std::cout << endl;

    asserts(cities.at(5).getCity() == "UT", "First city should be UT");
    asserts(cities.at(5).getReachableCities().size() == 7, "Train starting from city UT can reach 7 cities"); 
    
    std::cout << endl;

    asserts(cities.at(6).getCity() == "HM", "First city should be HM");
    asserts(cities.at(6).getReachableCities().size() == 6, "Train starting from city HM can reach 6 cities"); 
    
    std::cout << endl;

    asserts(cities.at(7).getCity() == "BA", "First city should be BA");
    asserts(cities.at(7).getReachableCities().size() == 5, "Train starting from city BA can reach 5 cities"); 
    
    std::cout << endl;

    asserts(cities.at(8).getCity() == "CA", "First city should be CA");
    asserts(cities.at(8).getReachableCities().size() == 3, "Train starting from city CA can reach 3 cities"); 
    
    std::cout << endl;

    asserts(cities.at(9).getCity() == "DW", "First city should be DW");
    asserts(cities.at(9).getReachableCities().size() == 3, "Train starting from city DW can reach 3 cities"); 
    
    std::cout << endl;

    asserts(cities.at(10).getCity() == "FL", "First city should be FL");
    asserts(cities.at(10).getReachableCities().size() == 3, "Train starting from city FL can reach 3 cities"); 
    
    std::cout << endl;

    asserts(cities.at(11).getCity() == "HA", "First city should be HA");
    asserts(cities.at(11).getReachableCities().size() == 3, "Train starting from city HA can reach 3 cities"); 
    
    std::cout << endl;

    asserts(cities.at(12).getCity() == "DA", "First city should be DA");
    asserts(cities.at(12).getReachableCities().size() == 2, "Train starting from city DA can reach 2 cities"); 
    
    std::cout << endl;

    asserts(cities.at(13).getCity() == "DL", "First city should be DL");
    asserts(cities.at(13).getReachableCities().size() == 2, "Train starting from city DL can reach 2 cities"); 
    
    std::cout << endl;

    asserts(cities.at(14).getCity() == "DN", "First city should be DN");
    asserts(cities.at(14).getReachableCities().size() == 2, "Train starting from city DN can reach 2 cities"); 
    
    std::cout << endl;

    asserts(cities.at(15).getCity() == "KA", "First city should be KA");
    asserts(cities.at(15).getReachableCities().size() == 1, "Train starting from city KA can reach 1 cities"); 
    
    std::cout << endl;

    asserts(cities.at(16).getCity() == "PA", "First city should be PA");
    asserts(cities.at(16).getReachableCities().size() == 1, "Train starting from city PA can reach 1 cities"); 
    
    std::cout << endl;

    asserts(cities.at(17).getCity() == "VA", "First city should be VA");
    asserts(cities.at(17).getReachableCities().size() == 1, "Train starting from city VA can reach 1 cities"); 
    
    std::cout << endl;


    cout << endl << "All test cases passed!" << endl;


    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}