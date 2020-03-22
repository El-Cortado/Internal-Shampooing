// Legend has it that one could have used this vulenrability take control over the world.
// The path is under your control as well as some other memory in other parts of this program.
// Good luck. No googling!
// By the way: wchar, wcscpy and w*whatever* are exactly like their regular versions but supporting unicode. They are not the point here.

#include <wchar.h>

int canonicalize_path(wchar_t* path)
{
  wchar_t* p;
  wchar_t* q;
  wchar_t* previous_slash = NULL;
  wchar_t* current_slash  = NULL;
  wchar_t  ch;

  // If the path starts with a server name, skip it

  if ((path[0] == L'\\' || path[0] == L'/') &&
    (path[1] == L'\\' || path[1] == L'/'))
  {
    p = path+2;

    while (*p != L'\\' && *p != L'/') {
      if (*p == L'\0')
        return 0;
      p++;
    }

    p++;

    // make path point after the server name

    path = p;

    // make sure the server name is followed by a single slash

    if (path[0] == L'\\' || path[0] == L'/')
      return 0;
  }

  if (path[0] == L'\0')   // return if the path is empty
    return 1;

  // Iterate through the path and canonicalize "..\" and ".\"

  p = path;

  while (1) {
    if (*p == L'\\') {
      // we have a slash

      if (current_slash == p-1)   // don't allow consequtive slashes
        return 0;

      // store the locations of the current and previous slashes

      previous_slash = current_slash;
      current_slash = p;
    }
    else if (*p == L'.' && (current_slash == p-1 || p == path)) {
      // we have \. or ^.

      if (p[1] == L'.' && (p[2] == L'\\' || p[2] == L'\0')) {
        // we have a \..\, \..$, ^..\ or ^..$ sequence

        if (previous_slash == NULL)
          return 0;

        ch = p[2];

        wcscpy(previous_slash, &p[2]);

        if (ch == L'\0')
          return 1;

        current_slash = previous_slash;
        p = previous_slash;

        // find the slash before p
        q = p-1;
        
        while (*q != L'\\' && q != path)
          q--;

        if (*p == L'\\')
          previous_slash = q;
        else
          previous_slash = NULL;
      }
      else if (p[1] == L'\\') {
        // we have "\.\" or "^.\"
        if (current_slash != NULL) {
          wcscpy(current_slash, p+2);
          goto end_of_loop;
        }
        else { // current_slash == NULL
          wcscpy(p, p+2);
          goto end_of_loop;
        }
      }
      else if (p[1] != L'\0') {
        // we have \. or ^. followed by some other char

        if (current_slash != NULL) {
          p = current_slash;
        }
        *p = L'\0';
        return 1;
      }
    }

    p++;

end_of_loop:
    if (*p == L'\0')
      return 1;
  }
}
