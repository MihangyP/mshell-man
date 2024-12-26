/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:01:30 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 19:50:47 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char *var, char **env)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
		{
			return (env[i] + var_len + 1);
		}
		i++;
	}
	return (NULL);
}

int	get_var_name_length(char *str)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*expand_env_var(char *var_name, char **env)
{
	int		var_len;
	char	*var;
	char	*value;

	var_len = get_var_name_length(var_name);
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	ft_strlcpy(var, var_name, (var_len + 1));
	value = get_env_value(var, env);
	free(var);
	if (value == NULL)
		return (NULL);
	return (value);
}

char	*expand_special_char(char *str, char **env, int *i, int exit_code)
{
	char	*result;
	char	*var_value;

	result = NULL;
	var_value = NULL;
	if (str[*i + 1] == '?')
	{
		result = ft_itoa(exit_code);
		(*i)++;
	}
	else
	{
		result = NULL;
		var_value = expand_env_var(str + *i + 1, env);
		result = (char *)ft_calloc((ft_strlen(var_value) + 3), sizeof(char));
		result[0] = '"';
		ft_strlcpy(result + 1, var_value, ft_strlen(var_value) + 1);
		result[ft_strlen(var_value) + 1] = '"';
		*i += get_var_name_length(str + *i + 1);
	}
	return (result);
}

char	*special_expand_char(char *str, char **env, int exit_code)
{
	char	*result;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == '$'
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			tmp = expand_special_char(str, env, &i, exit_code);
			result = str_append(result, tmp);
			free(tmp);
		}
		else
			result = char_append(result, str[i]);
	}
	return (result);
}
