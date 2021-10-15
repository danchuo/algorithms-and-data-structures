#include <iostream>
#include <string>

class SpecialNode {
public:
    const int kArraySize = 1000;
    SpecialNode *next;
    int number_of_elements;
    int result_of_operation;
    int *array;

    explicit SpecialNode();
    ~SpecialNode();
};

SpecialNode::SpecialNode() {
    array = new int[kArraySize];
    number_of_elements = 0;
    result_of_operation = 0;
}

SpecialNode::~SpecialNode() {
    delete[] array;
    delete next;
}

class UnrolledList {
public:
    SpecialNode *head;
    int size;

    UnrolledList();
    ~UnrolledList();
};

UnrolledList::UnrolledList() {
    size = 0;
    head = nullptr;
}

UnrolledList::~UnrolledList() {
    delete head;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int length_of_list;
    int number_of_commands;

    std::cin >> length_of_list >> number_of_commands;

    return 0;
}
