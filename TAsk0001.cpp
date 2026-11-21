#include <stdio.h>

long long linear_calls = 0;
long long fast_calls = 0;


int digital_root(int n)
{
    if (n < 10)
        return n;

    int sum = 0;

    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }

    return digital_root(sum);
}

long long power_linear(long long base, int exp)
{
    linear_calls++;

    if (exp == 0)
        return 1;

    return base * power_linear(base, exp - 1);
}


long long power_fast(long long base, int exp)
{
    fast_calls++;

    if (exp == 0)
        return 1;

    long long half = power_fast(base, exp / 2);

    if (exp % 2 == 0)
        return half * half;

    return base * half * half;
}


long long power_iterative(long long base, int exp)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result *= base;

        base *= base;
        exp /= 2;
    }

    return result;
}

int main(void)
{
    int exponent;
    long long base;

    printf("Enter base: ");
    if (scanf("%lld", &base) != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter exponent (0 to 30): ");
    if (scanf("%d", &exponent) != 1 ||
        exponent < 0 || exponent > 30)
    {
        printf("Invalid exponent\n");
        return 1;
    }

    printf("\nDigital Root of 9875 = %d\n",digital_root(9875));

    linear_calls = 0;
    long long a = power_linear(base, exponent);

    printf("Linear Power = %lld\n", a);
    printf("Linear Calls = %lld\n", linear_calls);

    fast_calls = 0;
    long long b = power_fast(base, exponent);

    printf("Fast Power = %lld\n", b);
    printf("Fast Calls = %lld\n", fast_calls);

    printf("Iterative Power = %lld\n",
           power_iterative(base, exponent));

    return 0;
}