//
// Created by wysocki on 24/07/2017.
//

#ifndef STATEK_ITICKABLE_H
#define STATEK_ITICKABLE_H


class ITickable {
public:
	ITickable();
	virtual ~ITickable();
	
	virtual void Tick(float delta) = 0;
};


#endif //STATEK_ITICKABLE_H
