#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  // store str at another place str_temp
  // read the i char of str_temp and assign it to n-i char of str
  if (str != NULL){
    int n = strlen(str);
    char dest[n+1];
    const char * src = str;
  
    char * str_temp = strncpy(dest, src, n+1);
    //printf("%s\n", str_temp);
    //str_temp[n] = '\0';
    if (n > 0) {
      for (int i = 0; i < n; i++) {
        str[i] = str_temp[n - 1 - i];
      }
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
