/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:16:51 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 19:51:00 by aghergut         ###   ########.fr       */
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

static int	copy_elements(char **map, char **new_map, size_t skip)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		if (i == skip)
		{
			i++;
			continue;
		}
		new_map[j] = ft_strdup(map[i]);
		if (!new_map[j])
		{
			free_partial(new_map, j);
			return (0);
		}
		j++;
		i++;

	}
	new_map[j] = NULL;
	return (1);
}

int	ft_mapitem_del(char ***map_ref, size_t del_idx)
{
	char	**new_map;
	char	**temp;
	size_t	length;

	if (!map_ref || !*map_ref)
		return (0);
	temp = *map_ref;
	length = ft_mapsize(temp);
	if (del_idx >= length)
		return (0);
	new_map = (char **)malloc(length * sizeof(char *));
	if (!new_map)
		return (0);
	if (!copy_elements(temp, new_map, del_idx))
		return (0);
	ft_mapfree(temp);
	*map_ref = new_map;
	return (1);
}

