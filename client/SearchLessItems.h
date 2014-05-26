/*
 * SearchLessItems.h
 *
 *  Created on: 13/05/2014
 *      Author: arthurhortmannerpen
 */

#ifndef SEARCHLESSITEMS_H_
#define SEARCHLESSITEMS_H_

#include "SearchBehavior.h"
#include "../CircularList.h"

class SearchLessItems: public SearchBehavior {
public:
	SearchBehavior *copy() const;
	Cashier &search(CircularList<Cashier> &cashiers) const;
};

#endif /* SEARCHLESSITEMS_H_ */
