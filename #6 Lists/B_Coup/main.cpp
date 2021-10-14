#include <iostream>

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
    Node *last;

    void addToTheEnd(Node *node);

    static List createFilledList(int length) {
        List list;
        Node *current_node = list.head;
        int input_number;

        for (int i = 0; i < length; ++i) {
            std::cin >> input_number;
            current_node->next = new Node(input_number);
            current_node = current_node->next;
        }

        list.last = current_node;

        return list;
    }

    static List createInvertedList(List const &other) {
        List list;

        recurrentCoup(other.head->next, &list);

        return list;
    }

    List();
    ~List();

    void printList();

private:
    static void recurrentCoup(Node *original, List *inverted) {
        if (original->next != nullptr) {
            recurrentCoup(original->next, inverted);
        }

        inverted->addToTheEnd(new Node(original->data));
    }
};

List::List() {
    head = new Node(0);
    last = nullptr;
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

void List::addToTheEnd(Node *node) {
    if (last == nullptr) {
        head->next = node;
        last = node;
    } else {
        last = (last->next = node);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int length_of_list;

    std::cin >> length_of_list;

    if (length_of_list > 0) {
        List list = List::createFilledList(length_of_list);
        List inverted_list = List::createInvertedList(list);

        inverted_list.printList();
    }

    return 0;
}
