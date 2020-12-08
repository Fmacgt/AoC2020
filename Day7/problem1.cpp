
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>


int tryAddColor(std::string color, std::unordered_map<std::string, int>& nodeIndexMap, 
        std::vector<std::unordered_map<int, int>>& graph);

void invertGraph(const std::vector<std::unordered_map<int, int>> graph, 
        std::vector<std::vector<int>>& invertedGraph);

void findContainerCount(int nodeIdx, const std::vector<std::vector<int>> graph, std::set<int>& occurrenceMap);

const std::string SHINY_GOLD = "shiny gold";


// <colorA> " bags contain " {<Ni> " " <color_i> " bag, "}* <Nn> " " <color_n> " bag."

// 1. read and parse input -> different colored bags
// 2. construct a containing graph for (bag, N contained bags)
// 3. construct an inverted containing graph for (contained bag, bag)
// 4. DFS the Dag from the node of shiny gold bag, count unrepeated nodes
int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    std::unordered_map<std::string, int> nodeIndexMap;
    std::vector<std::unordered_map<int, int>> containingGraph;
    std::vector<std::vector<int>> invertedGraph;

    std::string line;
    while (getline(fin, line)) {
        size_t colorAIndex = line.find("bags");
        std::string colorA = line.substr(0, colorAIndex - 1);
        int indexA = tryAddColor(colorA, nodeIndexMap, containingGraph);
        std::cout << "[" << colorA << "]: " << indexA << std::endl;

        size_t lineSize = line.size();
        size_t ptr = line.find("contain") + 8;
        while (ptr != std::string::npos) {
            size_t numberEnd = line.find(' ', ptr);
            size_t numberLength = numberEnd - ptr;
            std::string numberString = line.substr(ptr, numberLength);
            if (numberString == "no") {
                std::cout << "\tN/A" << std::endl;
                break;
            }
            int number = stoi(line.substr(ptr, numberLength));

            ptr += numberLength + 1;
            size_t colorEnd = line.find("bag", ptr);
            size_t colorLength = colorEnd - ptr - 1;
            std::string color = line.substr(ptr, colorLength);
            int nodeIndex = tryAddColor(color, nodeIndexMap, containingGraph);
            std::cout << "\t" << number << " '" << color << ": " << nodeIndex << std::endl;

            containingGraph[indexA].emplace(nodeIndex, number);

            size_t commaIndex = line.find(',', ptr);
            if (commaIndex != std::string::npos) {
                ptr = commaIndex + 2;
            } else {
                ptr = std::string::npos;
            }
        }
    }

    fin.close();

    invertGraph(containingGraph, invertedGraph);

    std::set<int> occurrenceMap;
    int startIndex = nodeIndexMap[SHINY_GOLD];
    findContainerCount(startIndex, invertedGraph, occurrenceMap);
    std::cout << occurrenceMap.size() << std::endl;

    return 0;
}

int tryAddColor(std::string color, std::unordered_map<std::string, int>& nodeIndexMap, 
        std::vector<std::unordered_map<int, int>>& graph)
{
    auto iter = nodeIndexMap.find(color);
    if (iter == nodeIndexMap.end()) {
        int nodeIndex = graph.size();
        nodeIndexMap.emplace(color, nodeIndex);

        // create edge list
        std::unordered_map<int, int> adjList;
        graph.push_back(adjList);

        return nodeIndex;
    }

    return iter->second;
}

void invertGraph(const std::vector<std::unordered_map<int, int>> graph, 
        std::vector<std::vector<int>>& invertedGraph)
{
    int nodeCount = graph.size();
    for (int i = 0; i < nodeCount; i++) {
        invertedGraph.push_back(std::vector<int>());
    }

    for (int toIdx = 0; toIdx < nodeCount; toIdx++) {
        auto adjList = graph[toIdx];
        auto iter = adjList.begin();
        while (iter != adjList.end()) {
            int fromIdx = iter->first;
            std::cout << "(" << fromIdx << ", " << toIdx << ")" << std::endl;
            invertedGraph[fromIdx].push_back(toIdx);

            iter++;
        }
    }
}

void findContainerCount(int nodeIdx, const std::vector<std::vector<int>> graph, std::set<int>& occurrenceMap)
{
    for (const int& nextIdx : graph[nodeIdx]) {
        if (occurrenceMap.count(nextIdx) == 0) {
            occurrenceMap.emplace(nextIdx);
            findContainerCount(nextIdx, graph, occurrenceMap);
        }
    }
}
