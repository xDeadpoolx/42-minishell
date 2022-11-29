/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/11/28 20:58:05 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (chdir(data->rl_decomp[1]) != 0)
		perror("cd");
}

void	ft_pwd(t_vault *data)
{
	char	*pwd;
	int		size_buffer;

	(void)data;
	size_buffer = 1;
	if (data->rl_decomp[1] != NULL)
		write(2, "pwd: too many arguments\n", 24);
	else
	{
		pwd = calloc(sizeof(char), size_buffer);
		while (getcwd(pwd, size_buffer) == NULL)
		{
			free (pwd);
			size_buffer++;
			pwd = calloc(sizeof(char), size_buffer);
		}
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
		free (pwd);
	}
}

void	ft_echo(t_vault *data)
{
	int		i;
	int		flag_n;
	int		len;
	int		j;
	int		k;
	int		first;

	i = 1;
	flag_n = 0;
	len = 0;
	first = 1;
	if (!(data->rl_decomp[i]))
		return ;
	else if (ft_strcmp(data->rl_decomp[i], "-n") == 0)
	{
		i = 2;
		flag_n = 1;
	}
	while (data->rl_decomp[i])
	{
		data->b_in->flag_clean_echo = 0;
		if (data->rl_decomp[i])
		{
			j = 0;
			k = 0;
			len = ft_strlen(data->rl_decomp[i]);
			data->b_in->echo_clean = ft_calloc(len + 1, sizeof(char));
			while (data->rl_decomp[i][j])
			{
				if (data->rl_decomp[i][j] == '\"')
				{
					data->b_in->flag_clean_echo = 1;
					j++;
				}
				data->b_in->echo_clean[k] = data->rl_decomp[i][j];
				j++;
				k++;
			}
			if (data->b_in->flag_clean_echo == 1)
			{
				free (data->rl_decomp[i]);
				data->rl_decomp[i] = ft_strdup(data->b_in->echo_clean);
				free (data->b_in->echo_clean);
				ft_putstr_fd(data->rl_decomp[i], 1);
			}
			else
			{
				if (first == 1)
				{
					ft_putstr_fd(data->rl_decomp[i], 1);
					first = 0;
				}
				else
				{
					ft_putstr_fd(" ", 1);
					ft_putstr_fd(data->rl_decomp[i], 1);
				}
			}
		}
		else
			break ;
		i++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
		return ;
}

void	ft_exit(t_vault *data)
{
	//prevoir les free en fonction d'ou on est dans le programme lors de exit
	(void) data;
	// if (data->b_in->env_unset)
	// 	free_dbl_ptr((void **)data->b_in->env_unset);
	// if (data->b_in->env_export)
	// 	free_dbl_ptr((void **)data->b_in->env_export);
	// if (data->b_in->env_order)
	// 	free_dbl_ptr((void **)data->b_in->env_order);
//	free_dbl_ptr((void **)data->rl_decomp);
	exit (0);
}

void	ft_env(t_vault *data, int env)
{
	int	i;

	i = 0;
	if (env == 1)
	{
		while (data->env[i])
		{
			ft_putstr_fd(data->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	else if (env == 2)
	{
		while (data->b_in->env_order[i])
		{
			ft_putstr_fd(data->b_in->env_order[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	return ;
}
