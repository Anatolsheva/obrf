#include <stdio.h>

struct element
{
    int dana;
    struct element * pop;

};

typedef struct element elem;

int empty(elem * stos)
{
    if(stos == NULL)
    {
        return 1; /// 1 - oznacza ze stos jest pusty
    }

    return 0; /// 0 -stos a elementy
}

void push(elem **stos, int wartosc)
{
    elem *nowy=(elem*)malloc(sizeof(elem));
    nowy->pop=*stos;
    *stos=nowy;
    nowy->dana=wartosc;
}

void print(elem *stos)
{
    while(stos)
    {
        printf(" %d\n",stos->dana);
        stos=stos->pop;
    }
}

void pop(elem **stos, int *wartosc)
{
    elem *pom=*stos;
    *stos=(*stos)->pop;
    *wartosc=pom->dana;
    free(pom);
}

void inicjuj(elem **stos)
{
    *stos=NULL;
}

void czysc(elem **stos)
{
    int tmp;
    while(*stos)
    {
        pop(stos,&tmp);
    }
}

int main()
{
    elem *szczyt;
    inicjuj(&szczyt);
    char oper=' ';
        char oper2=' ';
        int prze=0;
    int arg;
    int d1,d2;

    while(oper != 'q')
    {
        prze=0;
           oper2 = getc(stdin);
           if(oper2=='-' || oper2=='+')
           {
               prze=1;
           }
             ungetc(oper2,stdin);
        if(scanf("%d",&arg))
        {
            push(&szczyt,arg);
        }
        else
        {

           if(prze)
           {
               oper=oper2;
               getc(stdin);
           }
           else
           {
              oper = getc(stdin);
              getc(stdin);
           }

  printf("%c\n",oper);
            switch(oper)
            {
            case '+':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    push(&szczyt,d1);
                    break;
                }
                pop(&szczyt,&d2);
                push(&szczyt,d1+d2);

            }
            break;

            case '-':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    push(&szczyt,d1);
                    break;
                }
                pop(&szczyt,&d2);
                push(&szczyt,d1-d2);

            }
            break;

            case '*':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    push(&szczyt,d1);
                    break;
                }
                pop(&szczyt,&d2);
                push(&szczyt,d1*d2);

            }
            break;

            case '/':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    push(&szczyt,d1);
                    break;
                }
                pop(&szczyt,&d2);

                if(d2==0)
                {
                    printf("dzilenie przez 0!!\n");
                    push(&szczyt,d2);
                    push(&szczyt,d1);
                }

                push(&szczyt,d1/d2);

            }
            break;
            case 'P':
            {
                pop(&szczyt,&d2);
            }
            break;
            case 'c':
            {
                czysc(&szczyt);
            }
            break;
            case 'r':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    push(&szczyt,d1);
                    break;
                }
                pop(&szczyt,&d2);
                push(&szczyt,d1);
                push(&szczyt,d2);

            }
            break;
            case 'd':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                pop(&szczyt,&d1);

                push(&szczyt,d1);
                push(&szczyt,d1);

            }
            break;
            case 'p':
            {
                if(empty(szczyt))
                {
                    printf("Uwaga stos pusty!!\n");
                    break;
                }
                printf("%d ",szczyt->dana );
            }
            break;
            case 'f':
            {
                print(szczyt);
            }
            break;
            }

        }
    }
    return (0);
}
