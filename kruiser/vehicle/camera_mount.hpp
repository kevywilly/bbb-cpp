#ifndef CAMERA_MOUNT_HPP_
#define CAMERA_MOUNT_HPP_

#include "../robotcape/robotcape.hpp"
#include <iostream>

namespace ServoStatus {
	typedef enum Status{
		DISABLED,
		NORMAL,
		FREE
	} Status;

}

class CameraMount {

public:
    // Constructor
	CameraMount(short ch1, short ch2) : servo1(ch1), servo2(ch2) {
	    pulse1 = 0;
	    pulse2 = 0;
	    if(rc_get_state() == RUNNING)
	        disable();
	    status = ServoStatus::DISABLED;
	}
	
	void send_pulses() {
		rc_send_servo_pulse_normalized(servo1, pulse1);
		rc_send_servo_pulse_normalized(servo2, pulse2);
	}
	void enable() {
	    rc_enable_servo_power_rail();
	    status = ServoStatus::NORMAL;
	}
	
	void disable() {
	    rc_disable_servo_power_rail();
	    status = ServoStatus::DISABLED;
	}
	
	ServoStatus::Status get_state() {
	    return status;
	}
	
	void look(float yaw, float pitch) {
        
        pulse1 = angle_to_pulse(yaw);
        pulse2 = angle_to_pulse(pitch);
	    
	    status = ServoStatus::NORMAL;
	}
	
	void free_spin() {
	    disable();
    }
    
	// Deconstructor
    virtual ~CameraMount() {
        disable();
    }
    
    
private:
    short servo1, servo2;
    float pulse1, pulse2;
    
    ServoStatus::Status status;
    
    float angle_to_pulse(float angle) {
        float a = angle;
        if(a < -90.0)
            a = -90.0;
        if(a > 90.0)
            a = 90.0;
            
        return angle*1.5/90.0;
    }
    
    float pulse_to_angle(float pulse) {
        return pulse * 90.0/1.5;
    }
    
};


#endif /* CAMERA_MOUNT_HPP_ */