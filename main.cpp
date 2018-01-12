#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

// First create the function to calculate the price of a bond
double BondPrice(double d, double N, double r, double c, double FV)
{
    double PV = 0.;

    for (int i = 0; i <= N; i++)
    {
        PV = PV + c*pow((1+r), -(i+d)); // discounted coupon value
    }

    // accured interest needs to be subtracted from the dirty price to get the quoted price (clean price) of the bond
    PV = PV + FV*pow((1+r), -(N+d)) - c*(1-d);

    return PV;
}

// Next use the bisection method to calculate the yield to maturity of a bond
double YTM(double d, double N, double PV, double c, double FV)
{
    const int maxIteration = 1000000;
    double epsilon = 0.0000001;
    double rlower = 0.0000001;
    double rupper = 1;

    // the difference between the PV and the bond price based on the lower r value
    double rlowerDif = PV - BondPrice(d, N, rlower, c, FV);

    // the difference between the PV and the bond price based on the upper r value
    double rupperDif = PV - BondPrice(d, N, rupper, c, FV);

    double rmiddle, rmiddleDif;

    if (c == 0) // zero-coupon bond
        return pow((FV/PV), 1/(N+d)) - 1;

    else if (PV == FV) // bond price equals its par value
        return c/FV;

    else
    {

        if (rlowerDif*rupperDif > 0)
            return -1;
        else
            for (int i = 0;i <= maxIteration; i++)
            {
                rmiddle = (rlower + rupper) / 2.0;
                rmiddleDif = PV - BondPrice(d, N, rmiddle, c, FV);
                if (abs(rmiddleDif) < epsilon)
                    goto Lastline;
                else
                {
                    if (rmiddleDif > 0)
                        rupper = rmiddle;
                    else
                        rlower = rmiddle;
                }
            }
        Lastline:
        return rmiddle;
    }
}

// Run the YTM function
int main()
{
    double d, N, PV, c, FV;

    cout<<"In order to calculate the yield to maturity of a bond, please provide the following data:"<<endl;
    cout<<"Year fraction until next couple payment (should be between 0 and 1): d = "; cin>> d;
    cout<<"Number of years until maturity: N = "; cin>> N;
    cout<<"Bond Price: PV = "; cin>> PV;
    cout<<"Coupon value: c = "; cin>> c;
    cout<<"Par value: FV = "; cin>> FV;

    double r = YTM(d, N, PV, c, FV);
    cout<<"Yield to Maturity: YTM = "<< r <<" or "<< r*100 << "%"<<endl;
}
