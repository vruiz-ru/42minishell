/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 22:50:25 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

/* Valida si el identificador es válido (ej: VAR_1 es ok, 1VAR no) */
static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	// El primer caracter debe ser letra o '_'
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	// Los siguientes pueden ser alfanuméricos o '_'
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Lógica interna para añadir/actualizar la variable */
static void	export_logic(t_process *process, char *arg)
{
	char	*name;
	char	*eq_pos;
	int		idx;

	// Obtenemos el nombre para buscarlo
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
		name = ft_substr(arg, 0, eq_pos - arg);
	else
		name = ft_strdup(arg);

	// Buscamos si ya existe en parent_env
	idx = ft_mapitem_index(process->envs->parent_env, name);
	
	// Si existe y tenemos valor nuevo, reemplazamos
	if (idx >= 0 && eq_pos) 
		ft_mapitem_replace(&process->envs->parent_env, arg, idx);
	// Si no existe, lo añadimos
	else if (idx < 0)
		ft_mapitem_add(&process->envs->parent_env, arg);
	
	free(name);
}

/* Función principal */
int	ft_export(t_process *process, t_cmd *cmd)
{
	int	i;
	int	status;

	status = 0;
	// Si no hay argumentos, deberíamos listar (opcional, aquí no hacemos nada y retornamos 0)
	if (!cmd->args[1])
		return (0);

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1; // Marcamos error pero seguimos con los siguientes
		}
		else
		{
			export_logic(process, cmd->args[i]);
		}
		i++;
	}
	return (status);
}



/*
#include "builtins.h"

static void	update(char ***map, char *var)
{
	int 	env_idx;
	
	env_idx = ft_mapitem_index(*map, var);
	if (env_idx < 0)
		return ;
	if (!ft_mapitem_replace(map, var, env_idx))
		return ;
	return ;
}

static void	transfer(t_process *process, char *var)
{
	char	*get_var;
	int		idx;
	
	idx = ft_mapitem_index(process->envs->static_env, var);
	if (idx < 0)
		return ;
	get_var = ft_strdup(process->envs->static_env[idx]);
	if (!get_var)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (ft_mapitem_index(process->envs->parent_env, get_var) < 0 && \
		!ft_mapitem_add(&process->envs->parent_env, get_var))
	{
		free(get_var);
		return ;
	}
	ft_mapitem_del(&process->envs->static_env, idx);
	free(get_var);
	return ;
}

int ft_export(t_process *process, t_cmd *cmd)
{
	char	**local;
	char	*line;
	int		idx;

	(void)cmd;
	local = process->envs->static_env;
	line = ft_construct(process->tokens, NULL);
	idx = ft_mapitem_index(local, line);
	if (!ft_strchr(line, '='))
	{
		if (idx < 0)
			return (1);
		if (ft_mapitem_index(process->envs->parent_env, local[idx]) < 0)
		{
			if (!ft_mapitem_add(&process->envs->parent_env, local[idx]))
				return (perror("malloc"), exit(EXIT_FAILURE), free(line), 1);
		}
		return (free(line), 1);
	}
	update(&process->envs->parent_env, line);
	update(&process->envs->static_env, line);
	if (ft_mapitem_index(process->envs->parent_env, line) < 0 && idx < 0 && \
		!ft_mapitem_add(&process->envs->parent_env, line))
		return (perror("malloc"), exit(EXIT_FAILURE), free(line), 1);
	transfer(process, line);
	return (free(line), 0);
}*/
