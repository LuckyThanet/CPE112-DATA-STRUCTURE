#include <stdio.h>
#include "moddin.h"

int main()
{
    CATEGORY_T *head = NULL;
    head = ReadFile(head);
    head = SelectMenu(head);
    FreeCategoryList(head);
    return 0;
}
