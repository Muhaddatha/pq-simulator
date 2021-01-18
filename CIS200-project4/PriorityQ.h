#pragma once
#include "Job.h"
/*
Author Muhaddatha Abdulghani
Creation date: 4/11/19
Modification date: 4/21/19
File: PriorityQ.h
Purpose: The purpose of this file is to contain the implementation of the
priority Q class
*/
struct node {
	job Job = { '.', 0, 0, 0, 0 };
	node* next = nullptr;
};
class priorityQ {
private:
	node* head;
	int length;
	node* DJobFinder;
	node* DJobFinderPrev;
public:
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: An on=bject of the class priorityQ is created
	description: This method is a default constructor for the class
	priority Q
	*/
	priorityQ() {
		head = nullptr;
		length = 0;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: none
	description: This method enters a job in the queue
	*/
	void enqueue(job inputJob) {
		//jobNum++;
		node* temp = new node;
		temp->Job = inputJob;
		/*
		//insert at the front of queue if job is of d type
		if (temp->Job.jobType == 'D') {
		temp->next = head;
		head = temp;
		temp = nullptr;
		length++;
		return;
		}
		*/
		if (isEmpty()) {
			head = temp;
			temp = nullptr;
			length++;
			return;
		}
		node* curPtr = head;
		node* prevPtr = nullptr;
		while (curPtr != nullptr && curPtr->Job.arrivalTime <=
			temp->Job.arrivalTime) {
			prevPtr = curPtr;
			curPtr = curPtr->next;
		}
		//insert at beginning
		if (curPtr == head) {
			temp->next = head;
			head = temp;
		}
		//insert at end
		else if (curPtr == nullptr) {
			prevPtr->next = temp;
		}
		//insert at middle
		else {
			temp->next = curPtr;
			prevPtr->next = temp;
		}
		prevPtr = nullptr;
		temp = nullptr;
		curPtr = nullptr;
		length++;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition:
	postcondition:
	description:
	void print() {
	//if head is empty
	node* temp = head;
	while (temp != nullptr) {
	std::cout << temp->Job.jobType << " " <<
	temp->Job.arrivalTime << " "<< temp->Job.processingTime << std::endl;
	if (debugging) {
	std::cout << temp->Job.jobNumber << " "
	<< temp->Job.jobTypeNumber << std::endl;
	std::cout <<
	"****************************" << std::endl;
	}
	temp = temp->next;
	}
	temp = nullptr;
	}
	*/
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: return of a job
	description: This method removes a job from the queue to be
	processed
	*/
	job dequeue() {
		node* temp = head;
		if (head == nullptr) {
			if (debugging) {
				std::cout << "dequeue function - Head is nullptr" << std::endl;
			}
			job Blank = { 'E', 0, 0, 0 };
			return Blank;
		}
		head = head->next;
		job jobLeavingQueue = temp->Job;
		temp = nullptr;
		return jobLeavingQueue;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: none
	description: This method is a destructor for the PriorityQ class
	*/
	~priorityQ() {
		node* temp = head;
		while (temp != nullptr) {
			head = head->next;
			delete temp;
			temp = head;
		}
		temp = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: A low priority jo is interrupted
	postcondition: none
	description: This method puts a low priority job back into the queue
	as a result of being interrpted by a high priority job
	*/
	void putBackInQueue(job interruptedJob) {
		node* temp = new node;
		temp->Job = interruptedJob;
		temp->next = head->next;
		if (head != nullptr) {
			head->next = temp;
		}
		length++;
		temp = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: return of an integer
	description: This method returns the size of the queue
	*/
	int getQueueSize() {
		return length;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: queue is not empty
	postcondition: retun of a job info
	description: This function returns the information of the first job
	in the queue
	*/
	job peek() {
		if (!isEmpty()) {
			return head->Job;
		}
		std::cout << "Peek-function : Queue is empty." <<
			std::endl;
		job blank = { 'E', 0, 0, 0 , 0 };
		return blank;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: return of job info
	description: This method returns the information related to when the
	next high priority job will arrive
	*/
	job peekNextDJob() {
		DJobFinder = head;
		while (DJobFinder != nullptr) {
			if (DJobFinder->Job.jobType == 'D') {
				return DJobFinder->Job;
			}
			DJobFinderPrev = DJobFinder;
			DJobFinder = DJobFinder->next;
		}
		job emptyDJob = { 'E', -1, 0, 0 };
		return emptyDJob;
	}
	/**
	job extractDJob() {
	//extract from beginning
	if (DJobFinder == head) {
	head = head->next;
	job targetDJob = DJobFinder->Job;
	DJobFinder = nullptr;
	length--;
	delete DJobFinder;
	return targetDJob;
	}
	//extract from middle
	else if (DJobFinder->next != nullptr) {
	DJobFinderPrev->next = DJobFinder->next;
	DJobFinder->next = nullptr;
	job targetDJob = DJobFinder->Job;
	DJobFinder = nullptr;
	length--;
	delete DJobFinder;
	return targetDJob;
	}
	//extract from end
	else if (DJobFinder->next == nullptr) {
	DJobFinderPrev->next = nullptr;
	job targetDJob = DJobFinder->Job;
	DJobFinder = nullptr;
	length--;
	delete DJobFinder;
	return targetDJob;
	}
	else if (DJobFinder == nullptr) {
	job Blank = { 'E', 0, 0 };
	return Blank;
	}
	}
	*/
	/*
	Author: Muhaddatha Abdulghani
	precondition: A D job's arrival time matches the universal time
	postcondition: none
	description: This method moves the D job that just arrived to the
	front of the queue
	*/
	void moveHighPriorityToFront() {
		if (DJobFinder == head) {
			if (debugging) {
				std::cout << "High Priority is already at the front" << std::endl;
			}
			return;
		}
		else if (DJobFinder != nullptr) {
			DJobFinderPrev->next = DJobFinder->next;
			DJobFinder->next = head;
			head = DJobFinder;
		}
		return;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: the queue is not empty
	postcondition: return of a boolean value
	description: This function checks to see if the queue is empty
	*/
	bool isEmpty() {
		if (head == nullptr)
			return true;
		return false;
	}
};
