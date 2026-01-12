#include "stdio.h"
#include "math.h"
#include "conio.h"

struct polynomial
{
    double m_coeff[10];
    int m_power[10];
};

void RearrangePoly (int maxPower, double coeff[], int power[], double tempCoeff[])
{
    int i=0;
    do
    {
        tempCoeff[maxPower-power[i]]=coeff[i];
        i++;
    }
    while(power[i-1]!=0);
    for(i=0;i<=maxPower;i++)
    {
        power[i]=maxPower-i;
        coeff[i] = tempCoeff[i];
        tempCoeff[i] = 0;
    }
}

void EnterPoly (char c[],int* maxPower ,double coeff[], int power[], double tempCoeff[])
{
    int i=0;
    printf("Enter the %s polynomial [ 1x^(4) -9x^(3) 2x^(1) 0 ]: ",c);
    for(i=0; ; i++)
    {
        scanf("%lfx^(%d)", &coeff[i] , &power[i]);
        if(power[i]==0) break;
    }
    *maxPower = power[0];
    RearrangePoly (*maxPower, coeff, power, tempCoeff);
}

void ResultCalc(int denomMaxPower, double denomCoeff[]  , double nomCoeff[], int nomPower[], double resultCoeff[], int resultPower[] , int n)
{
    resultPower[n] = nomPower[n] - denomMaxPower;
    resultCoeff[n] = nomCoeff[n] / denomCoeff[0];
}

void SubFactor (int denomMaxPower , double denomCoeff[], double tempCoeff[], double resultCoeff[], int n)
{
    int i;
    for(i=0;i<=denomMaxPower;i++)
    {
        tempCoeff[i+n]= resultCoeff[n] * denomCoeff[i];
    }
}

void NewNomPoly (int nomMaxPower, double nomCoeff[], double tempCoeff[])
{
    int i;
    for(i=0;i<=nomMaxPower;i++)
    {
        nomCoeff[i] = nomCoeff[i] - tempCoeff[i];
    }
}

void printPoly (int start, int end, double polyCoeff[], int polyPower[])
{
    int i;
    for (i=start;i<=(end);i++)
    {
        if (i>start)
        {
            if(polyCoeff[i]==0.0) continue;
            else if(polyCoeff[i]>0) printf(" + ");
            else if(polyCoeff[i]<0)printf(" - ");
            if(polyPower[i]==0) printf("%0.2lf", fabs(polyCoeff[i]));
            else if(polyPower[i]==1)
            {
                if (polyCoeff[i]==1) printf("x");
                else printf("%0.2lfx", fabs(polyCoeff[i]));
            }
            else if (polyPower[i]>1)
            {
                if (polyCoeff[i]==1) printf("x^(%d)", polyPower[i]);
                else printf("%0.2lfx^(%d)", fabs(polyCoeff[i]), polyPower[i]);
            }
        }
        else
        {
            if(polyCoeff[i]==0.0) continue;
            if(polyPower[i]==0) printf("%0.2lf", polyCoeff[i]);
            else if(polyPower[i] == 1) 
            {
                if (polyCoeff[i]==1) printf("x");
                else printf("%0.2lfx", polyCoeff[i]);
            }
            else if(polyPower[i]>1)
            {
                if (polyCoeff[i]==1) printf("x^(%d)", polyPower[i]);
                else printf("%0.2lfx^(%d)", polyCoeff[i], polyPower[i]);
            }
        }
    }
}

void PrintResult (int nomMaxPower,int denomMaxPower, double resultCoeff[], int resultPower[])
{
    printf("\nThe result is: ");
    printPoly (0, nomMaxPower-denomMaxPower, resultCoeff, resultPower);
}

void PrintRemainder (int denomMaxPower, int nomMaxPower, double denomCoeff[], int denomPower[], double nomCoeff[], int nomPower[], int n)
{
    printf("(");
    printPoly (n, denomMaxPower+n-1, nomCoeff, nomPower);
    printf(")/");
    printf("(");
    printPoly (0, denomMaxPower, denomCoeff, denomPower);
    printf(")\n");
}

void PrintRemainderOnly (int denomMaxPower, int nomMaxPower, double denomCoeff[], int denomPower[], double nomCoeff[], int nomPower[], int n)
{
    printf("(");
    printPoly (n, nomMaxPower, nomCoeff, nomPower);
    printf(")/");
    printf("(");
    printPoly (0, denomMaxPower, denomCoeff, denomPower);
    printf(")\n");
}

int PolyCompare (int denomMaxPower, int nomMaxPower, double denomCoeff[], int denomPower[], double nomCoeff[], int nomPower[])
{
    int i,counter;
    if(nomMaxPower>denomMaxPower)
        return 1;
    else if (nomMaxPower<denomMaxPower)
        return -1;
    else
    {
        for(i=0,counter=0;i<=denomMaxPower;i++)
        {
            if(nomCoeff[i]!=denomCoeff[i])
                counter ++;
        }
        if (counter==0) return 0;
        else return 1;
    }
}

int main()
{
    printf ("Name: Mahmoud Ahmed Mohamed Elwan Ahmed Siam\n\tID: 1900135\nGroup: 2\tSection:9\n");
    printf ("========================================\n");
    printf ("Welcome to polynomial division calculator");
    printf ("\n========================================\n");
    printf ("Example: Enter the polynomial as follows [ 1x^(4) -9x^(3) 2x^(1) 0 ] \nYou should enter all the coefficients even if it is 1 but you don't have to enter 0!\n");
    printf ("You should enter the free term even if it is 0 like the example above!\n");
    printf ("You should the power of x even if it is 1!\n");
    printf ("\n========================================\n");
    int i = 0, j, compare, counter = 0 , k;
	int nomMaxPower, denomMaxPower;
    struct polynomial SNom, SDenom, STemp, SResult;
    for(i=0;i<=nomMaxPower;i++)
    {
        STemp.m_coeff[i] = 0;
        SNom.m_power[i] = 0;
        SDenom.m_power[i] = 0;
    }
    i=0;
    EnterPoly("numerator", &nomMaxPower, SNom.m_coeff, SNom.m_power, STemp.m_coeff);
    EnterPoly("denominator", &denomMaxPower , SDenom.m_coeff, SDenom.m_power, STemp.m_coeff);
    compare = PolyCompare(denomMaxPower,nomMaxPower,SDenom.m_coeff,SDenom.m_power,SNom.m_coeff,SNom.m_power);
    if (compare<0)
    {
        PrintRemainderOnly (denomMaxPower, nomMaxPower, SDenom.m_coeff, SDenom.m_power, SNom.m_coeff, SNom.m_power, i);
    }
    else if (compare>0)
    {
        for (i=0;i<=(nomMaxPower-denomMaxPower);i++)
        {
            ResultCalc(denomMaxPower, SDenom.m_coeff, SNom.m_coeff, SNom.m_power, SResult.m_coeff, SResult.m_power , i);
            SubFactor (denomMaxPower , SDenom.m_coeff, STemp.m_coeff, SResult.m_coeff, i);
            NewNomPoly (nomMaxPower, SNom.m_coeff, STemp.m_coeff);
        }
            PrintResult(nomMaxPower, denomMaxPower, SResult.m_coeff ,SResult.m_power);
            for(k=0;k<=nomMaxPower;k++){}
            for(j=i;j<=nomMaxPower;j++)
            {
            if((SNom.m_coeff[j]!=0) && (SNom.m_coeff[j]!=-0)) counter++;
            }
            if (counter!=0 )
            {
                printf(" + ");
                PrintRemainder (denomMaxPower, nomMaxPower, SDenom.m_coeff, SDenom.m_power, SNom.m_coeff, SNom.m_power, i);
            }
            else printf("\n");
    }
    else if(compare==0)
    {
        printf ("\nThe result is: 1.00\n");
    }
	return 0;
}