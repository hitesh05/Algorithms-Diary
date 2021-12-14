# CHAPTER 1: INTRODUCTION TOPICS


# Sieve of Eratosthenes

Sieve of Eratosthenes is a very efficient algorithms which calculates all the prime numbers between 1 to n (n is any natural number). The algorithm was invented by the Greek scientist and mathematician in 4th century B.C. He is also famous for making the first measurement of the size of the Earth.

**The Algorithm:**

1. Write all numbers between 2 to n.
2. Mark all the proper multiples of 2 as composite, since 2 is the only even prime number.
3. Iterate from 2 and find the next number that has not yet been marked (3). 3 is prime, and now mark all the proper multiples of 3 as composite.
4. Continuing with the algorithm, the next number will be 5, hence it is prime and now mark all its proper multiples as composite. 
5. Continue till all the numbers till n have been processed.

![](img1.png)


**Code**

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

using VB = vector<bool>;

VB sieveOfEratosthenes(int n)
{
    VB v(n + 1, true);
    v[0] = v[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (v[i] && ll(i * i) <= n)
        {
            for (int j = i * i; j <= n; j += i)
            {
                v[j] = false;
            }
        }
    }

    return v;
}

int main()
{
    cout << "enter n" << endl;
    int n;
    cin >> n;

    VB isprime = sieveOfEratosthenes(n);

    for (int i = 0; i < isprime.size(); i++)
    {
        if (isprime[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
}
```

> Complexity: $O(n*log(logn))$

### Examples
[Example 1](https://codeforces.com/contest/776/problem/B)

Solution:
```c++
#include <bits/stdc++.h>
using namespace std;

int sieve[100005];

int main()
{
    int i, n, j;
    cin >> n;
    for (i = 2; i <= n + 1; i++)
    {
        if (!sieve[i])
            for (j = 2 * i; j <= n + 1; j += i)
                sieve[j] = 1;
    }

    if (n > 2)
        cout << "2" << endl;
    else
        cout << "1" << endl;

    for (i = 2; i <= n + 1; i++)
    {
        if (!sieve[i])
            cout << "1 ";
        else
            cout << "2 ";
    }

    return 0;
}
```

### Practice Problems (Click on the problem link to view the problem)
The problems are sorted by difficulty.

[Problem 1](https://codeforces.com/contest/26/problem/A)

[Problem 2](https://codeforces.com/problemset/problem/17/A)

[Problem 3](https://codeforces.com/problemset/problem/154/B)