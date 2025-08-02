/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapadd_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 10:49:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:57:54 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

static void	free_partial(char **map, size_t from_index)
{
	if (!map)
		return;
	while (from_index > 0)
		free(map[--from_index]);
	free(map);
}

char	**ft_mapadd_item(char **map, char *item)
{
	char	**buff;
	size_t	length;
	size_t	i;

	if (!map)
		return (ft_mapnew(item));
	length = ft_mapsize(map);
	buff = malloc((length + 2) * sizeof(char *));
	if (!buff)
		return (NULL); 
	i = 0;
	while (map[i])
	{
		buff[i] = ft_strdup(map[i]);
		if (!buff[i])
			return (free_partial(buff, i), NULL);
		i++;
	}
	buff[i] = ft_strdup(item);
	if (buff[i] == NULL)
		return (free_partial(buff, i), NULL);
	buff[++i] = NULL;
	ft_mapfree(map);
	return (buff);
}
