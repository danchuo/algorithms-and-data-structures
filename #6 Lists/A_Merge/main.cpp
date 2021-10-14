#include <iostream>

class Node {
public:
    Node* next;
    int data;

    Node(int data);
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
    Node* head;

    static List createFilledList(int length) {
        List list;
        Node* current_node = list.head;
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

    static void printList(List const& list) {
        Node* previous = list.head;

        while (previous->next != nullptr) {
            int output = ((previous->next)->data);
            std::cout << output << ' ';
            previous = previous->next;
        }
    }
};

List::List() {
    head = new Node(0);
}

List::~List() {
    delete head;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int length_of_first_list;
    int length_of_second_list;

    std::cin >> length_of_first_list >> length_of_second_list;

    auto first = List::createFilledList(length_of_first_list);
    auto second = List::createFilledList(length_of_second_list);

    std::cout << '\n';
    List::printList(first);
    std::cout << '\n';
    List::printList(second);

    return 0;
}
