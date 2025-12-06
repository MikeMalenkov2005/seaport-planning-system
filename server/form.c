#include "form.h"

#include <stdlib.h>
#include <string.h>

static int from_hex(int x)
{
  return x > '9' ? x - 'A' + 10 : x - '0';
}

char *form_get(char *buffer, size_t size, const char *form, const char *key)
{
  size_t key_len, len;
  if (!buffer || !size || !form || !key) return NULL;
  key_len = strlen(key);
  while (form)
  {
    len = strcspn(form, "=");
    if (len == key_len && !strncmp(form, key, key_len))
    {
      form += len + 1;
      for (len = 0; len < size - 1 && *form && *form != '&'; ++len)
      {
        buffer[len] = *form++;
        if (buffer[len] == '%')
        {
          buffer[len] = from_hex(*form++) << 4;
          buffer[len] |= from_hex(*form++);
        }
      }
      buffer[len] = 0;
      return buffer;
    }
    else if ((form = strchr(form, '&'))) ++form;
  }
  return NULL;
}

size_t form_get_length(const char *form, const char *key)
{
  size_t key_len = 0, len = 0;
  if (!form || !key) return 0;
  key_len = strlen(key);
  while (form)
  {
    if (strcspn(form, "=") == key_len && !strncmp(form, key, key_len))
    {
      for (form += key_len + 1; *form && *form != '&'; ++len)
      {
        if (*form++ == '%') form += 2;
      }
      form = NULL;
    }
    else if ((form = strchr(form, '&'))) ++form;
  }
  return len;
}

char *form_next_key(const char *new_form)
{
  static char buffer[64];
  static const char *form;
  const char *next;
  if (new_form) form = new_form;
  if (!form || !(next = strchr(form, '='))) return NULL;
  if (form >= next) return (void*)(form = NULL);
  memcpy(memset(buffer, 0, sizeof(buffer)), form, next - form);
  form = strchr(next, '&');
  if (form) ++form;
  return buffer;
}

char *form_clone(const char *form, const char *key)
{
  size_t length = form_get_length(form, key);
  char *value = length ? malloc(length + 1) : NULL;
  if (value && !form_get(value, length + 1, form, key))
  {
    free(value);
    value = NULL;
  }
  return value;
}

