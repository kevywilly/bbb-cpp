#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include "../robotcape.hpp"
#include "motor.hpp"


class Drivetrain {


private:
    Motor motor1;
    Motor motor2;

public:
    // Constructor
	Drivetrain(short ch1, short ch2) : motor1(ch1), motor2(ch2) {}
	
	// Deconstructor
    virtual ~Drivetrain() {
        rc_disable_motors();
    }
};


#endif /* DRIVETRAIN_H_ */
