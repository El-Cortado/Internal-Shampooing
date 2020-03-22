#include <string.h>

char *correct = ""; // REDACTED

int accept(char *name, char *password) {
  char buffer[500];
  int rejected = 1;
  if (strlen(name) + strlen(password) > sizeof(buffer)) {
    return !rejected;
  }
  strcpy(buffer, name);
  strcat(buffer, password);
  return !rejected;
}
