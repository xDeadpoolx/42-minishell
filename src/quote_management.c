/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/01 20:43:41 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_str_quote(t_vault *data)
{
	int		i;

	i = 0;
	data->quote_in->begin = 0;
	data->quote_in->len = 1;
	while (data->read_line[i])
	{
		data->quote_in->spc_count = 0;
		if (data->read_line[i] == ' ')
		{
			while (data->read_line[i] == ' ')
				i++;
			data->quote_in->begin = i;
		}
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			data->quote_in->quote = data->read_line[i];
			i++;
			while ((data->read_line[i] != data->quote_in->quote
					|| data->read_line[i + 1] > 32)
				&& data->read_line[i])
			{
				if (data->read_line[i] == data->quote_in->quote)
				{
					while (data->read_line[i] && data->read_line[i] != ' ')
					{
						data->quote_in->len++;
						i++;
					}
					break ;
				}
				if (data->read_line[i] == ' ')
					data->quote_in->spc_count++;
				data->quote_in->len++;
				i++;
			}
			data->quote_in->len++;
			decomposer_array_to_replace(data, i);
		}
		i++;
	}
}

void	decomposer_array_to_replace(t_vault *data, int end)
{
	int		i;
	int		j;

	if (data->rl_decomp_i != 0)
		i = data->rl_decomp_i;
	else
		i = 0;
	while (data->rl_decomp[i])
	{
		j = 0;
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == data->quote_in->quote)
			{
				replace_decomposer_array(data, end, &i);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	replace_decomposer_array(t_vault *data, int end, int *i)
{
	int	j;

	j = 0;
	free(data->rl_decomp[*i]);
	data->rl_decomp[*i]
		= ft_calloc(sizeof(char), data->quote_in->len + 1);
	while (data->quote_in->begin <= end)
	{
		data->rl_decomp[*i][j]
			= data->read_line[data->quote_in->begin];
		data->quote_in->begin++;
		j++;
	}
	(*i)++;
	data->rl_decomp_i = *i;
	if (ft_strchr(data->rl_decomp[*i - 1], ' ') != NULL)
		find_decomposer_to_switch(data, *i);
}

void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;

	next_array = to_switch + data->quote_in->spc_count;
	actual_array = to_switch;
	while (data->rl_decomp[next_array])
	{
		data->rl_decomp[actual_array] = data->rl_decomp[next_array];
		next_array++;
		actual_array++;
	}
	data->rl_decomp[actual_array] = "\0";
}

// 'je"tu"'il
// "coucou">'toi'