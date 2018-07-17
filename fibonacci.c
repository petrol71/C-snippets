//  Calculates Fibonacci numbers 1-50.
//  Created by Petri Ollonen on 18/07/2018.
//  Copyright © 2018 Petri Ollonen. All rights reserved.
//

#include <stdio.h>

int main(void)
{
    long int prev = 0;
    long int curr = 1;
    long int next;
    
    printf("1: %ld\n2: %ld\n", prev, curr);
    
    for(int i=2; i<50; i++)
    {
        next = prev + curr;
        prev = curr;
        curr = next;
        printf("%d: %ld\n", i+1, next);
    }
    
    return 0;
}
