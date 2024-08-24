#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
typedef struct node
{
    int val;
    struct node *next;
} node;
int is_empty(node *stack)
{
    if (stack->val == (int)'$' && stack->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int top(node *stack)
{
    while (stack->next != NULL)
    {
        stack = stack->next;
    }
    return stack->val;
}
node *create_empty_stack()
{
    node *stack = (node *)malloc(sizeof(node));
    stack->next = NULL;
    stack->val = (int)'$';
}
void push(node *stack, int x)
{
    while (stack->next != NULL)
    {
        stack = stack->next;
    }
    stack->next = (node *)malloc(sizeof(node));
    stack = stack->next;
    stack->next = NULL;
    stack->val = x;
}
int pop(node *stack)
{
    if (is_empty(stack))
    {
        return;
    }
    while (stack->next->next != NULL)
    {
        stack = stack->next;
    }
    int x = stack->next->val;
    free(stack->next);
    stack->next = NULL;
    return x;
}
int priority(char c, int n)
{
    char ops[7][3] = {{'$', '0', '0'}, {'+', '2', '2'}, {'-', '2', '2'}, {'*', '3', '3'}, {'/', '3', '3'}, {'^', '5', '4'}, {'(', '6', '1'}};
    int i = 0;
    while (ops[i][0] != c)
    {
        i++;
    }
    return ops[i][n];
}
int length(node *stack)
{
    int count = 0;
    while (!is_empty(stack) && stack != NULL)
    {
        count++;
        stack = stack->next;
    }
    return count;
}
int operate(int y, int z, char c)
{
    switch (c)
    {
    case '+':
        return y+z;
        break;
    case '-':
        return y-z;
        break;
    case '*':
        return y*z;
        break;
    case '/':
        return y/z;
        break;
    case '^':
        return pow(y,z);
        break;
    }
}
int main()
{
    node *num = create_empty_stack();
    node *op = create_empty_stack();
    char str[100];
    scanf("%s", str);
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        while (str[i] >= '0' && str[i] <= '9')
        {
            x *= 10;
            x += ((int)str[i] - 48);
            i++;
        }
        push(num, x);
        if (length(num) == 1)
        {
            push(op, str[i]);
            continue;
        }
        else if(str[i] == '#'){
            while (top(op) != '$')
            {
                int y = pop(num);
                int z = pop(num);
                push(num, operate(y, z, pop(op)));
            }
        }
        else if (str[i] == ')')
        {
            while (top(op) != '(')
            {
                int y = pop(num);
                int z = pop(num);
                push(num, operate(y, z, pop(op)));
            }
            pop(op);
        }
        else
        {
            while (priority(top(op), 2) > priority(str[i], 1))
            {
                int y = pop(num);
                int z = pop(num);
                push(num,operate(y,z,pop(op)));
            }
        }
    }
    // node *temp = num;
    // temp = temp->next;
    // while (temp != NULL)
    // {
    //     printf("%d\n", temp->val);
    // }
    printf("%d",top(num));
    return 0;
}