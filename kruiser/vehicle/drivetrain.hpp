#ifndef MOTOR_H_
#define MOTOR_H_

#include "../robotcape/robotcape.hpp"
typedef enum m_mode_t{
	DISABLED,
	NORMAL,
	BRAKE,
	FREE
} m_mode_t;

class Motor {
public:
    short ch_;
    float speed_;
    m_mode_t m_mode_;
    
    
    Motor(short channel) {
        ch_ = channel;
        speed_ = 0.0;
        m_mode_ = DISABLED;
    }

    bool is_disabled() {
        return (m_mode_ == DISABLED);
    }
    
    bool is_free() {
        return (m_mode_ == FREE);
    }
    
    float get_speed() {
        return speed_;
    } 
    
    void set_speed(float speed) {
        m_mode_ = NORMAL;
        if(speed < -1)
            speed_ = -1;
        else if(speed > 1)
            speed_= 1;
        else
            speed_ = speed;
        
        rc_enable_motors(); 
	    rc_set_led(GREEN,ON);
	    rc_set_led(RED,ON);
	    rc_set_motor(ch_, speed_);
    }
    
    void brake() {
        m_mode_ = BRAKE;
        rc_set_motor_brake(ch_);
    }
    
    void free_spin() {
        m_mode_ = FREE;
        rc_set_motor_free_spin(ch_);
    }
    
};

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