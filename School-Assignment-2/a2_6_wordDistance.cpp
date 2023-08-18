// a2_6_wordDistance
// Dallas Hart
//
// Finds a path between two words using the words in 5-words.txt

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

#define WORDSIZE 5

// Structure to store a vertex's data
struct vertex
{
    std::size_t identifier = 0;
    std::vector<std::size_t> connected = {};
    std::size_t distance = -1;
    std::size_t previous = -1;
};

// Returns true if the words are one character apart
bool compare(const std::string &word, const std::string &word2)
{
    std::size_t matching = 0;
    for (std::size_t i = 0; i < WORDSIZE; i++)
    {
        matching += word[i] != word2[i];
    }
    return matching == 1;
}

// Comparison function for priority queue
struct vertexDistComp
{
    inline bool operator()(const vertex &a, const vertex &b)
    {
        return a.distance > b.distance;
    }
};

// Had to adapt the algorithm to my code - https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
std::vector<std::size_t> dijkstra(std::vector<vertex> &graph, std::size_t src, std::size_t dest)
{
    graph[src].distance = 0;
    std::priority_queue<vertex, std::vector<vertex>, vertexDistComp> Q; // Search vertexes the shortest distance away first
    Q.push(graph[src]);

    while (!Q.empty())
    {
        // Grab the vertex the shortest distance away
        vertex minDist = Q.top();
        Q.pop();

        // If the destination is found
        if (minDist.identifier == dest)
        {
            // Backtrack to get path
            std::vector<std::size_t> path;
            std::size_t current = dest;
            while (current != (std::size_t)-1)
            {
                path.push_back(current);
                current = graph[current].previous;
            }
            return path;
        }

        // Run through all connected vertexes that have not been visited yet
        for (std::size_t &vertIdentifier : minDist.connected)
        {
            std::size_t newVertDist = minDist.distance + 1;
            if (newVertDist < graph[vertIdentifier].distance)
            {
                graph[vertIdentifier].distance = newVertDist;
                graph[vertIdentifier].previous = minDist.identifier;
                Q.push(graph[vertIdentifier]);
            }
        }
    }

    return {};
}

int main()
{
    // Error checking
    std::string start;
    std::size_t startIdentifier = -1;
    do
    {
        std::cout << "Enter starting word: ";
        std::cin >> start;
    } while (start.length() != WORDSIZE);

    std::string end;
    std::size_t endIdentifier = -1;
    do
    {
        std::cout << "Enter ending word: ";
        std::cin >> end;
    } while (end.length() != WORDSIZE);

    // File being used.
    std::ifstream file("5-words.txt");

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> fileData;

        std::cout << "Reading File" << std::endl;
        // Read the file and clean the strings
        while (file.good())
        {
            file >> line;
            fileData.push_back(line);
        }
        file.close();

        // Create adjacency graph
        std::cout << "Constructing Graph " << std::endl;
        std::vector<vertex> graph;
        graph.resize(fileData.size());
        size_t inc = 0;
        for (vertex &vert : graph)
        {
            vert = {inc++, {}, (std::size_t)-1, (std::size_t)-1};
        }

        // Fill adjacency graph
        for (std::size_t j = 0; j < fileData.size(); j++)
        {
            if (fileData[j] == start)
                startIdentifier = j;
            if (fileData[j] == end)
                endIdentifier = j;
            std::cout << "\rFilling Graph: " << (float)(j + 1) / (float)fileData.size() * 100 << "%   ";
            for (std::size_t i = j + 1; i < fileData.size(); i++)
            {
                if (compare(fileData[j], fileData[i]))
                {
                    graph[j].connected.push_back(i);
                    graph[i].connected.push_back(j);
                }
            }
        }
        // Both Start and end must be located inside the graph
        if (startIdentifier != -1 && endIdentifier != -1)
        {
            // Run Dijkstra's algorithm to find the shortest path between the two points
            std::vector<std::size_t> path = dijkstra(graph, startIdentifier, endIdentifier);
            if (path.size() > 0)
            {
                std::cout << "\n\"" << start << "\" is able to traverse to \"" << end << "\" in " << path.size() - 1 << " word distance" << std::endl;
                std::cout << "Path from \"" << start << "\" to \"" << end << "\": ";

                for (std::size_t i = 1; i < path.size(); i++)
                {
                    std::cout << fileData[path[path.size() - i]] << "->";
                }
                std::cout << fileData[endIdentifier] << std::endl;
            }
            else
            {
                std::cout << '\n'
                          << start << " is not able to traverse to " << end << std::endl;
            }
        }
        else
        {
            std::cout << '\n'
                      << start << " or " << end << " does not exist in the file." << std::endl;
        }
    }
    else
    {
        std::cout << "Could not open file!";
    }
    return 0;
}

/*
******s-iMac:assignment code ******$ ./out
Enter starting word: hello
Enter ending word: there
Reading File
Constructing Graph 
Filling Graph: 100%     
"hello" is able to traverse to "there" in 17 word distance
Path from "hello" to "there": hello->cello->cells->bells->belts->beats->beaks->leaks->leaps->leapt->least->lease->cease->chase->chose->those->these->there
******s-iMac:assignment code ******$ ./out
Enter starting word: blood
Enter ending word: tears
Reading File
Constructing Graph 
Filling Graph: 100%     
"blood" is able to traverse to "tears" in 13 word distance
Path from "blood" to "tears": blood->blond->bland->gland->grand->grind->grins->gains->pains->pairs->hairs->heirs->hears->tears
******s-iMac:assignment code ******$ ./out
Enter starting word: blood
Enter ending word: blood
Reading File
Constructing Graph 
Filling Graph: 100%     
"blood" is able to traverse to "blood" in 0 word distance
Path from "blood" to "blood": blood
*/