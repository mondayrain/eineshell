#include <cstring>

/* Split a string into an array of tokens.
 * Will write the tokens into the token_buf,
 * and return the # of tokens.
 */
int split_into_tokens(char *str, const char* delimiter, char* token_buf[]) {
    int i = 0;
    token_buf[i] = strtok(str, delimiter);

    while(token_buf[i]!=NULL)
    {
        token_buf[++i] = strtok(NULL, delimiter);
    }

    return i;
}
