#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

size_t len(const char *string)
{ // não conta o \0
	size_t i = 0;
	while (string[i] != '\0')
		i++;
	return i;
}

void substr(const char *string, size_t start, size_t end, char *out)
{
	memcpy(out, string + start, (start + end) * sizeof(char));
	out[end] = '\0';
}

int comp(const char *str1, const char *str2)
{
	size_t s1 = len(str1);
	size_t s2 = len(str2);
	if (s1 != s2)
	{
		return 0;
	}

	size_t i = 0;
	for (; i < s1; ++i)
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}

int index_char(const char *string, char c)
{
	size_t i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return i;
		i++;
	}
	return -1;
}

int find_index(const char *string, const char *text, int start_index)
{
	int index = -1;
	int found = 0;
	size_t i = start_index;
	size_t j = 0;

	while (1)
	{
		if (string[i] == text[j])
		{
			if (!found)
				index = i;

			found = 1;
			j++;
		}
		else
		{
			found = 0;
			index = -1;
			j = 0;
		}

		if (text[j] == '\0')
		{
			break;
		}

		if (string[i] == '\0')
		{
			return -1;
		}
		i++;
	}
	return index;
}

int find_last(const char *string, const char *text)
{
	int i = 0;
	int prev_index = -1;
	do
	{
		prev_index = i;
		i = find_index(string, text, i + 1);
	} while (i != -1);

	return prev_index;
}

int find(const char *string, const char *text)
{
	return find_index(string, text, 0);
}

char *ltrim(const char *string)
{
	size_t i = 0;
	while (string[i] == ' ')
		i++;

	size_t l = len(string);
	char *temp = malloc(l - i);
	substr(string, i, l, temp);
	return temp;
}

char *rtrim(const char *string)
{
	size_t l = len(string);
	size_t i = l - 1;
	while (string[i] == ' ')
		i--;

	char *temp = malloc(i + 1);
	substr(string, 0, i + 1, temp);
	return temp;
}

char *trim(const char *string)
{
	char *temp1 = ltrim(string);
	char *temp2 = rtrim(temp1);
	free(temp1);
	return temp2;
}

int char_is_num(const char c)
{
	return c >= '0' && c <= '9';
}

int char_to_int(const char c)
{
	if (char_is_num(c))
	{
		return c - '0';
	}
	return -1;
}

// implementar sinal
int to_int(const char *string, int *error)
{
	size_t l = len(string);
	int place = 1;
	int i = 0;
	int res = 0;
	int j = l - 1;
	for (; i < l && j >= 0; i++, j--, place *= 10)
	{
		if (!char_is_num(string[i]))
		{
			*error = 1;
			return 0;
		}

		res += char_to_int(string[j]) * place;
	}
	*error = 0;
	return res;
}

// isso ignora o sinal
// testar se a flag error é setada qndo deve
double to_double(const char *string, int *error)
{
	int dot = find(string, ".");
	if (dot == -1)
		return to_int(string, error);
	else if (dot == 0)
	{
		*error = 1;
		return 0;
	}
	size_t l = len(string);

	int place = 1;
	int i = 0;
	int res = 0;
	int j = l - 1;
	// double d = 0;
	for (; i < l && j >= 0; i++, j--, place *= 10)
	{
		if (string[i] == '.')
		{
			// d = place;
			place /= 10;
			continue;
		}
		else if (!char_is_num(string[i]))
		{
			*error = 1;
			return 0;
		}

		res += char_to_int(string[j]) * place;
	}
	*error = 0;
	// printf("K %d %f \n", res,  res/d);
	// char *buffer_numerator = malloc(dot);
	// substr(string, 0, dot, buffer_numerator);

	// char *buffer_decimal = malloc(l - dot);
	// substr(string, dot, l, buffer_decimal);

	// printf("~%s~%s\n", buffer_numerator, buffer_decimal);

	// int numerator = to_int(buffer_numerator, error);
	// int decimal = to_int(buffer_decimal, error);
	// free(numerator);
	// free(buffer_decimal);
	// if (error)
	// 	return 0;

	return res;
}

char digit_to_char(int digit, int *error)
{
	if (digit < 0 || digit > 9)
	{
		*error = 1;
		return 0;
	}

	return digit - (0 - '0');
}

int char_is_upper(const char c)
{
	return c >= 'A' && c <= 'Z';
}

int char_is_lower(const char c)
{
	return c >= 'a' && c <= 'z';
}

int char_is_alpha(const char c)
{
	return char_is_lower(c) || char_is_upper(c);
}

char char_to_upper(const char c)
{
	if (char_is_alpha(c))
	{
		return c - 32;
	}
	return c;
}

char char_to_lower(const char c)
{
	if (char_is_alpha(c))
	{
		return c + 32;
	}
	return c;
}

char *to_upper(const char *string)
{
	size_t l = len(string);
	char *temp = malloc(l + 1);

	size_t i = 0;
	for (; i < l; i++)
		temp[i] = char_is_lower(string[i]) ? char_to_upper(string[i]) : string[i];

	temp[l] = '\0';
	return temp;
}

char *to_lower(const char *string)
{
	size_t l = len(string);
	char *temp = malloc(l + 1);

	size_t i = 0;
	for (; i < l; i++)
		temp[i] = char_is_upper(string[i]) ? char_to_lower(string[i]) : string[i];

	temp[l] = '\0';
	return temp;
}

int main(int argc, char **args)
{
	const char *text = "Hello world";
	size_t size = len(text);
	assert(size == 11);

	assert(comp("Hello", "Hello"));
	assert(!comp("Hello", "Helloo"));
	assert(!comp("Hello", "Hell1"));

	char *buffer = (char *)malloc(5);
	substr(text, 1, 4, buffer);

	assert(comp(buffer, "ello"));
	free(buffer);

	const char *s = "   oi haha  ";
	char *l_trimmed = ltrim(s);
	char *r_trimmed = rtrim(s);
	char *trimmed = trim(s);
	assert(comp(l_trimmed, "oi haha  "));
	assert(comp(r_trimmed, "   oi haha"));
	assert(comp(trimmed, "oi haha"));
	free(l_trimmed);
	free(r_trimmed);
	free(trimmed);

	assert(index_char(text, 'w') == 6);
	assert(find(text, "world") == 6);
	assert(find("worl", "world") == -1);
	assert(find("the smell is nice", "smell") == 4);
	assert(find(text, "worl d") == -1);
	assert(find_last("foo baz fiz baz buz", "baz") == 12);

	assert(char_is_num('0'));
	assert(char_is_num('1'));
	assert(char_is_num('9'));
	assert(!char_is_num('a'));

	assert(char_to_int('0') == 0);
	assert(char_to_int('1') == 1);
	assert(char_to_int('9') == 9);
	assert(char_to_int('a') == -1);

	assert(char_is_alpha('a'));
	assert(char_is_alpha('z'));
	assert(char_is_alpha('A'));
	assert(char_is_alpha('Z'));
	assert(!char_is_alpha('1'));

	assert(char_to_upper('c') == 'C');
	assert(char_to_lower('D') == 'd');

	char *foo = to_upper("9 Oi ff.");
	char *baz = to_lower("9 Oi ff.");
	assert(comp(foo, "9 OI FF."));
	assert(comp(baz, "9 oi ff."));
	free(foo);
	free(baz);

	int error;
	assert(digit_to_char(8, &error) == '8');
	assert(to_int("2439", &error) == 2439);

	return 0;
}