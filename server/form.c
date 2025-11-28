#include "form.h"

#include <string.h>

char *form_get(char *buffer, size_t size, const char *form, const char *key)
{
  size_t key_len, entry_len;
  if (!buffer || !size || !form || !key) return NULL;
  key_len = strlen(key);
  while (form)
  {
    entry_len = strcspn(form, "=");
    if (entry_len == key_len && !strncmp(form, key, key_len))
    {
      form += entry_len;
      if (*form) entry_len = strcspn(++form, "&");
      else entry_len = 0;
      memset(buffer, 0, size--);
      return strncpy(buffer, form, size > entry_len ? entry_len : size);
    }
    else if ((form = strchr(form, '&'))) ++form;
  }
  return NULL;
}

size_t form_get_length(const char *form, const char *key)
{
  size_t key_len;
  if (!form || !key) return 0;
  key_len = strlen(key);
  while (form)
  {
    if (strcspn(form, "=") == key_len && !strncmp(form, key, key_len))
    {
      form += key_len;
      return *form ? strcspn(++form, "&") : 0;
    }
    else if ((form = strchr(form, '&'))) ++form;
  }
  return 0;
}

