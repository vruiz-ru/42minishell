/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:45:52 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 12:52:35 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static char	*failed_malloc(void)
{
	write(1, "Failed malloc!\n", sizeof("Failed malloc!\n") - 1);
	return (NULL);
}

static int	token_length(char *str, const char *delim)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(delim, str[i]))
			break ;
		i++;
	}
	return (i);
}

static char	*get_token(char *cpy, const char *delim)
{
	char	*token;
	int		size;
	int		i;

	if (!cpy || !*cpy)
		return (NULL);
	while (*cpy && ft_strchr(delim, *cpy))
		cpy++;
	if (!*cpy)
		return (NULL);
	size = token_length(cpy, delim);
	token = malloc(size + 1);
	if (!token)
		return (failed_malloc());
	i = -1;
	while (++i < size)
		token[i] = cpy[i];
	token[i] = '\0';
	return (token);
}

static char	*trim_static(char *cpy, const char *delim)
{
	char	*new;
	int		size;
	int		i;

	size = 0;
	while (cpy[size] && ft_strchr(delim, cpy[size]))
		size++;
	while (cpy[size] && !ft_strchr(delim, cpy[size]))
		size++;
	while (cpy[size] && ft_strchr(delim, cpy[size]))
		size++;
	if (!cpy[size])
		return (free(cpy), NULL);
	new = malloc((size + 1) * sizeof(char));		// + 1 = char NULL
	if (!new)
		return (failed_malloc());
	i = 0;
	while (cpy[size])
		new[i++] = cpy[size++];
	new[i] = '\0';
	free(cpy);
	return (new);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char *cpy = NULL;
	char		*token;

	if (str == NULL && cpy == NULL)
		return (NULL);
	if (delim == NULL || !*delim)
		return (NULL);
	if (str)
	{
		free(cpy);
		cpy = ft_strdup(str);
		if (!cpy)
			return (failed_malloc());
	}
	token = get_token(cpy, delim);
	cpy = trim_static(cpy, delim);
	return (token);
}
