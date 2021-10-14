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

    static List merge(List* first, List* second) {
        Node* current_node_from_first = first->head->next;
        Node* current_node_from_second = second->head->next;

        List result;

        Node* last_node = result.head;

        while (current_node_from_first != nullptr || current_node_from_second != nullptr) {
            if (current_node_from_first != nullptr && current_node_from_second == nullptr) {
                last_node = (last_node->next = current_node_from_first);
                current_node_from_first = current_node_from_first->next;
            } else if (current_node_from_first == nullptr && current_node_from_second != nullptr) {
                last_node = (last_node->next = current_node_from_second);
                current_node_from_second = current_node_from_second->next;
            } else {
                if (current_node_from_first->data <= current_node_from_second->data) {
                    last_node = (last_node->next = current_node_from_first);
                    current_node_from_first = current_node_from_first->next;
                } else {
                    last_node = (last_node->next = current_node_from_second);
                    current_node_from_second = current_node_from_second->next;
                }
            }
        }

        return result;
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

    auto merged = List::merge(&first, &second);

    List::printList(merged);

    return 0;
}
