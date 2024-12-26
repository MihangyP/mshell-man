/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:54:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:01:19 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	should_expand(char *str, int i, int in_single_quotes)
{
	return (str[i] == '$' && !in_single_quotes
		&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'));
}

int	handle_quotes_expander(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
	{
		*in_single_quotes = !(*in_single_quotes);
		return (1);
	}
	else if (c == '"' && !(*in_single_quotes))
	{
		*in_double_quotes = !(*in_double_quotes);
		return (1);
	}
	return (0);
}

void	expand_char(t_expand_context *ctx)
{
	char	*tmp;

	tmp = expand_special_char(ctx->str, ctx->env, ctx->i, ctx->exit_code);
	ctx->result->value = str_append(ctx->result->value, tmp);
	if (!ctx->in_double_quotes && ctx->result->prev != '=')
		ctx->result->create_token = 1;
	free(tmp);
}

void	handle_non_expand_char(t_expand_context *ctx, char *str, int i)
{
	if (is_ignored_dollar(str[i], str[i + 1], ctx->in_double_quotes,
			ctx->in_single_quotes) == 1)
		ctx->result->value = char_append(ctx->result->value, str[i]);
}

t_expand_result	expand_token(char *str, char **env, int exit_status)
{
	t_expand_result		result;
	t_expand_context	ctx;
	int					i;

	init_expand_vars(&result, &i);
	init_expand_context(&ctx, &result, exit_status);
	ctx.str = str;
	ctx.env = env;
	ctx.i = &i;
	while (str[++i])
	{
		if (handle_quotes_expander(str[i], &ctx.in_single_quotes,
				&ctx.in_double_quotes) == 1)
			handle_non_expand_char(&ctx, str, i);
		else if (should_expand(str, i, ctx.in_single_quotes))
			expand_char(&ctx);
		else
			handle_non_expand_char(&ctx, str, i);
		ctx.result->prev = str[i];
	}
	result.value = finalize_result(result.value);
	return (result);
}
