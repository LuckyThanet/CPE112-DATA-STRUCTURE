#include "moddin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Admin

//create a node of category
CATEGORY_T *createC()
{
  //create temp and store a memory to it
    CATEGORY_T *temp;
    temp = (CATEGORY_T *)malloc(sizeof(CATEGORY_T));
    temp->next = NULL;
    temp->prod = NULL;
    return temp;
}

//create a node of product
PRODUCT_T *createP()
{
  //create temp and store a memory to it
    PRODUCT_T *temp;
    temp = (PRODUCT_T *)malloc(sizeof(PRODUCT_T));
    temp->next = NULL;
    return temp;
}

//link a node to be a linked list (category)
CATEGORY_T *CreateCategory(CATEGORY_T *head, char *data)
{
    CATEGORY_T *node;
    CATEGORY_T *p;
    node = createC();
    node->name = strdup(data);
  //if head is NULL, specification a head to a start 
    if (head == NULL)
    {
        head = node;
    }
      //else if head isn't NULL, create a new node and link it to head
    else
    {
        p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = node;
    }
    return head;
}

//priority queue
PRODUCT_T *CreateProduct(PRODUCT_T *head, char *value, int Hotprice,
                         int Coldprice, int smoothiesprice, int date)
{
    PRODUCT_T *start = head;
    PRODUCT_T *temp = createP();
    temp->data = strdup(value);
    temp->Hotprice = Hotprice;
    temp->Coldprice = Coldprice;
    temp->Smoothiesprice = smoothiesprice;
    temp->date = date;
    if (head == NULL)
    {
        head = temp;
    }
    else if (start->date > date)
    {
        temp->next = start;
        head = temp;
    }
    else
    {
        while (start->next && (start->next->date <= date))
        {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
    return head;
}

//change \n to \0
void DeleteN(char *str)
{
    int len = strlen(str);
    if (str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// Display call when you select role admin and want to show all menu
void Display(CATEGORY_T *head)
{
    int count = 0;
    CATEGORY_T *current = head;
    printf("--------------------------------------------------------\n");
  //loop for print data in node
    while (current)
    {
        printf("Category : %s\n", current->name);
        PRODUCT_T *product = current->prod;
        printf("%-12s\t %26s\n", "Product", "Date(YY/MM/DD)");
        while (product)
        {
            printf("%-30s\t %6d\n", product->data, product->date);
            count++;
            product = product->next;
        }
        if (!count)
        {
            printf("No products in this category.\n");
        }
        printf("--------------------------------------------------------\n");
        count = 0;
        current = current->next;
    }
}

// DisplaySelect is search a product in every category
// call this function when Admin search a product
void DisplaySelect(CATEGORY_T *head, char *str)
{
    int count = 0;
    CATEGORY_T *current = head;
    printf("--------------------------------------------------------\n");
  //loop for print data in node
    while (current)
    {
        printf("Category : %s\n", current->name);
        printf("%-12s\t %26s\n", "Product", "Date(YY/MM/DD)");
        PRODUCT_T *product = current->prod;
        while (product)
        {
            if (strstr(product->data, str))
            {
                count++;
                printf("%-30s\t %6d\n", product->data, product->date);
            }
            product = product->next;
        }
        if (!count)
        {
            printf("There is no %s in this category.\n", str);
        }
        count = 0;
        printf("--------------------------------------------------------\n");
        current = current->next;
    }
    printf("\n");
}

//select a category for product
CATEGORY_T *Select(CATEGORY_T *head, char *str, char *d, int Hotprice, int Coldprice, int Smoothiesprice, int date)
{
    CATEGORY_T *current = head;
    //loop for move node to next node
    while (strcmp(current->name, str) && current)
    {
        current = current->next;
    }
    current->prod = CreateProduct(current->prod, d, Hotprice, Coldprice, Smoothiesprice, date);
    return head;
}

//select a specific product to delete
CATEGORY_T *SelcetDeleteNoded(CATEGORY_T *head, char *selectName, int date)
{
    CATEGORY_T *current = head;
  //loop for move node to next node
    while (current)
    {
        PRODUCT_T *CurrentProduct = current->prod;
        PRODUCT_T *prev = NULL;
      //loop for delete node
        while (CurrentProduct)
        {
            if (!strcmp(CurrentProduct->data, selectName) && CurrentProduct->date == date)
            {
                break;
            }
            prev = CurrentProduct;
            CurrentProduct = CurrentProduct->next;
        }
        if (CurrentProduct)
        {                                               
            if (prev == NULL)
            {
                PRODUCT_T *tmp = CurrentProduct;
                CurrentProduct = CurrentProduct->next;
                current->prod = CurrentProduct;
                free(tmp->data);
                free(tmp);
            }
            else
            {
                prev->next = CurrentProduct->next;
                free(CurrentProduct->data);
                free(CurrentProduct);
            }
        }
        current = current->next;
    }
    return head;
}

//delete a product that expired first
CATEGORY_T *DeleteNode(CATEGORY_T *head, char *selectName)
{
    CATEGORY_T *current = head;
  //loop for move node to next node
    while (current)
    {
        PRODUCT_T *CurrentProduct = current->prod;
        PRODUCT_T *prev = NULL;
      //loop for delete node
        while (CurrentProduct && strcmp(CurrentProduct->data, selectName))
        {
            prev = CurrentProduct;
            CurrentProduct = CurrentProduct->next;
        }
        if (CurrentProduct)
        {
            if (prev == NULL)
            {
                PRODUCT_T *tmp = CurrentProduct;
                CurrentProduct = CurrentProduct->next;
                current->prod = CurrentProduct;
                free(tmp);
            }
            else
            {
                prev->next = CurrentProduct->next;
                free(CurrentProduct);
            }
        }
        current = current->next;
    }
    return head;
}

// Customer
//print all category and product
void PrintCustomer(PRODUCT_T *head)
{
    PRODUCT_T *product = head;
    if (product->Hotprice == 0 && product->Coldprice == 0)
    {
        printf("%-29s\t %2s\t %2s\t %6d\n", product->data, "-", "-", product->Smoothiesprice);
    }
    else if (product->Hotprice == 0 && product->Smoothiesprice == 0)
    {
        printf("%-29s\t %2s\t %-1d\t %6s\n", product->data, "-", product->Coldprice, "-");
    }
    else if (product->Coldprice == 0 && product->Smoothiesprice == 0)
    {
        printf("%-29s\t %-1d\t %2s\t %6s\n", product->data, product->Hotprice, "-", "-");
    }
    else if (product->Hotprice == 0)
    {
        printf("%-29s\t %2s\t %-1d\t %6d\n", product->data, "-", product->Coldprice, product->Smoothiesprice);
    }
    else if (product->Coldprice == 0)
    {
        printf("%-29s\t %-1d\t %2s\t %6d\n", product->data, product->Hotprice, "-", product->Smoothiesprice);
    }
    else if (product->Smoothiesprice == 0)
    {
        printf("%-29s\t %-1d\t %-1d\t %6s\n", product->data, product->Hotprice, product->Coldprice, "-");
    }
    else
    {
        printf("%-29s\t %-1d\t %-1d\t %6d\n", product->data, product->Hotprice, product->Coldprice, product->Smoothiesprice);
    }
}

//restore memory to ram
void FreeProductList(PRODUCT_T *head)
{
  //loop to free a node
    while (head)
    {
        PRODUCT_T *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

//restore memory to ram
void FreeCategoryList(CATEGORY_T *head)
{
  //loop to free a node
  while (head)
    {
        FreeProductList(head->prod);
        CATEGORY_T *temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

// DisplayNonDuplicate
//show all category and product
void DisplayNonDuplicate(CATEGORY_T *head)
{
    CATEGORY_T *current = head;
    PRODUCT_T *headNewProduct = NULL;
  //loop for move node to next node
    while (current)
    {
        printf("--------------------------------------------------------\n");
        printf("Category : %s\n", current->name);
        printf("%-12s\t                %3s %4s %9s\n", "Product", "Hot", "Cold", "Smoothie");
        printf("\n");
        PRODUCT_T *product = current->prod;
      //loop for print all category and product
        while (product)
        {
            if (headNewProduct == NULL)
            {
                headNewProduct = createP();
                headNewProduct->data = strdup(product->data);
                PrintCustomer(product);
            }
            else
            {  
                PRODUCT_T *curNewList = headNewProduct;
                PRODUCT_T *prevNewList = NULL;
                short status = 1;
                while (curNewList)
                {
                    if (!strcmp(curNewList->data, product->data))
                    {
                        status = 0;
                    }
                    prevNewList = curNewList;
                    curNewList = curNewList->next;
                }
                if (status)
                {
                    prevNewList->next = createP();
                    prevNewList->next->data = strdup(product->data);
                    PrintCustomer(product);
                }
            }
            product = product->next;
        }
        current = current->next;
    }
    printf("--------------------------------------------------------\n");
    FreeProductList(headNewProduct);
}

//read file from txt file
CATEGORY_T *ReadFile(CATEGORY_T *head)
{
    FILE *fp;
    fp = fopen("moddin.txt", "r");
    CATEGORY_T *current = head;
    char buffer[100], *prechar;
    int count = 0;
  //loop for read file and insert data to node
    while (fgets(buffer, 100, fp) != NULL)
    {
        char tmp[100];
        int Hotprice;
        int Coldprice;
        int Smoothiesprice;
        int date;
        int len = strlen(buffer);
        if (buffer[0] == '\n')
        {
            count++;
        }
        else if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
      //step for create node
        switch (count)
        {
        case 0:
            current = CreateCategory(current, buffer);
            prechar = strdup(buffer);
            count++;
            break;
        case 1:
            sscanf(buffer, "%s %d %d %d %d", tmp, &Hotprice, &Coldprice,
                   &Smoothiesprice, &date);
            current = Select(current, prechar, tmp, Hotprice, Coldprice,
                             Smoothiesprice, date);
            break;
        default:
            count = 0;
            free(prechar);
            break;
        }
    }
    fclose(fp);
    return current;
}

//write file to txt file
void WriteFile(CATEGORY_T *head)
{
    FILE *fp;
    fp = fopen("moddin.txt", "w");
    CATEGORY_T *current = head;
  //loop for move node to next node
    while (current)
    {
        fprintf(fp, "%s\n", current->name);
        PRODUCT_T *product = current->prod;
      //loop to write file to txt file
        while (product)
        {
            fprintf(fp, "%s %d %d %d %d\n", product->data, product->Hotprice,
                    product->Coldprice, product->Smoothiesprice, product->date);
            product = product->next;
        }
        fprintf(fp, "\n");
        current = current->next;
    }
    fclose(fp);
}

// search product for customer
void DisplaySelectCustomer(CATEGORY_T *head, char *str)
{
    CATEGORY_T *current = head;
    PRODUCT_T *headNewProduct = NULL;
    int count = 0;
  //loop for move node to next node
    while (current)
    {
        printf("--------------------------------------------------------\n");
        printf("Category : %s\n", current->name);
        printf("%-12s\t                %3s %4s %9s\n", "Product", "Hot", "Cold", "Smoothie");
        PRODUCT_T *product = current->prod;
        count = 0;
      //loop for print data in node
        while (product)
        {
            if (headNewProduct == NULL)
            {
                headNewProduct = createP();
                headNewProduct->data = strdup(product->data);
                if (strstr(product->data, str))
                {
                    count++;
                    PrintCustomer(product);
                }
            }
            else
            {
                PRODUCT_T *curNewList = headNewProduct;
                PRODUCT_T *prevNewList = NULL;
                short status = 1;
              //loop for check a data in curNewList is equal to data in product
                while (curNewList)
                {
                    if (!strcmp(curNewList->data, product->data))
                    {
                        status = 0;
                    }
                    prevNewList = curNewList;
                    curNewList = curNewList->next;
                }
                if (status)
                {
                    prevNewList->next = createP();
                    prevNewList->next->data = product->data;
                    if (strstr(product->data, str))
                    {
                        count++;
                        PrintCustomer(product);
                    }
                }
            }
            product = product->next;
        }
        if (!count)
        {
            printf("There are no products you need in this category.\n");
        }
        current = current->next;
    }
    printf("--------------------------------------------------------\n");
    FreeProductList(headNewProduct);
}

// UI
//get data from user
void inputUser(char *str)
{
    char tmp[101];
    fgets(tmp, sizeof(tmp) / tmp[0], stdin);
    DeleteN(tmp);
    strcpy(str, tmp);
}

//check format from user
int CheckValid(char *buffer)
{
    int check = 1;
    DeleteN(buffer);
    for (int i = 0; buffer[i]; i++)
    {
        if (!(buffer[i] >= '0' && buffer[i] <= '9'))
        {
            check = 0;
        }
    }
    return (check) ? atoi(buffer) : 0;
}

//check format from user
int CheckStr(char *buffer)
{
    int count = 0;
    DeleteN(buffer);
    trim(buffer);
    for (int i = 0; buffer[i]; i++)
    {
        if (buffer[i] == ' ')
        {
            return 0;
        }
    }
    return 1;
}

//delete spacebar from user
void trim(char *str)
{
    int len = strlen(str);
    int st = 0, en = len - 1;
    while (str[st] == ' ')
    {
        st++;
    }
    while (en > st && str[en] == ' ')
    {
        en--;
    }
    str[en + 1] = '\0';
    memmove(str, str + st, en - st + 2);
}

//UI in Customer
int Cumstomer()
{
    char str[100];
    printf("--------------------------------------------------------\n");
    printf("----------------->( Role >> Customer )<-----------------\n");
    printf("                     Select option\n");
    printf("  >> 1.show all Cateory                   >> 2.Seacrh menu\n");
    printf("  >> 3.Top up                             >> 4.Home\n");
    printf("                 >> Type anything to exit.\n");
    printf("\n");
    printf("choose your answer >> ");
    fgets(str, 100, stdin);
    return CheckValid(str) ? atoi(str) : 0;
}

//UI in Admin
int Admin()
{
    char str[100];
    printf("--------------------------------------------------------\n");
    printf("------------------->( Role >> Admin )<------------------\n");
    printf("                      Select option\n");
    printf("  >> 1.Add menu (Category)                >> 2.Add menu (Product)\n");
    printf("  >> 3.Seacrh menu                        >> 4.Delete menu\n");
    printf("  >> 5.Show the menu                      >> 6.Home\n");
    printf("                 >> Type anything to exit.\n");
    printf("choose your answer >> ");
    fgets(str, 100, stdin);
    // scanf("%s",str);
    return CheckValid(str) ? atoi(str) : 0;
}

//function to buy a product
CATEGORY_T *BuyProduct(CATEGORY_T *head, int *cash)
{
  CATEGORY_T *current = head, *p = head;
    int money = *cash, choice, n, status = 0;
    char NameProduct[101], InputMoney[101];
    printf("---------------------->( MODDIN )<----------------------\n");
    printf("what drink do you want >> ");
    fgets(NameProduct, 101, stdin);
    printf("Select type of drink ->  ( 1.Hot ) ( 2.Cold ) ( 3.Smoothies )\n");
    printf("choose your answer >> ");
    fgets(InputMoney, 101, stdin);
    n = CheckStr(NameProduct);
    choice = CheckValid(InputMoney);
  //loop for move a node to next node
    while (p)
    {
        PRODUCT_T *product = p->prod;
      //loop to check money is enough
        while (product)
        {
            if (!strcmp(NameProduct, product->data) && !status)
            {
                status = 1;
                if (choice == 1)
                {
                    money = money - product->Hotprice;
                    if (!product->Hotprice)
                    {
                        status = 0;
                    }
                }
                else if (choice == 2)
                {
                    money = money - product->Coldprice;
                    if (!product->Coldprice)
                    {
                        status = 0;
                    }
                }
                else if (choice == 3)
                {
                    money = money - product->Smoothiesprice;
                    if (!product->Smoothiesprice)
                    {
                        status = 0;
                    }
                }
            }
            product = product->next;
        }
        p = p->next;
    }
    if (n && money >= 0 && status)
    {
        (*cash) = money;
        current = DeleteNode(current, NameProduct);
    }
    else if (money < 0)
    {
        printf("balance is not enough\n");
    }
    else
    {
        printf("Invalid\n");
    }
    return current;
}

//choose to be an Admin or a customer
CATEGORY_T *SelectMenu(CATEGORY_T *head)
{
    CATEGORY_T *current = head;
    int Ans, cash;
    char choice[101];
    printf("---------------------->( MODDIN )<----------------------\n");
    printf("                     Choose a role\n");
    printf("  >> 1.Customer                          >> 2.Admin     \n");
    printf("               >> Type anything to exit.\n");
    printf("\n");
    printf("choose your answer >> ");
    fgets(choice, 101, stdin);
    Ans = CheckValid(choice);
  //if 1 you are customer
    if (Ans == 1)
    {
        printf("--------------------------------------------------------\n");
        printf("Please enter your money >> ");
        inputUser(choice);
        cash = CheckValid(choice);
        while (!cash)
        {
            int n;
            printf("-> Select 1 to try again \n");
            printf("-> Type anything to exit.\n");
            printf("Select here >> ");
            inputUser(choice);
            n = CheckValid(choice);
            if (n == 1)
            {
                printf("Please enter your money >> ");
                inputUser(choice);
                cash = CheckValid(choice);
            }
            else
            {
                current = SelectMenu(current);
                return current;
            }
        }
        printf("balance : %d Baht\n", cash);
        Ans = Cumstomer();
        while (Ans && Ans < 5) // role customer
        {
            if (Ans == 1) // show all menu for customer
            {
                int x;
                DisplayNonDuplicate(current);
                printf("-> Select 1 to Buy a product\n");
                printf("-> Type anything to exit.\n");
                printf("choose here >> ");
                inputUser(choice);
                x = CheckValid(choice);
                if (x == 1)
                {
                    current = BuyProduct(current, &cash);
                    WriteFile(current);
                    printf("change = %d\n", cash);
                }
            }
            else if (Ans == 2) // search menu for customer
            {
                int x;
                printf("Type a name of Product.\n");
                printf("choose here >> ");
                inputUser(choice);
                x = CheckStr(choice);
                DisplaySelectCustomer(current, choice);
                printf("Select 1 to Buy a product or Type anything to exit.\n");
                printf("choose here >> ");
                fgets(choice, 101, stdin);
                x = CheckValid(choice);
                if (x == 1)
                {
                    current = BuyProduct(current, &cash);
                    WriteFile(current);
                    printf("change = %d\n", cash);
                }
            }
            else if (Ans == 3)
            {
                int money;
                printf("Please enter your money >> ");
                inputUser(choice);
                money = CheckValid(choice);
                if (money)
                {
                    cash += money;
                    printf("change = %d\n", cash);
                }
                else
                {
                    printf("Invalid\n");
                }
            }
            else if (Ans == 4)
            {
                current = SelectMenu(current);
                return current;
            }
            Ans = Cumstomer();
        }
    }
      //if 2 you are Admin
    else if (Ans == 2)
    {
        char p[101];
        int correct = 0, trypass = 0; // check correct password and try password
        char password[] = "12345678";
        printf("--------------------------------------------------------\n");
        printf("        **Enter the Admin password (3 times)**\n");
        while (correct != 1 && trypass != 3)
        {
            printf("Enter password >> ");
            fgets(p, 101, stdin);
            DeleteN(p);
            if (!strcmp(p, password))
            {
                correct++; // correct++ means password correct
            }
            else
            {
                trypass++; // count try password
                printf("Incorrect !!\n");
            }
        }
        if (correct)
        {
            Ans = Admin();
            while (Ans && Ans < 7)
            {
                if (Ans == 1) // Add category
                {
                    char strNameCategory[101];
                    CATEGORY_T *ptr = head;
                    printf("--------------------------------------------------------\n");
                    while (ptr)
                    {
                        printf("CATEGORY : %s\n", ptr->name);
                        ptr = ptr->next;
                    }
                    printf("Add New Category >> ");
                    inputUser(strNameCategory);
                    current = CreateCategory(current, strNameCategory);
                    WriteFile(current);
                    printf("successfully added\n");
                    printf("--------------------------------------------------------\n");
                }
                else if (Ans == 2) // Add product
                {
                    char strFormat[201], strNameC[50], strNameP[50];
                    int hot, cold, smooth, date;
                    CATEGORY_T *ptr = head;
                    printf("--------------------------------------------------------\n");
                    while (ptr)
                    {
                        printf("CATEGORY : %s\n", ptr->name);
                        ptr = ptr->next;
                    }
                    printf("                    Type Format Add menu\n");
                    printf("\n");
                    printf("Add Category name >> ");
                    scanf("%s", strNameC);
                    printf("Add Product name >> ");
                    scanf("%s", strNameP);
                    printf("Add Hotprice >> ");
                    scanf("%d", &hot);
                    printf("Add Coldprice >> ");
                    scanf("%d", &cold);
                    printf("Add Smoothiesprice >> ");
                    scanf("%d", &smooth);
                    printf("Add Date(YY/MM/DD) >> ");
                    scanf("%d", &date);
                    char tmp;
                    scanf("%c", &tmp); // get \n in stdin
                    current = Select(current, strNameC, strNameP, hot, cold, smooth, date);
                    WriteFile(current);
                    printf("successfully added !!\n");
                }
                else if (Ans == 3) // search
                {
                    char NameProduct[101];
                    printf("--------------------------------------------------------\n");
                    printf("Search name of product >> ");
                    inputUser(NameProduct);
                    DisplaySelect(head, NameProduct);
                }
                else if (Ans == 4) // delete
                {
                    int date;
                    char NameProduct[101];
                    Display(current);
                    printf("--------------------------------------------------------\n");
                    printf("Type Product that you want to delete\n");
                    printf("          Type format\n");
                    printf("Product name >> ");
                    scanf("%s", NameProduct);
                    printf("Date (YY/MM/DD) >> ");
                    scanf("%d", &date);
                    char tmp;
                    scanf("%c", &tmp); // get \n in stdin
                    current = SelcetDeleteNoded(current, NameProduct, date);
                    WriteFile(current);
                    printf("delete successfully !!\n");
                }
                else if (Ans == 5) // Show all product
                {
                    Display(current);
                }
                else if (Ans == 6)
                {
                    current = SelectMenu(current);
                    return current;
                }
                Ans = Admin();
            }
        }
        else
        {
            int x;
            char str[101];
            printf("-> Select 1 to Home\n");
            printf("-> Type anything to exit.\n");
            printf("choose here >> ");
            inputUser(str);
            x = CheckValid(str);
            if (x == 1)
            {
                current = SelectMenu(current);
                return current;
            }
        }
    }
    WriteFile(current);
    return current;
}