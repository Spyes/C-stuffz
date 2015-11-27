#include <stdio.h>
#include <stdlib.h>

/*
 * 1. Move the subtree consisting of the top n-1 disks from S to I
 * 2. Move the remaining (largest) disk from S to D
 * 3. Move the subtee from I to D
 */

void doTowers(int topN, char src, char inter, char dest)
{
    if (topN == 1)
	printf("Disk 1 from %c to %c\n", src, dest);
    else {
	doTowers(topN-1, src, dest, inter);
	printf("Disk %i from %c to %c\n", topN, src, dest);
	doTowers(topN-1, inter, src, dest);
    }
}

int main(int argc, char **argv)
{
    printf("Enter number of disks: ");
    char ch;
    int nDisks;
    ch = getch();
    printf("\n");
    nDisks = ch - '0';
    doTowers(nDisks, 'A', 'B', 'C');
    return 0;
}
