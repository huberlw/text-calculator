//#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //gtk_init(&argc, &argv);

    // put gtk code here

    //gtk_main();

    // NO GUI FOR NOW
    // JUST COMMAND LINE CALCULATOR
    setbuf(stdout, NULL);

    char expression[10];
    int len = 10;

    printf("Enter mathematical expression:\n");
    fgets(expression, len, stdin);

    printf("You entered the following expresion:\n");
    printf(expression);

    return 0;
}