#ifndef C_VERSION_STAR_H
#define C_VERSION_STAR_H

class Star {
    public:
        Star(const int);
        double GetFunctionValue() { return functionValue; }
        void SetFunctionValue(double value) { functionValue = value; }
        double* GetPosition() { return  position; }
        double GetPosition(int i) { return  position[i]; }
        void SetPosition(double* new_pos) { delete [] position; position = new_pos; }
        void SetPosition(int i, double value) { position[i]=value; }

    private:
        double* position;
        double functionValue;
};

#endif //C_VERSION_STAR_H
