#include <string.h>

char *correct = ""; // REDACTED

int accept(char *name, char *password) {
  char buffer[500];
  int accepted = 0;
  size_t len1 = strlen(name);
  size_t len2 = strlen(password);

  if (strlen(name) + strlen(password) > sizeof(buffer)) {
    return accepted;
  }
  memcpy(buffer, name, len1);
  memcpy(&buffer[len1], password, len2);
  return !memcmp(buffer, correct, len1 + len2);
}

