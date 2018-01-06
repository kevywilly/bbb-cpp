#ifndef ROBOTCAPE_HPP_
#define ROBOTCAPE_HPP_


extern "C" {
    int rc_initialize();
    int rc_cleanup();
    void rc_enable_motors();
    void rc_disable_motors();
}

#endif /* ROBOTCAPE_HPP_ */