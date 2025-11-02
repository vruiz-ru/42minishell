/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:11:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:45:27 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../import/libft/lists/lists.h"
#include <stdbool.h>

typedef struct Environment_utils
{
	char	**parent_env;
	char	**static_env;
}	t_envs;

typedef struct Prompt_utils
{
	char	*display;
	char	*shell_name;
	char	*home_path;
	char	*current_wd;
	char	*last_wd;
}	t_prompt;

typedef struct Process_utils
{
	t_prompt	*prompt;
	t_envs		*envs;
	t_list		*tokens;
	pid_t		pid;
	char		*line;
	char		*last_arg;
	int			exit_status;
	bool		is_special;
	bool        is_variable;
}   t_process;

#endif