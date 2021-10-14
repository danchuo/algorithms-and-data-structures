#include <iostream>
#include <string>

class Node {
public:
    Node *next;
    int data;

    explicit Node(int data);
    ~Node();
};

Node::Node(int data) {
    this->data = data;
    next = nullptr;
}

Node::~Node() {
    delete next;
}

class List {
public:
    Node *head;

    static List createFilledList(int length) {
        List list;
        Node *current_node = list.head;
        int input_number;

        for (int i = 0; i < length; ++i) {
            std::cin >> input_number;
            current_node->next = new Node(input_number);
            current_node = current_node->next;
        }

        return list;
    }

    List();
    ~List();

    void insert(int value, int position);
    void remove(int position);
    void printList();
};

List::List() {
    head = new Node(0);
}

List::~List() {
    delete head;
}

void List::printList() {
    Node *previous = head;

    while (previous->next != nullptr) {
        int output = ((previous->next)->data);
        std::cout << output << ' ';
        previous = previous->next;
    }
}

void List::insert(int value, int position) {
    Node *insert_node = new Node(value);
    Node *current = head;

    for (int i = 0; i <= position; ++i) {
        current = current->next;
    }

    if (current->next == nullptr) {
        current->next = insert_node;
    } else {
        insert_node->next = current->next;
        current->next = insert_node;
    }
}

void List::remove(int position) {
    Node *current = head;

    for (int i = 0; i <= position; ++i) {
        current = current->next;
    }

    Node *node_to_delete = current->next;

    current->next = node_to_delete->next;

    node_to_delete->next = nullptr;
    delete node_to_delete;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int length_of_list;
    int number_of_commands;

    std::cin >> length_of_list >> number_of_commands;

    auto list = List::createFilledList(length_of_list);

    std::string command;
    std::getline(std::cin, command);
    int first_number;
    int second_number;

    for (int i = 0; i < number_of_commands; ++i) {
        std::getline(std::cin, command);
        first_number = std::stoi(command.substr(7));

        if (command[0] == 'r') {
            list.remove(first_number);
        } else {
            second_number = std::stoi(command.substr(command.find_last_of(' ') + 1));
            list.insert(first_number, second_number);
        }
    }

    list.printList();

    return 0;
}
