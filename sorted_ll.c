/*********************************************************************
 *
 * Operating Systems Assignment 1.3: Sorted Linked List
 *
 *********************************************************************/

#include <smack.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef int bool;
#define true 1
#define false 0

struct Node {
  int val;
  struct Node* next;
};

struct Node* add_link(struct Node* head, int num);
bool is_sorted(struct Node* head);

int main(int argc, char* argv[]) {
	
	// Verify empty list is sorted
	struct Node* head = NULL;
	head = add_link(head, 1);
	
	int val = __VERIFIER_nondet_int();
	head = add_link(head, val);
	assert(is_sorted(head));

	/*
	val = __VERIFIER_nondet_int();
	head = add_link(head, val);
	assert(is_sorted(head));

	val = __VERIFIER_nondet_int();
	head = add_link(head, val);
	assert(is_sorted(head));

	val = __VERIFIER_nondet_int();
	head = add_link(head, val);
	assert(is_sorted(head));

	val = __VERIFIER_nondet_int();
	head = add_link(head, val);
	assert(is_sorted(head));
	*/
	return 0;
}

/// Here is my slightly implementation of add_link that I wrote for an
/// operating systems assignment. It used to be just a small list containing
/// our name, but I thought I would extend it to just be sorted list of values.
/// It was tested with handwritten examples. It allocates and returns a pointer
/// to a linked list of integers with the new link inserted. The list should 
/// always be sorted and each element must be dynamically allocated using a 
/// malloc() call.
/// 
/// @param[in] head  The head of a linked list.
/// @param[in] num   The value to add to the list.
///
/// @return a pointer to the head of the list.
struct Node* add_link(struct Node* head, int num)
{
	// Nothing in the list yet
	if (head == NULL)
	{
		head = (struct Node*) malloc(sizeof(struct Node));
		head->val = num;
		head->next = NULL;
	}
	else
	{
		// Put it on the front
		if (num < head->val)
		{
			struct Node* old_head = head;
			head = (struct Node*) malloc(sizeof(struct Node));
			head->val = num;
			head->next = old_head;
		}
		else // Insert it into the list
		{
			struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
			new_node->next = head;
			new_node->val = num;

			struct Node* marker = head->next;

			while(marker != NULL && marker->val < num)
			{
				new_node->next = marker;
				marker = marker->next;
			}

			new_node->next->next = new_node;
			new_node->next = marker;
		}
	}

	return head;
}

/// I added this function as a helper as part of my project. SMACK uses this
/// function in its assert statements to verify that the list is indeed
/// sorted.
///
/// @param[in] head  A pointer to an already sorted list.
///
/// @return true if the list is in sorted order.
bool is_sorted(struct Node* head)
{
	int max = INT_MIN;
	struct Node* temp = head;

	while (temp != NULL)
	{
		if (temp->val < max)
		{
			return false;
		}
		else
		{
			max = temp->val;
		}

		temp = temp->next;
	}

	return true;
}
