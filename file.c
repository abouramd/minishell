#include <stdio.h>
// int main()
// {
//     int size;
//     scanf("%d", &size);
//     int i = 1,j=0,k=1,l=size/2-1;
//     while (j<size)
//     {
//         printf("X");
//         j++;
//     }
//     printf("\n");
//     while (i < size / 2)
//     {
//         j = 0;
//         while (j < size/2)
//         {
//             if(j == 0 || j == k)
//                 printf("X");
//             else
//                 printf(" ");
//             j++;
//         }
//         j = 0;
//         while (j < size/2)
//         {
//             if (j == 0||j==l)
//                 printf("X");
//             else
//                 printf(" ");
//             j++;
//         }
//         printf("X");
//         printf("\n");
//         i++;
//         k++;
//         l--;
//     }
//     j = 0;
//      while (j<size)
//     {
//         printf("X");
//         j++;
//     }
//     printf("\n");
//     i = 1,j=0,k=1,l=size/2-1;
//     while (i < size / 2)
//     {
//         j = 0;
//         while (j < size/2)
//         {
//             if(j == 0 || j == l)
//                 printf("X");
//             else
//                 printf(" ");
//             j++;
//         }
//         j = 0;
//         while (j < size/2)
//         {
//             if (j == 0||j==k)
//                 printf("X");
//             else
//                 printf(" ");
//             j++;
//         }
//         printf("X");
//         printf("\n");
//         i++;
//         k++;
//         l--;
//     }
//     j = 0;
//      while (j<size)
//     {
//         printf("X");
//         j++;
//     }
//     printf("\n");
// }
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N][4];
    for (int i = 0; i < N; i++) {
        int w;
        int x;
        int y;
        int z;
        scanf("%d%d%d%d", &w, &x, &y, &z);
        arr[i][0] = w;
        arr[i][1] = x;
        arr[i][2] = y;
        arr[i][3] = z;
        int k = 0;
        int max = -1000;
        int pos;
        while (k < 4)
        {
            if (max < arr[i][k])
            {
                max = arr[i][k];
                pos = k;
            }
            //printf("%d ", arr[i][k]);
            k++;
        }
        arr[i][pos] = -1000;
        max = -1000;
        k = 0;
        while (k < 4)
        {
            if (max < arr[i][k])
            {
                max = arr[i][k];
            }
            //printf("%d ", arr[i][k]);
            k++;
        }
      printf("%d\n", max);
    }
}