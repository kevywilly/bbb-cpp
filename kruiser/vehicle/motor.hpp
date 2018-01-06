#ifndef MOTOR_H_
#define MOTOR_H_

#include "rc_usefulincludes.h"
#include "roboticscape.h"

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



#endif