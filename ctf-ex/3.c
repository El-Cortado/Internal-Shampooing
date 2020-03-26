#include <string.h>

char *correct = ""; // REDACTED

int accept(char *name, char *password) {
  char buffer[500];
  int accepted = 0;

  size_t max_pass_size = sizeof(buffer) - strlen(name) - 1;

  if (strlen(password) > max_pass_size) {
    return accepted;
  }
  strcpy(buffer, name);
  strcat(buffer, password);
  return !strcmp(buffer, correct);
}
