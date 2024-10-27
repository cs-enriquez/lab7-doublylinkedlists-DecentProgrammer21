	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node *front = new Node(s);
		if(numStudents == 0){
			head = front;
			tail = front;
		}else{
			front->next = head;
			head->prev = front;
			head = front;
		}
		numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
			Node *back = new Node(s);
	if(numStudents == 0){
		head = back;
		tail = back;
	}else{
		back->prev = tail;
		tail->next = back;
		tail = back;
	}
	numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node *travel = head;
		while(travel != nullptr){
		cout << travel->data.name << endl;
		travel = travel->next;
		}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(tail == nullptr){
		cout << "Tail is empty! Cannot perform action." << endl;
		return;
		}
		Node *back = tail;
		if(head == tail){
			head = nullptr;
			tail = nullptr;
		}else{
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete back;
		numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
	if(head == nullptr){
		cout << "Head is empty! Cannot perform action." << endl;
		return;
		}
	Node *front = head;
	if(head == tail){
		head = nullptr;
		tail = nullptr;
	}else{
		head = head->next;
		head->prev = nullptr;
	}
	delete front;
	numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if(index < 0 || index > numStudents){
			cout << "Out of bounds" << endl;
			return;
		}else if(index == 0){
			addFront(s);
			return;
		}else if(index == numStudents - 1){
			addBack(s);
			return;
		}
		Node *newNode = new Node(s);
		Node *temp = head;
		for(int i = 0; i < index-1; i++){
			temp = temp->next;
		}
		newNode->next = temp->next; //Links nw node to next node
		if(temp->next != nullptr){ 
			temp->next->prev = newNode; //Links next node back to new node
		}
		temp->next = newNode;
		newNode->prev = temp; //Linking newnode and temp
		
		numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Node *current = head;
		while(current != nullptr){
			if(current->data.id == idNum){
				return current->data;	
			}
			current = current->next;
		}
		cout << "Student ID not found" << endl;
		Student dummystudent;
		return dummystudent;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node *current = head;
		while(current != nullptr && current->data.id != idNum){
			current = current->next;
		}
		if(current == nullptr){
			cout << "No student found" << endl;
			return;
		}
		if(current == head){
			popFront();
		}
		if(current ==  tail){
			popBack();
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		numStudents--;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node *current = head;
		while(current != nullptr && current->data.id != idNum){
			current = current->next;
		}
		if(current == nullptr){
			cout << "No student found" << endl;
			return;
		}else{
			current->data.GPA = newGPA;
		}
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if(otherList.head == nullptr){
			cout << "List is empty! Cannot perform this action" << endl;
			return;
		}
		if(head == nullptr){
			head = otherList.head;
			tail = otherList.tail;
		}else{
			tail->next = otherList.head;
			otherList.head->prev = tail;
			tail = otherList.tail;
		}
		numStudents+=otherList.numStudents;
		otherList.head = nullptr;
		otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honorList;
		Node *travel = head;
		while(travel != nullptr){
		if(travel->data.GPA >= minGPA){
			honorList.addBack(travel->data);
		}
		travel = travel->next;
		}
		return honorList;
	}
