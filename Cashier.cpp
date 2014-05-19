/*
 * Cashier.cpp
 *
 *  Created on: 09/05/2014
 *      Author: arthurhortmannerpen
 */

#include "Cashier.h"
#include "Client.h"
#include "ProcessBehavior.h"
#include <deque>
#include <string>
#include <iostream>

class ProcessBehavior;


Cashier::Cashier(std::string id, double salary, const ProcessBehavior &processBehavior, int timeOfArrival, bool overTime):
        _id(id),
        _salary(salary),
        _queue(std::deque<Client>()),
        _totalWaitingTime(),
        _clientsServed(),
        _totalIncome(),
        _numOfItems(),
        _processBehavior(processBehavior.copy()),
        _timeOfArrival(timeOfArrival),
		_overTime(overTime)
		{}

Cashier::Cashier(const Cashier& other) :
        _id(other._id),
        _salary(other._salary),
        _queue(std::deque<Client>(other._queue)),
        _totalWaitingTime(other._totalWaitingTime),
        _clientsServed(other._clientsServed),
        _totalIncome(other._totalIncome),
        _numOfItems(other._numOfItems),
        _processBehavior(other._processBehavior->copy()),
		_timeOfArrival(other._timeOfArrival),
		_overTime(other._overTime)
        {}

Cashier& Cashier::operator=(Cashier other) {
	swap(*this, other);
	return *this;
	}

void swap(Cashier& first, Cashier& second) {
	using std::swap;
	swap(first._clientsServed, second._clientsServed);
	swap(first._id, second._id);
	swap(first._processBehavior, second._processBehavior);
	swap(first._queue, second._queue);
	swap(first._salary, second._salary);
	swap(first._totalIncome, second._totalIncome);
	swap(first._numOfItems, second._numOfItems);
	swap(first._totalWaitingTime, second._totalWaitingTime);
	swap(first._timeOfArrival, second._timeOfArrival);
	swap(first._overTime, second._overTime);
}

Cashier::~Cashier() {
	delete _processBehavior;
}

void Cashier::addClient(Client &client) {
	int timeOfDeparture = _processBehavior->processTime(client);
	if (_queue.empty()) {
		timeOfDeparture += client.timeOfArrival();
	}
	else {
		timeOfDeparture += _queue.back().timeOfDeparture();
	}
	client.timeOfDeparture(timeOfDeparture);
	_numOfItems += client.cartSize();
	_queue.push_back(client);
}

void Cashier::update(int currentTime) {
	if (_queue.empty())
		return;
	const Client &firstClient = _queue.front();
	if (firstClient.timeOfDeparture() == currentTime) {
		++_clientsServed;
		_totalWaitingTime += currentTime - firstClient.timeOfArrival();
		_totalIncome += firstClient.cartValue();
		_numOfItems -= firstClient.cartSize();
		_queue.pop_front();
	}
}

double Cashier::totalIncome() const {
	return _totalIncome;
}

double Cashier::averageIncome() const {
	return _totalIncome/_clientsServed;
}

int Cashier::totalWaitingTime() const {
	return _totalWaitingTime;
}

int Cashier::clientsServed() const {
	return _clientsServed;
}

int Cashier::queueSize() const {
	return _queue.size();
}

int Cashier::numOfItems() const {
	return _numOfItems;
}

std::string Cashier::id() const {
	return _id;
}

double Cashier::salary() const {
	return _salary;
}

int Cashier::timeOfArrival() const {
	return _timeOfArrival;
}

bool Cashier::overTime() const {
	return _overTime;
}
