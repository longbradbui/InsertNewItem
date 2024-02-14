#include "doubly_linked.h"
#include <iostream>

List::List()
{
    head_ptr_ = nullptr;
    tail_ptr_ = nullptr;
}

List::List(const List &parent_list)
{
    this->head_ptr_ = nullptr;
    *(this) = parent_list;
}

List::~List()
{
    Node *current = head_ptr_;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    // Reset head_ptr_ and tail_ptr_ to nullptr
    head_ptr_ = nullptr;
    tail_ptr_ = nullptr;
    cout << "~ Destructor is called ~" << endl;
}

bool List::InsertItem(int value)
{
    // Empty list
    if (head_ptr_ == nullptr)
    {
        // If the list is empty, create a new node and make it both head and tail
        Node *insert_node = new Node;
        insert_node->data = value;
        insert_node->next = nullptr;
        insert_node->previous = nullptr; // No previous node since it's the first node
        head_ptr_ = insert_node;
        tail_ptr_ = insert_node; // Update tail_ptr_ as well
        return true;
    }
    // If value equals the first element
    if (head_ptr_->data == value)
    {
        cerr << "Duplicate with first item" << endl;
        return false;
    }
    // First in line
    if (head_ptr_->data > value)
    {
        Node *insert_node = new Node;
        insert_node->data = value;
        insert_node->next = head_ptr_;
        insert_node->previous = nullptr;
        head_ptr_->previous = insert_node;
        head_ptr_ = insert_node;
        return true;
    }
    // All others
    Node *current_node = head_ptr_;
    while ((current_node->next != nullptr) && (current_node->next->data < value))
    {
        current_node = current_node->next;
    }
    // Check for duplicates
    if ((current_node->next != nullptr) && (current_node->next->data == value))
    {
        cerr << "Duplicate value found" << endl;
        return false;
    }
    // Create new node and insert
    Node *insert_node = new Node;
    insert_node->data = value;
    insert_node->next = current_node->next;
    insert_node->previous = current_node;
    // Insert somewhere in between
    if (current_node->next != nullptr)
    {
        current_node->next->previous = insert_node;
    }
    // Insert at the end
    else
    {
        tail_ptr_ = insert_node; // Update tail_ptr_ if inserting at the end
    }
    current_node->next = insert_node;
    return true;
}

bool List::RemoveItem(int value)
{
    // Empty list
    if (head_ptr_ == nullptr)
    {
        return false;
    }
    // First in line
    if ((head_ptr_->data == value) && (head_ptr_->next != nullptr))
    {
        Node *temp = head_ptr_;
        head_ptr_ = head_ptr_->next;
        head_ptr_->previous = nullptr;
        delete temp;
        temp = nullptr;
        return true;
    }
    // All others
    else
    {
        Node *current_node = head_ptr_;
        while ((current_node->next != nullptr) && (current_node->next->data < value))
        {
            current_node = current_node->next;
        }
        // Value is not in the list
        if (current_node->next == nullptr)
        {
            return false;
        }
        // Not found any match
        if (current_node->next->data > value)
        {
            return false;
        }
        // Somewhere in between
        Node *temp = current_node->next;
        current_node->next = current_node->next->next;
        delete temp;
        return true;
    }
}

bool List::Push(int value)
{
    // List is empty, create a new node and make it the head node
    if (head_ptr_ == nullptr)
    {
        Node *insert_node = new Node;
        insert_node->data = value;
        insert_node->next = nullptr;     // Point to nullptr since this is the only node
        insert_node->previous = nullptr; // Previous is nullptr for the first node
        head_ptr_ = insert_node;         // Update head_ptr_ to point to this new node
        tail_ptr_ = insert_node;         // Update tail_ptr_ to point to this new node
        return true;
    }
    // List is full, create a new node and push to the top
    else if ((head_ptr_ != nullptr) && (head_ptr_->data) > value)
    {
        Node *insert_node = new Node;
        insert_node->data = value;
        insert_node->next = head_ptr_;
        insert_node->previous = nullptr;   // Previous for the new head node should be nullptr
        head_ptr_->previous = insert_node; // Update the previous pointer of the old head node
        head_ptr_ = insert_node;           // Update head_ptr_ to point to the new node
        return true;
    }
    cerr << "Push [" << value << "] was not successful" << endl;
    return false; 
}

bool List::Pop()
{
    if (head_ptr_ == nullptr)
    {
        return false;
    } 
    Node* temp = head_ptr_;
    head_ptr_ = head_ptr_->next;
    delete temp;
    return false;
}

List &List::operator=(const List &parent_list)
{
    // If the parent list is empty or the two list have the same address
    if (this == &parent_list || parent_list.head_ptr_ == nullptr)
    {
        return *this;
    }
    // Emptying the child list
    int a;
    while(this->RemoveItem(a)){}
    // Performing Deep Copy
    Node* source;
    Node* destination;
    destination = new Node;
    destination->data = parent_list.head_ptr_->data;
    this->head_ptr_ = destination;
    source = parent_list.head_ptr_->next;
    while (source != nullptr)
    {
        destination->next = new Node();    // Construct first
        destination = destination->next;   // Then move over
        destination->data = source->data;  // Then assign value
        source = source->next;             // Then move source forward until null
    }
    return *this;
}

ostream &operator<<(ostream &stream, const List &rhs)
{
    Node *iterator = rhs.head_ptr_;
    while (iterator != nullptr)
    {
        stream << iterator->data << " || ";
        iterator = iterator->next;
    }
    return stream;
}
