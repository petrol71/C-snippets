//  Neat function pointer excercise.
//  Created by Petri Ollonen on 18/07/2018.
//  Copyright © 2018 Petri Ollonen. All rights reserved.
//

#include <stdio.h>

/*Function prototypes*/
int f(int num);
void map(int a[], int arrSize, int (*foo)(int));

int main(void)
{
    int arrSize = 10;
    int a[arrSize];
    
    int (*foo)(int);
    foo = &f;
    
    map(a, arrSize, f);
   
    return 0;
}

void map(int arr[], int size, int (*foo)(int))
{
   
    for(int i=0; i<size; i++)
    {
        arr[i] = foo(i);
        printf("%d\n", arr[i]);
    }
}

int f(int num)
{
    return ++num;
}
