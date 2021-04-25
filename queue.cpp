#include <iostream>
#include <vector>

#include "queue.h"

using namespace std;

int Queue::size(){
	return size_;
}

Queue::Queue(){
	vector<Person> queue_;
	size_ = 0;
}

vector<Person> Queue::queue(){
	return queue_;
}

void Queue::push(const Person client){
	queue_.push_back(client);
	size_++;
}

void Queue::pop(){
	queue_.erase(queue_.begin());
	size_--;
}

void Queue::switch_places(int index1, int index2){
	Person temp = queue_.at(index1);
	queue_.at(index1) = queue_.at(index2);
	queue_.at(index2) = temp;
}

Person Queue::operator[](const int& id){
	return queue_[id];
}

bool Queue::operator==(const Queue& queue){
	if(queue.size_ != size_){
		return false;
	}
	for(int i = 0; i < size_ - 1; i++){
		if(queue_[i] != queue.queue_[i]){
			return false;
		}
	}
	return true;
}

bool Queue::operator!=(const Queue& queue){
	return !(*this == queue);
}

Queue Queue::operator+(const Queue& queue){
	Queue new_queue;
	for(auto elem: queue_){
		new_queue.push(elem);
	}
	for(auto elem: queue.queue_){
		new_queue.push(elem);
	}
	new_queue.size_ = size_ + queue.size_;
	return new_queue;
}

Queue& Queue::operator+=(const Queue& queue){
	this->queue_.reserve(queue.queue_.size());
	for (auto elem: queue.queue_){
		this->push(elem);
	}
	this->size_ += queue.size_;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Queue& queue){
	for(int i = 0; i < queue.queue_.size(); i++){
		os << queue.queue_.at(i) << endl;
	}
	return os;
}
