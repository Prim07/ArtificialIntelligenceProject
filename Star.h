//
// Created by LENOVO on 2017-05-12.
//

#ifndef C_VERSION_STAR_H
#define C_VERSION_STAR_H


class Star {
public:
    Star();
    double GetFunctionValue() { return functionValue; }
    void SetFunctionValue(double value) { functionValue = value; }
    double* GetPosition() { return  position; }
    double GetPosition(int i) { return  position[i]; }
    void SetPosition(int i, double value) { position[i]=value; }
    double* position;
    double functionValue;
};

#endif //C_VERSION_STAR_H
