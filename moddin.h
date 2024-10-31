#ifndef moddin
#define moddin

typedef struct product
{
    char *data;
    int Hotprice;
    int Coldprice;
    int Smoothiesprice;
    int date;
    struct product *next;
} PRODUCT_T;

typedef struct category
{
    char *name;
    struct category *next;
    struct product *prod;
} CATEGORY_T;

//Admin 

CATEGORY_T *createC(); 

PRODUCT_T *createP(); 

CATEGORY_T *CreateCategory(CATEGORY_T *head, char *data);

PRODUCT_T *CreateProduct(PRODUCT_T *head, char *value, int Hotprice, int Coldprice, int smoothiesprice,int date);

void DeleteN (char * str);

void Display(CATEGORY_T *head);

void DisplaySelect(CATEGORY_T *head ,char *str);

CATEGORY_T *Select(CATEGORY_T *head, char *str, char *d, int Hotprice, int Coldprice, int smoothiesprice , int date);

void WriteFile(CATEGORY_T *head); 

//Customer

void PrintCustomer(PRODUCT_T *head);

void FreeProductList(PRODUCT_T *head);

void FreeCategoryList(CATEGORY_T *head);

void DisplayNonDuplicate(CATEGORY_T *head);

CATEGORY_T *SelcetDeleteNoded(CATEGORY_T *head, char *selectName , int date);

CATEGORY_T *DeleteNode(CATEGORY_T *head, char *selectName);

void SearchProduct(CATEGORY_T *head , char *selectName);

CATEGORY_T* ReadFile(CATEGORY_T *head);

void DisplaySelectCustomer(CATEGORY_T *head , char *str);

//UI
//main interface

void inputUser(char *str);

int CheckValid (char *str);

int CheckStr(char *buffer);

void trim(char *str);

int Cumstomer();

int Admin();

CATEGORY_T *BuyProduct(CATEGORY_T *head , int *cash);

CATEGORY_T * SelectMenu(CATEGORY_T * head);

#endif

