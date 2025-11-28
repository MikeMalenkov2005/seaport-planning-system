#include "base64.h"

#include <stdio.h>
#include <string.h>

static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(char *buffer, size_t size, const char *plain) {
  int octets = 0;
  char triple[3];
  char *out = buffer;
  if (size * 3 / 4 <= strlen(plain)) return NULL;
  while (*plain)
  {
    triple[octets++] = *plain++;
    if(octets == 3)
    {
      *out++ = table[triple[0] >> 2];
      *out++ = table[((triple[0] & 0x03) << 4) + (triple[1] >> 4)];
      *out++ = table[((triple[1] & 0x0f) << 2) + (triple[2] >> 6)];
      *out++ = table[triple[2] & 0x3f];
      octets = 0;
    }
  }
  if (octets)
  {
    *out++ = table[triple[0] >> 2];
    if(octets == 1)
    {
      *out++ = table[(triple[0] & 0x03) << 4];
      *out++ = '=';
    }
    else
    {
      *out++ = table[((triple[0] & 0x03) << 4) + (triple[1] >> 4)];
      *out++ = table[(triple[1] & 0x0f) << 2];
    }
    *out++ = '=';
  }
  *out++ = '\0';
  return buffer;
}

char *base64_decode(char *buffer, size_t size, const char *encoded)
{
  int count = 0;
  unsigned char chars[4];
  char *out = buffer;
  if (size <= strlen(encoded) * 3 / 4) return NULL;
  while (*encoded)
  {
    chars[count] = 0;
    while (chars[count] < 64 && table[chars[count]] != *encoded) ++chars[count];
    ++encoded;
    if (++count == 4)
    {
      *out++ = (chars[0] << 2) + (chars[1] >> 4);
      if(chars[2] != 64) *out++ = (chars[1] << 4) + (chars[2] >> 2);
      if(chars[3] != 64) *out++ = (chars[2] << 6) + chars[3];
      count = 0;
    }
  }
  *out++ = '\0';
  return buffer;
}

