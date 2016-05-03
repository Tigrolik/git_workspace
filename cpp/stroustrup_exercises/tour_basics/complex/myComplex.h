#ifndef _MYCOMPLEX_H_
#define _MYCOMPLEX_H_

class myComplex {

    private:
        double re, im;

    public:
        myComplex(double = 0.0, double = 0.0);

        double real() const;
        double imag() const;
        void real(const double);
        void imag(const double);
        double norm();

        myComplex& operator+=(myComplex);
        myComplex& operator-=(myComplex);
        myComplex& operator*=(myComplex);
        myComplex& operator/=(myComplex);

};

#endif
