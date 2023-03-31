#include <stdio.h>
#include <string.h>
void filter(char str[], char invalid[]) {
    int len_1 = strlen(str);
    int len_2 = strlen(invalid);
    for (int i = 0; i < len_1; i++) {
        for (int j = 0; j < len_2; j++) {
            if (invalid[i] == str[j]) {
                for (int k = j; k < len_1 - 1; k++) {

                    str[k] = str[k + 1];
                }
                str[len_1] = '\0';
                len_1--;

            }
        }
    }
    str[len_1] = '\0';
}

int main () {
    char word[] = "fun fun fun!!!";
    char word1[] = "frightened";

    filter(word, word1);
    printf("%s\n", word1);
    printf("%s\n", word);
    return 0;
}