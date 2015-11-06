#include <stdio.h>

int main(int argc, char **argv)
{
    int a;
    if (a) {
	printf("Set\n");
    } else if (!a) {
	printf("Not set\n");
    }
    return 0;
}
