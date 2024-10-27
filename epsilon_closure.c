#include<stdio.h>
#include<string.h>
char eclosure[20][20], states[10], sym[3] = "01", st[20][20];
int checkstate(char x[][20], int i, char y)
{
    int f = 0;
    for(int a=0;a<strlen(x[i]);a++)
    {
        if (x[i][a] == y)
        {
            f=1;
            break;
        }
    }
    if (f == 0)
        return 1;
    else
        return 0;
}

int main()
{
    int i, nt, k, j;
    char state, state1, input, state2;
    printf("\nEnter the no. of states: ");
    scanf("%d", &i);
    printf("\nEnter the no. of TRANSITIONS: ");
    scanf("%d", &nt);
    printf("\nEnter the states: ");
    scanf("%s", states);
    printf("\nEnter the transitions in the format 'state input nextState' (e.g., 'A 0 B'):\n");
    for(int j=0;j<nt;j++)
        scanf("%s", st[j]);
    for(i=0;i<strlen(states);i++)
    {
        k= 0;
        printf("\ne-closure of %c is {", states[i]);
        state = states[i];
        eclosure[i][k++] = state;
        eclosure[i][k++] = ',';
        for(j=0;j<nt;j++)
        {
            state1 = st[j][0], input = st[j][1], state2 = st[j][2];
            if(state == state1 && input =='e')
            {
            eclosure[i][k++] = state2;
            eclosure[i][k++] = ',';
            state = state2;
            }
        }
        eclosure[i][k++] = '\0';
        printf("%s}",eclosure[i]);
    }
    printf("\n");
    return 0;
}    