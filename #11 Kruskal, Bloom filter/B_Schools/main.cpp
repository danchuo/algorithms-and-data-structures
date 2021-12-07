#include <iostream>
#include <string>

template <typename T>
class MyStack {
public:
    MyStack();
    ~MyStack();

    void push(T elem);

    T pop();

    int getSize();

private:
    int top_;

    int size_;

    T *arr_;
};

template <typename T>
MyStack<T>::MyStack() {
    top_ = -1;
    size_ = 10;
    arr_ = new T[size_];
}

template <typename T>
T MyStack<T>::pop() {
    T popped = arr_[top_];
    --top_;

    return popped;
}

template <typename T>
void MyStack<T>::push(T elem) {
    if (top_ + 1 >= size_) {
        size_ *= 2;
        int *new_arr = new int[size_];

        for (int i = 0; i < size_ / 2; ++i) {
            new_arr[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = new_arr;
    }

    ++top_;
    arr_[top_] = elem;
}

template <typename T>
int MyStack<T>::getSize() {
    return top_ + 1;
}

template <typename T>
MyStack<T>::~MyStack() {
    delete[] arr_;
}

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

int64_t calculateWeightAndAllUsedConnections(Connection **connections, const int number_of_nodes,
                                             const int number_of_edges,
                                             MyStack<int> *used_connections) {
    SNMInt *nodes = new SNMInt(number_of_nodes);
    int64_t answer = 0;

    for (int i = 0; i < number_of_edges; ++i) {
        Connection *current_connection = connections[i];
        if (nodes->find(current_connection->first_node) !=
            nodes->find(current_connection->second_node)) {
            used_connections->push(i);
            nodes->unite(current_connection->first_node, current_connection->second_node);
            answer += current_connection->edge_weight;
        }
    }

    delete nodes;
    return answer;
}

int64_t calculateWeightWithoutOneConnection(Connection **connections, const int number_of_nodes,
                                            const int number_of_edges,
                                            const int not_counted_element = -1) {
    SNMInt *nodes = new SNMInt(number_of_nodes);
    int64_t answer = 0;

    for (int i = 0; i < number_of_edges; ++i) {
        if (i == not_counted_element) {
            continue;
        }

        Connection *current_connection = connections[i];
        if (nodes->find(current_connection->first_node) !=
            nodes->find(current_connection->second_node)) {
            nodes->unite(current_connection->first_node, current_connection->second_node);
            answer += current_connection->edge_weight;
        }
    }

    delete nodes;
    return answer;
}

Connection **readConnections(const int number_of_edges) {
    Connection **connections = new Connection *[number_of_edges];
    int first_node;
    int second_node;
    int edge_weight;

    for (int i = 0; i < number_of_edges; ++i) {
        std::cin >> first_node >> second_node >> edge_weight;
        connections[i] = new Connection(first_node - 1, second_node - 1, edge_weight);
    }

    quickSort(connections, 0, number_of_edges - 1);

    return connections;
}

std::string findWeightsOfTheMinimumSpanningTree(const int number_of_nodes,
                                                const int number_of_edges) {
    Connection **connections = readConnections(number_of_edges);

    MyStack<int> *used_connections = new MyStack<int>();

    int64_t minimal = calculateWeightAndAllUsedConnections(connections, number_of_nodes,
                                                           number_of_edges, used_connections);
    int64_t second_minimal = INT64_MAX;

    int size_of_stack = used_connections->getSize();

    for (int index = 0; index < size_of_stack; ++index) {
        int current_index = used_connections->pop();
        int64_t result = calculateWeightWithoutOneConnection(connections, number_of_nodes,
                                                             number_of_edges, current_index);
        if (result < second_minimal) {
            if (result > minimal) {
                second_minimal = result;
            } else {
                if (result == minimal) {
                    second_minimal = result;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < number_of_edges; ++i) {
        delete connections[i];
    }
    delete[] connections;
    delete used_connections;

    return std::to_string(minimal) + " " + std::to_string(second_minimal);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_nodes;
    int number_of_edges;

    std::cin >> number_of_nodes >> number_of_edges;
    std::cout << findWeightsOfTheMinimumSpanningTree(number_of_nodes, number_of_edges);

    return 0;
}
