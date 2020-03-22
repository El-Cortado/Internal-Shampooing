#include <string.h>

char *correct = ""; // REDACTED

int accept(char *name, char *password) {
  char buffer[500];
  int accepted = 0;
  strcpy(buffer, name);
  strcat(buffer, password);
  accepted = !strcmp(buffer, correct);

  return accepted;
}

