#pragma once
#include <iostream>
#include <vector>

#include "person.h"

class Queue{
private:
	int size_;
	std::vector<Person> queue_;
public:
	Queue();
	int size();
	std::vector<Person> queue();
	void push(const Person client);
	void pop();
	void switch_places(int index1, int index2);
	Queue operator+(const Queue& queue);
	Queue& operator+=(const Queue& queue);
	bool operator==(const Queue& queue);
	bool operator!=(const Queue& queue);
	Person operator[](const int& id);
	friend std::ostream& operator<<(std::ostream& os, const Queue& queue);
};
