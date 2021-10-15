#include <iostream>
#include <string>

class Node {
public:
    Node *next;
    Node *previous;
    int data;

    explicit Node(int data);
    ~Node();
};

Node::Node(int data) {
    this->data = data;
    next = nullptr;
    previous = nullptr;
}

Node::~Node() {
    delete next;
}

class List {
public:
    Node *head;
    Node *tail;

    void pushBack(Node *node);
    void pushFront(Node *node);
    void insert(int value, int position);
    void remove(int position);

    static List createFilledList(int length) {
        List list;
        Node *current_node = list.head;
        Node *previous_node = nullptr;
        int input_number;

        for (int i = 0; i < length; ++i) {
            std::cin >> input_number;
            Node *new_node = new Node(input_number);
            new_node->previous = previous_node;
            current_node->next = new_node;
            previous_node = (current_node = current_node->next);
        }

        list.tail = current_node;

        return list;
    }

    List();
    ~List();

    void printListFromHead();
    void printListFromTail();
};

List::List() {
    head = new Node(0);
    tail = nullptr;
}

List::~List() {
    delete head;
}

void List::printListFromHead() {
    Node *previous = head;

    while (previous->next != nullptr) {
        std::cout << ((previous->next)->data) << ' ';
        previous = previous->next;
    }
}

void List::pushBack(Node *node) {
    if (tail == nullptr) {
        head->next = node;
        tail = node;
    } else {
        tail->next = node;
        node->previous = tail;
        tail = node;
    }
}

void List::pushFront(Node *node) {
    if (head->next == nullptr) {
        head->next = node;
        tail = node;
    } else {
        node->next = head->next;
        head->next = node;
        node->next->previous = node;
    }
}

void List::remove(int position) {
    Node *current = head;

    for (int i = 0; i <= position; ++i) {
        current = current->next;
    }

    Node *node_to_delete = current->next;

    if (node_to_delete->next != nullptr) {
        current->next = node_to_delete->next;
        node_to_delete->next->previous = current;
    } else {
        current->next = nullptr;
        tail = current;
    }

    node_to_delete->next = nullptr;
    node_to_delete->previous = nullptr;
    delete node_to_delete;
}

void List::insert(int value, int position) {
    Node *insert_node = new Node(value);
    Node *current = head;

    for (int i = 0; i <= position; ++i) {
        current = current->next;
    }

    if (current->next == nullptr) {
        current->next = insert_node;
        insert_node->previous = current;
        tail = insert_node;
    } else {
        insert_node->next = current->next;
        current->next = insert_node;
        insert_node->previous = current;
        insert_node->next->previous = insert_node;
    }
}

void List::printListFromTail() {
    Node *last = tail;

    while (last != nullptr) {
        std::cout << (last->data) << ' ';
        last = last->previous;
    }
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
        first_number = std::stoi(command.substr(command.find_first_of(' ') + 1));

        switch (command[5]) {
            case 'f': {
                list.pushFront(new Node(first_number));
                break;
            }
            case 'b': {
                list.pushBack(new Node(first_number));
                break;
            }
            case 't': {
                second_number = std::stoi(command.substr(command.find_last_of(' ') + 1));
                list.insert(first_number, second_number);
                break;
            }
            case 'e': {
                list.remove(first_number);
                break;
            }
        }
    }

    list.printListFromHead();
    std::cout << '\n';
    list.printListFromTail();

    return 0;
}
