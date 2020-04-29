/* exp(x) - exponential function of a real number.
            The argument, x, must be type double.
            The function returned is of type double.
            if x<-88, function returns zero (0.0)
            if x>88, function returns largest number.
*/
#define INDEX 15 /* number of factors for power series */
#define LN2    6.931471805599453e-01
#define LOG2E  1.442695040888963
#define F17   -2.811457254345521e-15
#define E      2.718281828459045
#define E_I    3.678794411714423e-01
double exp(x)
double x;
{ static double f[INDEX] = { 5.000000000000000e-01,
                            -1.666666666666667e-01,
                             4.166666666666667e-02,
                            -8.333333333333333e-03,
                             1.388888888888889e-03,
                            -1.984126984126984e-04,
                             2.480158730158730e-05,
                            -2.755731922398589e-06,
                             2.755731922398589e-07,
                            -2.505210838544172e-08,
                             2.087675698786810e-09,
                            -1.605904383682161e-10,
                             1.147074559772972e-11,
                            -7.647163731819816e-13,
                             4.779477332387385e-14 };
   union
   {
     double e;
     char c[8];
   } z;
   double dint();
   register int n;
   int m;
/* check for obvious values */
   if ( x == 0.0 )
     return(1.0);
   if ( x == 1.0 )
     return(E);
   if ( x == -1.0 )
     return(E_I);
/* check for range of argument */
   if ( x > 88.0 )  /* return largest value */
   { for ( n = 1; n < 8; ++n )
        z.c[n] = 0x7f;
     z.c[0] = 0x7f;
     return(z.e);
   }
   else
     if ( x < -88.0 )
        return(0.0);
/* reduce range of x and save exponent for adjustment */
   m = dint(x*LOG2E) + 1;
   x = -x + m * LN2;
/* calculate exponential function */
   if ( x < 1.0e-09 ) /* check for very small values */
     z.e = 1.0 - x;
   else  /* compute power series */
   { z.e = x * F17;
     for ( n = INDEX -1; n >= 0; --n )
       z.e = ( z.e + f[n] ) * x;
     z.e = ( z.e - 1.0 ) * x + 1.0;
   }
   z.c[7] += m; /* adjust exponent */
   return(z.e);  /* return exp(x) */
}


