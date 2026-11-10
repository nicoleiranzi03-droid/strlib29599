#include <stddef.h>

/* ---------- helpers (names differ from string.h / ctype.h) ---------- */

static size_t my_len(const char *s)
{
    const char *p = s;
    while (*p != '\0')
        p++;
    return (size_t)(p - s);
}

static char my_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (char)(c - 'A' + 'a');
    return c;
}

/* ---------- 1. str_find_char ---------- */

const char *str_find_char(const char *s, char c)
{
    while (*s != '\0') {
        if (*s == c)
            return s;
        s++;
    }
    /* s now points at the terminating '\0' */
    if (c == '\0')
        return s;
    return NULL;
}

/* ---------- 2. str_reverse ---------- */

void str_reverse(char *s)
{
    char *end = s;
    while (*end != '\0')
        end++;
    if (end == s)
        return;          /* empty string */
    end--;               /* last real character */
    while (s < end) {
        char tmp = *s;
        *s = *end;
        *end = tmp;
        s++;
        end--;
    }
}

/* ---------- 3. str_compare_ci ---------- */

int str_compare_ci(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        char ca = my_lower(*a);
        char cb = my_lower(*b);
        if (ca != cb)
            return (ca < cb) ? -1 : 1;
        a++;
        b++;
    }
    if (*a != '\0')
        return 1;        /* b ended first */
    if (*b != '\0')
        return -1;       /* a ended first */
    return 0;
}

/* ---------- 4. str_copy_bounded ---------- */

size_t str_copy_bounded(char *dst, const char *src, size_t size)
{
    size_t len = my_len(src);
    if (size > 0) {
        size_t n = (len < size - 1) ? len : size - 1;
        size_t i;
        for (i = 0; i < n; i++)
            dst[i] = src[i];
        dst[n] = '\0';
    }
    return len;
}

/* ---------- 5. str_find_sub ---------- */

const char *str_find_sub(const char *hay, const char *needle)
{
    for (;; hay++) {
        const char *h = hay;
        const char *n = needle;
        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }
        if (*n == '\0')
            return hay;  /* whole needle matched (also: empty needle) */
        if (*hay == '\0')
            return NULL; /* tried every start, including the end */
    }
}

/* ---------- 6. str_squeeze ---------- */

size_t str_squeeze(char *s)
{
    char *r = s;         /* read pointer  */
    char *w = s;         /* write pointer */
    int pending_space = 0;

    while (*r != '\0') {
        if (*r == ' ' || *r == '\t') {
            if (w != s)  /* ignore leading whitespace */
                pending_space = 1;
        } else {
            if (pending_space) {
                *w++ = ' ';
                pending_space = 0;
            }
            *w++ = *r;
        }
        r++;
    }
    *w = '\0';           /* trailing whitespace was never written */
    return (size_t)(w - s);
}

/* ---------- 7. str_split ---------- */

int str_split(char *s, char delim, char *fields[], int max_fields)
{
    int count = 1;       /* k delimiters -> k + 1 fields */
    char *p;

    if (max_fields > 0)
        fields[0] = s;

    for (p = s; *p != '\0'; p++) {
        if (*p == delim) {
            *p = '\0';
            if (count < max_fields)
                fields[count] = p + 1;
            count++;
        }
    }
    return count;
}

/* ---------- your own experiments (ignored by the autograder) ---------- */
#ifndef AUTOGRADER
#include <stdio.h>

int main(void)
{
    char a[] = "  hello   world  ";
    char b[] = "red,green,blue";
    char *f[5];
    int n, i;

    printf("%zu [%s]\n", str_squeeze(a), a);
    n = str_split(b, ',', f, 5);
    for (i = 0; i < n; i++)
        printf("f[%d]=%s\n", i, f[i]);
    return 0;
}
#endif
