//  Calculates Fibonacci numbers 1-50 recursively.
//  Implementation is very exhaustive!
//  Created by Petri Ollonen on 18/07/2018.
//  Copyright © 2018 Petri Ollonen. All rights reserved.
//

#include <stdio.h>

long int fibonacci(int num);

int main(void)
{
    for(int i=0; i<50; i++)
    {
        printf("%d: %ld\n", i+1, fibonacci(i));
    }
   
    return 0;
}

long int fibonacci(int n)
{
    if(n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (fibonacci(n-1) + fibonacci(n-2));
}
