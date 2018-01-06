#ifndef MOTOR_H_
#define MOTOR_H_

#include "../robotcape/robotcape.hpp"
typedef enum m_mode_t{
	DISABLED,
	NORMAL,
	BRAKE,
	FREE
} m_mode_t;


class Drivetrain {

private:
    short m1, m2;
    float speed_, angle_;
    m_mode_t state;

public:
    // Constructor
	Drivetrain(short ch1, short ch2) : m1(ch1), m2(ch2) {
	    if(rc_get_state() == RUNNING)
	        disable();
	    state = DISABLED;
	}
	
	void enable() {
	    rc_enable_motors();
	    state = NORMAL;
	}
	
	void disable() {
	    rc_disable_motors();
	    state = DISABLED;
	}
	
	m_mode_t get_state() {
	    return state;
	}
	
	void drive(float speed, float angle) {
        
        float d1,d2;
        d1=0;d2=0;
        
        // If zeros, then free spin
        if(speed == 0.0 && angle == 0.0) {
            free_spin();
            return;
        }
        
        speed_ = speed;
        angle_ = angle;
        
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
        
	    if(state == DISABLED)
	        enable();
	    
	    rc_set_motor(m1, d1);
	    rc_set_motor(m2, d2);
	    
	    state = NORMAL;
	}
	
	void free_spin() {
	    speed_ = angle_ = 0;
        rc_set_motor_free_spin_all();
        state = FREE;
    }
    
	// Deconstructor
    virtual ~Drivetrain() {
        disable();
    }
};


#endif