/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 10:49:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 22:27:53 by aghergut         ###   ########.fr       */
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

static char	**create_new(char **map, char *add_last)
{
	char    **new_map;
	int		i;

	new_map = malloc((ft_mapsize(map) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (free_partial(new_map, i), NULL);
	}
	new_map[i] = ft_strdup(add_last);
	if (new_map[i] == NULL)
		return (free_partial(new_map, i), NULL);
	new_map[i + 1] = NULL;
	return (new_map);
}

int	ft_mapitem_add(char ***map_ref, char *item)
{
	char	**map;
	char	**new;
	char	*to_add;

	if (!map_ref)
		return (0);
	map = *map_ref;
	to_add = ft_strdup(item);
	if (!to_add)
		return (0);
	if (map == NULL)
	{
		*map_ref = ft_mapnew(to_add);
		if (*map_ref == NULL)
			return (0);
		return (1);
	}
	new = create_new(map, to_add);
	if (new != NULL)
	{
		ft_mapfree(map);
		*map_ref = new;
		return (1);	
	}
	return (0);
}
