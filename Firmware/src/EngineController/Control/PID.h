#pragma once
#include "Integrator.h"
#include <cstdint>

// First Order Discrete PID

template<typename T>
class PID{

    public:

    PID(){};

    T Pid(float Kp, T Ki, float Kd, uint32_t dt, T input, T previnput, T setpoint){

        // Error term
        T currErr = setpoint - input;
        T prevErr = setpoint - previnput;
        
        // Proportional term
        T P = Kp * m_err;

        // Integral term
        Integrator<T>().integrate(m_err, dt);
        T I = Ki * Integrator<T>().getI();   

        // Derivative term
        T D = Kd * (currErr - prevErr) / dt;

        T output = P + I + D;  

        return output;

    }

    private:

    T m_err;
    T m_output;
    


};