#include <iostream>

struct Connection {
    int first_node;
    int second_node;
    int edge_weight;

    Connection(int first_node, int second_node, int edge_weight) {
        this->first_node = first_node;
        this->second_node = second_node;
        this->edge_weight = edge_weight;
    }
};

void mySwap(Connection **a, Connection **b) {
    Connection *t = *a;
    *a = *b;
    *b = t;
}

int partition(Connection **connections, int low, int high) {
    Connection *pivot = connections[high];
    int index = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (connections[j]->edge_weight < pivot->edge_weight) {
            index++;
            mySwap(&connections[index], &connections[j]);
        }
    }
    mySwap(&connections[index + 1], &connections[high]);
    return (index + 1);
}

void quickSort(Connection **connections, int low, int high) {
    if (low < high) {
        int pivot = partition(connections, low, high);

        quickSort(connections, low, pivot - 1);
        quickSort(connections, pivot + 1, high);
    }
}

class SNMInt {
public:
    explicit SNMInt(int number) {
        number_ = number;
        sets_ = new int[number_];
        for (int i = 0; i < number_; ++i) {
            sets_[i] = i;
        }
    }

    ~SNMInt() {
        delete[] sets_;
    }

    int find(int input_set) {
        if (sets_[input_set] == input_set) {
            return input_set;
        }
        return sets_[input_set] = find(sets_[input_set]);
    }

    void unite(int first, int second) {
        first = find(first);
        second = find(second);
        if (first != second) {
            sets_[second] = first;
        }
    }

private:
    int *sets_;
    int number_;
};

int64_t calculateTheWeightOfTheMinimumSpanningTree(SNMInt *nodes, Connection **connections,
                                                   const int number_of_edges) {
    int64_t answer = 0;

    for (int i = 0; i < number_of_edges; ++i) {
        Connection *current_connection = connections[i];
        if (nodes->find(current_connection->first_node) !=
            nodes->find(current_connection->second_node)) {
            nodes->unite(current_connection->first_node, current_connection->second_node);
            answer += current_connection->edge_weight;
        }
    }

    delete nodes;
    for (int i = 0; i < number_of_edges; ++i) {
        delete connections[i];
    }

    delete[] connections;
    return answer;
}

int64_t findTheWeightOfTheMinimumSpanningTree(const int number_of_nodes,
                                              const int number_of_edges) {
    SNMInt *nodes = new SNMInt(number_of_nodes);
    Connection **connections = new Connection *[number_of_edges];

    int first_node;
    int second_node;
    int edge_weight;

    for (int i = 0; i < number_of_edges; ++i) {
        std::cin >> first_node >> second_node >> edge_weight;
        connections[i] = new Connection(first_node - 1, second_node - 1, edge_weight);
    }

    quickSort(connections, 0, number_of_edges - 1);

    return calculateTheWeightOfTheMinimumSpanningTree(nodes, connections, number_of_edges);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_nodes;
    int number_of_edges;

    std::cin >> number_of_nodes >> number_of_edges;
    std::cout << findTheWeightOfTheMinimumSpanningTree(number_of_nodes, number_of_edges);

    return 0;
}
