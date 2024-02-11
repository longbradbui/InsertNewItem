#ifndef LIST_H_
#define LIST_H_
class List
{
public: 
	struct Node
	{
		Item* pItem;
		Node* previous;
		Node* next;
	};
	List();
	~List();
	bool InsertNewItem(Item& it);
private:
	Node* head_ptr_ = nullptr;
	Node* tail_ptr_ = nullptr;
};
#endif

bool List::InsertNewItem(Item& it)
{
	Node* insert_node = new Node();
	insert_node->next = nullptr;
	insert_node->previous = nullptr;
	insert_node->pItem = &(it); // get the value
	if (head_ptr_ == nullptr)
	{
		head_ptr_ = insert_node;
		insert_node->previous = head_ptr_;
		insert_node->next = tail_ptr_;
		return true;
	}
	if (*(head_ptr_->pItem) == it)
	{
		delete insert_node;
		insert_node = nullptr;
		return false;
	}
	if (*(head_ptr_->pItem) > it)
	{
		insert_node->next = head_ptr_;
		head_ptr_ = insert_node;
		return true;
	}
	if (*(tail_ptr_->pItem) < it)
	{
		insert_node->previous = tail_ptr_;
		tail_ptr_->next = insert_node;
		tail_ptr_ = insert_node;
		return true;
	}
	Node* current_node = head_ptr_;
	while (current_node != nullptr) 
	{
		if (*(current_node->pItem) == it)
		{
			delete insert_node;
			insert_node = nullptr;
			return false;
		}
		else if (*(current_node->pItem) < it)
		{
			current_node = current_node->next;
		} 
		else
		{
			/* assigning the previous pointer of insert_node to the same
			node that current_node is pointing to as its previous */
			insert_node->previous = current_node->previous;
			/* next pointer of insert_node is set to point to current_node, indicating 
			that current_node will be the next node in the list after insert_node. */
			insert_node->next = current_node;
			/* This line updates the next pointer of the node before current_node (i.e., current_node->previous)
			to point to insert_node, effectively linking insert_node into the list .*/
			current_node->previous->next = insert_node;
			/* the previous pointer of current_node is updated to point back to insert_node, 
			ensuring the proper bidirectional linking of nodes in the list. */
			current_node->previous = insert_node;
			return true;
		}		
	}
}
