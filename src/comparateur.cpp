#include "lib.hpp"
#include "const.hpp"

double difference(double samples[SAMPLES])
{
    double squaredx = 0.0;
    double squaredy = 0.0;
    double xy = 0.0;
    for(byte i = 0 ; i < SAMPLES; i++)
    {
        squaredx += pow(samples[i],2);
        squaredy += pow(nombre1[i],2);
        xy += samples[i]*nombre1[i];
    }
    return (xy/sqrt(squaredx*squaredy));
}