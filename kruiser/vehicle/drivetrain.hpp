#ifndef MOTOR_H_
#define MOTOR_H_

#include "../robotcape/robotcape.hpp"


namespace MotorStatus {
typedef enum Status{
	DISABLED,
	NORMAL,
	BRAKE,
	FREE
} Status;
}

class Drivetrain {

private:
    short m1, m2;
    float speed_, turn_;

    MotorStatus::Status m_status;

public:
    // Constructor
	Drivetrain(short ch1, short ch2) : m1(ch1), m2(ch2) {
	    if(rc_get_state() == RUNNING)
	        disable();
	    m_status = MotorStatus::DISABLED;
	}
	
	void enable() {
	    rc_enable_motors();
	    m_status = MotorStatus::NORMAL;
	}
	
	void disable() {
	    rc_disable_motors();
	    m_status = MotorStatus::DISABLED;
	}
	
	MotorStatus::Status get_status() {
	    return m_status;
	}
	
	void drive(float speed, float turn) {
        
        speed_ = speed;
        turn_ = turn;
        
        if(speed == 0 && turn == 0) {
            free_spin();
            return;
        }
        
        /*
        // If zeros, then free spin
        if(speed == 0.0 && angle == 0.0) {
            free_spin();
            return;
        }
        
        speed_ = speed;
        angle_ = angle;
        
        if angle
        if(angle == 0 || angle == 360) {
            d1 = speed;
            d2 = 0.0;
        } else if(angle <= 90) {
            d1 = speed;
            d2 = (angle/90.0);
        } else if(angle <= 180) {
            d1 = -speed;
            d2 = 1.0-(angle-90)/90.0;
        } else if(angle < 270) {
            d1 = -speed;
            d2 = -(1.0-(angle-180)/90.0);
        } else if(angle < 360) {
            d1 = speed;
            d2 = -(1.0-(angle-270)/90.0);
        }
        */
        
	    if(m_status == MotorStatus::DISABLED)
	        enable();
	    
	    rc_set_motor(m1, speed_);
	    rc_set_motor(m2, turn_);
	    
	    m_status = MotorStatus::NORMAL;
	}
	
	void free_spin() {
	    speed_ = turn_ = 0.0;
        rc_set_motor_free_spin_all();
        m_status = MotorStatus::FREE;
    }
    
	// Deconstructor
    virtual ~Drivetrain() {
        disable();
    }
};


#endif