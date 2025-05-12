#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// Graph class for room navigation
class Graph {
    map<string, vector<string>> adj;

public:
    void addEdge(const string& u, const string& v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void displayAdjacent(const string& room) {
        cout << "You can go to: ";
        for (auto& neighbor : adj[room])
            cout << neighbor << " ";
        cout << endl;
    }

    bool isConnected(const string& u, const string& v) {
        for (auto& neighbor : adj[u])
            if (neighbor == v) return true;
        return false;
    }

    void bfs(const string& start) {
        queue<string> q;
        map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        cout << "Hint - Reachable rooms from " << start << ": ";
        while (!q.empty()) {
            string room = q.front(); q.pop();
            cout << room << " ";

            for (auto& neighbor : adj[room]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

// Inventory stack using STL
class Inventory {
    stack<string> items;

public:
    void push(const string& item) {
        items.push(item);
        cout << item << " added to inventory.\n";
    }

    void pop() {
        if (!items.empty()) {
            cout << "Dropped: " << items.top() << endl;
            items.pop();
        } else {
            cout << "Inventory is empty.\n";
        }
    }

    void display() {
        if (items.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        stack<string> temp = items;
        cout << "Inventory items (top to bottom): ";
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

// Main Game class
class Game {
    Graph map;
    Inventory inventory;
    string currentRoom;

public:
    Game() {
        // Map setup
        map.addEdge("Entrance", "Hallway");
        map.addEdge("Hallway", "Library");
        map.addEdge("Hallway", "Armory");
        map.addEdge("Library", "TreasureRoom");
        currentRoom = "Entrance";
    }

    void start() {
        string command;

        cout << "===== Welcome to the Dungeon Adventure! =====\n";
        cout << "You are currently in the Entrance.\n";

        while (true) {
            cout << "\nCurrent Room: " << currentRoom << endl;
            map.displayAdjacent(currentRoom);
            cout << "Commands: go [room], pickup [item], drop, inventory, hint, exit\n> ";
            cin >> command;

            if (command == "go") {
                string dest;
                cin >> dest;
                if (map.isConnected(currentRoom, dest)) {
                    currentRoom = dest;
                    cout << "You moved to " << currentRoom << ".\n";

                    if (currentRoom == "TreasureRoom") {
                        cout << "?? You found the treasure! You win!\n";
                        break;
                    }
                } else {
                    cout << "You can't go there from here.\n";
                }
            } else if (command == "pickup") {
                string item;
                cin >> item;
                inventory.push(item);
            } else if (command == "drop") {
                inventory.pop();
            } else if (command == "inventory") {
                inventory.display();
            } else if (command == "hint") {
                map.bfs(currentRoom);
            } else if (command == "exit") {
                cout << "Thanks for playing. Goodbye!\n";
                break;
            } else {
                cout << "Invalid command.\n";
            }
        }
    }
}
int main() {
    Game game;
    game.start();
    return 0;
}
