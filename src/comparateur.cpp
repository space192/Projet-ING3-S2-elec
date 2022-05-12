#include "lib.hpp"
#include "Gaussian.hpp"
#include "const.hpp"
/*double difference(double samples[SAMPLES])
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
}*/

byte manahattanDistance(Gaussian *g)
{
    double Ltemp[K] = {0.0,0.0,0.0};
    double min = 1000;
    byte index;
    for(byte i = 0 ; i < 2 ;i++)
    {
        for(byte j = 0 ; j < K; j++)
        {
            Ltemp[i] += abs(g[j].getu() - Arthur[i][j].getu()) + abs(g[j].getsigma() - Arthur[i][j].getsigma());
        }
    }
    for(byte i = 0 ; i < 2 ; i++)
    {
        Serial.println(Ltemp[i]);
        if(Ltemp[i] < min)
        {
            min = Ltemp[i];
            index = i;
        }
    }
    Serial.println(min);
    Serial.println(index);
    if(min < 15)
    {
        return index+1;
    }
    else
    {
        return -1;
    }
}


double resultU = 0.0;
double resultsigma = 0.0;
double sumGaussian = 0.0;
int count = 0;
double tempG;
void findMaximums(double *t, uint8_t *tab2, int k)
{
    double *tempValue = (double *)malloc(sizeof(double) * k);
    double max = -2000.0;
    uint8_t index = -1;
    for (byte i = 0; i < k; i++)
    {
        index = -1;
        max = -20000;
        for (byte j = 0; j < SAMPLES / 2; j++)
        {
            if (t[j+2] > max)
            {
                max = t[j+2];
                index = j+2;
            }
        }
        tab2[i] = index;
        tempValue[i] = t[index];
        t[index] = -2000;
    }
    for (byte i = 0; i < k; i++)
    {
        t[tab2[i]] = tempValue[i];
    }
    free(tempValue);
}

double GaussianCalculus(Gaussian gauss, double x)
{
    return (double)(gauss.getWeight() * ((1 / (sqrt(2.0 * PI * gauss.getsigma()))) * exp(-0.5 * pow((x - gauss.getu()), 2) / gauss.getsigma())));
}

double TGaussianCalculus(Gaussian gaussT[], Gaussian gauss, double x)
{
    double numerator = GaussianCalculus(gauss, x);
    double denominator = 0.0;
    for (byte i = 0; i < K; i++)
    {
        denominator += GaussianCalculus(gaussT[i], x);
    }
    return numerator / denominator;
}

void GMM_ALGORITHM(double tab[SAMPLES], Gaussian Gresult[K])
{
    uint8_t *tab2 = (uint8_t *)malloc(sizeof(uint8_t) * K);
    findMaximums(tab, tab2, K);
    double result = 0.0;
    Gaussian tabG[K];
    for (byte i = 0; i < K; i++)
    {
        tabG[i].setu((double)tab2[i]);
        tabG[i].setsigma(10.0);
        tabG[i].setweight((double)(1.0 / K));
    }
    resultU = 0.0;
    resultsigma = 0.0;
    sumGaussian = 0.0;
    count = 0;
    for(byte l = 0 ; l < 2;l++)
    {
        result = 0.0;
        tempG = 0.0;
        for (byte i = 0; i < SAMPLES / 2; i++)
        {
            for (byte j = 0; j < K; j++)
            {
                result += sqrt(tab[i+2]) * TGaussianCalculus(tabG, tabG[j], i+2) * (log(tabG[j].getWeight()) - 0.5 * log(tabG[j].getsigma()) - 0.5 * (pow(i+2 - tabG[j].getu(), 2) / tabG[j].getsigma()) - 0.5 * log(2 * PI));
            }
        }
        for (byte j = 0; j < K; j++)
        {
            resultsigma = 0.0;
            resultU = 0.0;
            sumGaussian = 0.0;
            count = 0;
            for (byte i = 0; i < SAMPLES / 2; i++)
            {
                tempG = sqrt(tab[i+2]) * TGaussianCalculus(tabG, tabG[j], i+2);
                sumGaussian += tempG;
                resultU += tempG * i+2;
                resultsigma += tempG * pow((i+2 - tabG[j].getu()), 2);
                count += sqrt(tab[i+2]);
            }
            tabG[j].setu(resultU / sumGaussian);
            tabG[j].setweight(sumGaussian / count);
            tabG[j].setsigma(resultsigma / sumGaussian);
        }
    }
    for (byte i = 0; i < K; i++)
    {
        Gresult[i].setu(tabG[i].getu());
        Gresult[i].setsigma(tabG[i].getsigma());
        Gresult[i].setweight(tabG[i].getWeight());
    }
    free(tab2);
}