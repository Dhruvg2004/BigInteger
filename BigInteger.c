#include "BigInteger.h"

#define max 1001

struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node* l;
    int length;
};

void addatfront(struct node** n1, int data);
struct BigInteger initialize(char* s);
void display(struct node* n1);
struct BigInteger add(struct BigInteger n1, struct BigInteger n2);
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2); // Changed function name
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2); // Changed function name
//struct BigInteger div1(struct BigInteger int1, struct BigInteger int2); // Changed function name
struct node* reverse(struct node* head);

// Function to convert BigInteger to a string
char* bigIntegerToString(struct BigInteger n);

int main() {
    struct BigInteger n1;
    struct BigInteger n2;
    char num1[max], num2[max];

    printf("Enter the big Number-1: ");
    fgets(num1, max, stdin);
    printf("Enter the big Number-2: ");
    fgets(num2, max, stdin);

    n1 = initialize(num1);
    n2 = initialize(num2);

    display(n1.l);
    display(n2.l);

    struct BigInteger sum = add(n1, n2);
    struct BigInteger difference = sub(n1, n2); // Changed function name

    printf("\nSum: ");
    display(sum.l);
    printf("Difference: ");
    display(difference.l);

    // Implement other operations (e.g., multiplication, division) here if needed
    struct BigInteger product = mul(n1, n2); // Changed function name
    printf("\nProduct: ");
    display(product.l);

    // Perform division
    // struct BigInteger divisionResult = div1(n1, n2); // Changed function name
    printf("Division: ");
    //display(divisionResult.l);

    // Free the memory used by linked lists in n1, n2, and the result structures
    return 0;
}

void addatfront(struct node** n1, int data) {
    // Function to add a new node with data at the front of the linked list.
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = data;
    temp->next = *n1;
    *n1 = temp;
}

struct BigInteger initialize(char* s) {
    // Function to initialize a BigInteger structure from a string of digits.
    struct BigInteger n1;
    n1.l = NULL;
    n1.length = 0;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            addatfront(&(n1.l), (s[i] - '0')); // Convert character to integer and add it to the list
            n1.length++;
        }
    }

    return n1;
}

void display(struct node* n1) {
    // Function to display the contents of a BigInteger as a string.
    if (!n1) {
        printf("0");
        return;
    }

    while (n1) {
        printf("%d", n1->data);
        n1 = n1->next;
    }
    printf("\n");
}

struct BigInteger add(struct BigInteger n1, struct BigInteger n2) {
    // Function to add two BigIntegers and return the result as a new BigInteger.
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;

    int carry = 0;
    struct node* p1 = n1.l;
    struct node* p2 = n2.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int sum = carry + val1 + val2;
        carry = sum / 10;
        addatfront(&(result.l), sum % 10);
        result.length++;

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    if (carry > 0) {
        addatfront(&(result.l), carry);
        result.length++;
    }

    return result;
}

struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
    // Function to multiply two BigIntegers and return the result as a new BigInteger.
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;

    if (num1.length == 0 || num2.length == 0) {
        // If either input is empty, the product is also empty
        return result;
    }

    int num1_digits[num1.length];
    int num2_digits[num2.length];

    // Extract digits from num1 and num2
    struct node* p1 = num1.l;
    struct node* p2 = num2.l;
    int i = 0;

    while (p1) {
        num1_digits[i++] = p1->data;
        p1 = p1->next;
    }

    i = 0;
    while (p2) {
        num2_digits[i++] = p2->data;
        p2 = p2->next;
    }

    // Initialize an array to store the product
    int product_size = num1.length + num2.length;
    int product[product_size];
    for (i = 0; i < product_size; i++) {
        product[i] = 0;
    }

    // Perform the multiplication
    for (i = 0; i < num1.length; i++) {
        for (int j = 0; j < num2.length; j++) {
            product[i + j] += num1_digits[i] * num2_digits[j];
        }
    }

    // Handle carry and overflow
    for (i = 0; i < product_size - 1; i++) {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    // Remove leading zeros
    int result_length = product_size;
    while (result_length > 0 && product[result_length - 1] == 0) {
        result_length--;
    }

    for (i = result_length - 1; i >= 0; i--) {
        addatfront(&(result.l), product[i]);
        result.length++;
    }
    struct node *ptr = result.l;
    ptr = reverse(ptr);
    result.l = ptr;
    return result;
}

struct BigInteger sub(struct BigInteger n1, struct BigInteger n2) {
    // Function to subtract two BigIntegers and return the result as a new BigInteger.
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;

    // Check if n2 is larger than n1 in absolute value, and swap them if necessary
    if (n2.length > n1.length) {
        struct BigInteger temp = n1;
        n1 = n2;
        n2 = temp;
    } else if (n2.length == n1.length) {
        struct node* p1 = n1.l;
        struct node* p2 = n2.l;
        int shouldSwap = 0;
        while (p1 && p2) {
            if (p2->data > p1->data) {
                shouldSwap = 1;
                break;
            } else if (p1->data > p2->data) {
                shouldSwap = 0;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        if (shouldSwap) {
            struct BigInteger temp = n1;
            n1 = n2;
            n2 = temp;
        }
    }

    int borrow = 0;
    struct node* p1 = n1.l;
    struct node* p2 = n2.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        addatfront(&(result.l), diff);
        result.length++;

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    // Remove leading zeros if any
    while (result.l && result.l->data == 0) {
        struct node* temp = result.l;
        result.l = result.l->next;
        free(temp);
        result.length--;
    }

    return result;
}

struct node* reverse(struct node* head) {
    // Function to reverse a linked list and return the new head.
    struct node* temp1 = NULL;
    struct node* temp2 = NULL;
    while (head != NULL) {
        temp2 = head->next;
        head->next = temp1;
        temp1 = head;
        head = temp2;
    }
    head = temp1;
    return temp1;
}

char* bigIntegerToString(struct BigInteger n) {
    // Function to convert a BigInteger to a string.
    char* str = (char*)malloc((n.length + 1) * sizeof(char));
    int i = 0;
    struct node* current = n.l;
    while (current != NULL) {
        str[i] = current->data + '0';
        current = current->next;
        i++;
    }
    str[i] = '\0';
    return str;
}

void addToBigInteger(struct BigInteger* n1, int digit) {
    // Function to add a digit to the front of a BigInteger.
    addatfront(&(n1->l), digit);
    n1->length++;
}

// Function to compare two BigInteger numbers
int compare(struct BigInteger n1, struct BigInteger n2) {
    if (n1.length > n2.length) {
        return 1;
    } else if (n1.length < n2.length) {
        return -1;
    } else {
        // If lengths are equal, compare digit by digit
        struct node* p1 = n1.l;
        struct node* p2 = n2.l;
        while (p1 && p2) {
            if (p1->data > p2->data) {
                return 1;
            } else if (p1->data < p2->data) {
                return -1;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return 0;  // Numbers are equal
}

// Updated divide function
struct BigInteger div1(struct BigInteger int1, struct BigInteger int2) {
    struct BigInteger quotient;
    quotient.l = NULL;
    struct node* ptr1 = int1.l;
    struct node* ptr2 = int2.l;
    int1.l = reverse(ptr1);
    int2.l = reverse(ptr2);
    struct BigInteger zero;
    zero.l = NULL;

    if (compare(int2, zero) == 0) {
        printf("Division by zero is undefined.\n");
        return quotient;
    }

    struct BigInteger currentPart;
    currentPart.l = NULL;
    currentPart.length = 0;
    int int1Length = int1.length;

    struct BigInteger ten;
    ten.l = NULL;
    addatfront(&(ten.l), 1); // Initialize ten with 1

    for (int i = 0; i < int1Length; i++) {
        currentPart = mul(currentPart, ten);
        addatfront(&(currentPart.l), int1.l->data);
        currentPart.length++;

        int digit = 0;
        while (compare(currentPart, int2) != -1) {
            currentPart = sub(currentPart, int2);
            digit++;
        }

        if (quotient.length > 0 || digit != 0) {
            addatfront(&(quotient.l), digit);
            quotient.length++;
        }

        if (int1.l) {
            int1.l = int1.l->next;
            if (currentPart.length == 1 && currentPart.l->data == 0) {
                currentPart.length = 0;
                free(currentPart.l);
                currentPart.l = NULL;
            }
        }
    }

    while (quotient.length > 1 && quotient.l->data == 0) {
        // Remove leading zeros in the quotient.
        struct node* temp = quotient.l;
        quotient.l = quotient.l->next;
        free(temp);
        quotient.length--;
    }
    struct node* ptr3 = quotient.l;
    ptr3 = reverse(ptr3);
    quotient.l = ptr3;
    return quotient;
}
