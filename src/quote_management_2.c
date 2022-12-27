/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:49:24 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/27 10:56:25 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je cherche la ligne à remplacer dans rl_dec en trouvant la quote
	prioritaire que j'ai trouvé dans readline
*/
void	find_decomposer_array_to_replace(t_vault *data, int end)
{
	int		i;
	int		j;

	i = data->quote->last_replace;
	while (data->rl_dec[i])
	{
		j = 0;
		while (data->rl_dec[i][j])
		{
			if (data->rl_dec[i][j] == data->quote->quote_priority)
			{
				replace_decomposer_array(data, end, &i);
				data->quote->last_replace = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

/*
	Je free la ligne de rl_dec à remplacer, je la calloc de la taille de
	la nouvelle ligne qui va la remplacer et je me balade dans readline, de
	begin jusqu'a end, pour remplir la nouvelle ligne.
*/
void	replace_decomposer_array(t_vault *data, int end, int *i)
{
	int	j;

	j = 0;
	free(data->rl_dec[*i]);
	data->rl_dec[*i]
		= ft_calloc(sizeof(char), data->quote->len_of_replacement + 1);
	while (data->quote->begin < end)
	{
		data->rl_dec[*i][j]
			= data->read_line[data->quote->begin];
		data->quote->begin++;
		j++;
	}
	(*i)++;
	if (ft_strchr(data->rl_dec[*i - 1], ' ') != NULL)
		find_decomposer_to_switch(data, *i);
}

/*
	Je décalle les éléments du tableau. spc_count va me servir à savoir
	combien de ligne je vais devoir sauter dans rl_dec pour commencer
	mon remplacement.
*/
void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;

	next_array = to_switch + data->spc_count;
	actual_array = to_switch;
	while (data->rl_dec[next_array])
	{
		free (data->rl_dec[actual_array]);
		data->rl_dec[actual_array] = ft_strdup(data->rl_dec[next_array]);
		next_array++;
		actual_array++;
	}
	if (data->rl_dec[actual_array])
	{
		while (data->rl_dec[actual_array])
		{
			data->rl_dec[actual_array][0] = '\0';
			actual_array++;
		}
	}
}
