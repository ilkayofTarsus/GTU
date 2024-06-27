#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

struct Order{
	int p;
	int q;
	int delivered;
	int orderId;
	int readyToEat;
};

struct MessageToClient{
	int orderId;
	int durum;

};

#endif
