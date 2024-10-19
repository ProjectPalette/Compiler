#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_STATES 10000
#define INPUTS 2

int ninputs;
int dfa[MAX_STATES][INPUTS][MAX_STATES] = {0};
bool state[MAX_STATES] = {false};
int go[MAX_STATES][INPUTS] = {0};
int arr[MAX_STATES] = {0};

int main() {
    int st, fin, in, rel;
    int f[10], p, q, r, i, j, k, x = 0, curr1, flag;

    printf("Follow the one based indexing\n");
    printf("Enter the number of states: ");
    scanf("%d", &st);

    printf("Enter number of final states: ");
    scanf("%d", &fin);
    printf("Enter final states: ");
    for (i = 0; i < fin; i++) {
        scanf("%d", &f[i]);
    }

    printf("Enter the number of rules according to NFA: ");
    scanf("%d", &rel);
    printf("Define transition rule as \"initial state input symbol final state\":\n");
    for (i = 0; i < rel; i++) {
        scanf("%d %d %d", &p, &q, &r);
        dfa[p][q][r] = 1;  // Update transition rules
    }

    printf("Enter initial state: ");
    scanf("%d", &in);
    in = 1 << in;  // Convert to bit representation

    // Process the DFA states
    for (i = 0; i < st; i++) {
        for (j = 0; j < INPUTS; j++) {
            int stf = 0;
            for (k = 0; k < st; k++) {
                if (dfa[i][j][k] == 1) {
                    stf |= (1 << k);
                }
            }
            go[1 << i][j] = stf;  // Record transitions
            if (!state[stf]) {
                arr[x++] = stf;
                state[stf] = true;
            }
        }
    }

    // Process new states
    for (i = 0; i < x; i++) {
        for (j = 0; j < INPUTS; j++) {
            int new_state = 0;
            for (k = 0; k < st; k++) {
                if (arr[i] & (1 << k)) {
                    new_state |= go[1 << k][j];
                }
            }
            if (!state[new_state]) {
                arr[x++] = new_state;
                state[new_state] = true;
            }
        }
    }

    // Output distinct states
    printf("The total number of distinct states are:\nSTATE 0 1\n");
    for (i = 0; i < MAX_STATES; i++) {
        if (state[i]) {
            int y = 0;
            if (i == 0) {
                printf("q0 ");
            } else {
                for (j = 0; j < st; j++) {
                    if (i & (1 << j)) {
                        printf("q%d ", j);
                        y |= (1 << j);
                    }
                }
            }
            printf(" %d %d\n", go[y][0], go[y][1]);
        }
    }

    // Process strings
    for (int m = 0; m < 3; m++) {  // Example with 3 strings
        char str[1000];
        printf("\nEnter string: ");
        scanf("%s", str);
        curr1 = in;
        flag = 0;

        printf("String takes the following path -->\n");
        printf("%d-", curr1);
        for (i = 0; str[i]; i++) {
            curr1 = go[curr1][str[i] - '0'];
            printf("%d-", curr1);
        }

        printf("\nFinal state - %d\n", curr1);
        for (i = 0; i < fin; i++) {
            if (curr1 & (1 << f[i])) {
                flag = 1;
                break;
            }
        }
        printf(flag ? "String Accepted\n" : "String Rejected\n");
    }

    return 0;
}
