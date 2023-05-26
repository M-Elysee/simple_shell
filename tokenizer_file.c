#include "main.h"
/**
* strtow_func - splits a string into words. Repeat delimiters are ignored
* @str_var: the input string
* @d_var: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow_func(char *str_var, char *d_var)
{
	int i_var, j_var, k_var, m_var, numwords_var = 0;
	char **s_var;

	if (str_var == NULL || str_var[0] == 0)
		return (NULL);
	if (!d_var)
		d_var = " ";
	for (i_var = 0; str_var[i_var] != '\0'; i_var++)
		if (!is_delim_func(str_var[i_var], d_var)
				&& (is_delim_func(str_var[i_var + 1], d_var)
					|| !str_var[i_var + 1]))
			numwords_var++;

	if (numwords_var == 0)
		return (NULL);
	s_var = malloc((1 + numwords_var) * sizeof(char *));
	if (!s_var)
		return (NULL);
	for (i_var = 0, j_var = 0; j_var < numwords_var; j_var++)
	{
		while (is_delim_func(str_var[i_var], d_var))
			i_var++;
		k_var = 0;
		while (!is_delim_func(str_var[i_var + k_var], d_var)
				&& str_var[i_var + k_var])
			k_var++;
		s_var[j_var] = malloc((k_var + 1) * sizeof(char));
		if (!s_var[j_var])
		{
			for (k_var = 0; k_var < j_var; k_var++)
				free(s_var[k_var]);
			free(s_var);
			return (NULL);
		}
		for (m_var = 0; m_var < k_var; m_var++)
			s_var[j_var][m_var] = str_var[i_var++];
		s_var[j_var][m_var] = 0;
	}
	s_var[j_var] = NULL;
	return (s_var);
}
/**
* strtow2_func - splits a string into words
* @str_var: the input string
* @d_var: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2_func(char *str_var, char d_var)
{
	int i_var, j_var, k_var, m_var, numwords_var = 0;
	char **s_var;

	if (str_var == NULL || str_var[0] == 0)
		return (NULL);
	for (i_var = 0; str_var[i_var] != '\0'; i_var++)
		if ((str_var[i_var] != d_var
					&& str_var[i_var + 1] == d_var)
				|| (str_var[i_var] != d_var
				     && !str_var[i_var + 1])
				|| str_var[i_var + 1] == d_var)
			numwords_var++;
	if (numwords_var == 0)
		return (NULL);
	s_var = malloc((1 + numwords_var) * sizeof(char *));
	if (!s_var)
		return (NULL);
	for (i_var = 0, j_var = 0; j_var < numwords_var; j_var++)
	{
		while (str_var[i_var] == d_var && str_var[i_var] != d_var)
			i_var++;
		k_var = 0;
		while (str_var[i_var + k_var] !=
				d_var && str_var[i_var + k_var]
				&& str_var[i_var + k_var] != d_var)
			k_var++;
		s_var[j_var] = malloc((k_var + 1) * sizeof(char));
		if (!s_var[j_var])
		{
			for (k_var = 0; k_var < j_var; k_var++)
				free(s_var[k_var]);
			free(s_var);
			return (NULL);
		}
		for (m_var = 0; m_var < k_var; m_var++)
			s_var[j_var][m_var] = str_var[i_var++];
		s_var[j_var][m_var] = 0;
	}
	s_var[j_var] = NULL;
	return (s_var);
}

