		t_vals	*first;
	t_vals	*second;
	int		hdk_nb;

	hdk_nb = 0;
	first = (t_vals *)lexer->content;
	if (first->token == V_EOF)
		return (0);
	if (first->token == V_PIPE)
		return (err("syntax error near unexpected token `", first->val, 0));
	second = (t_vals *) lexer->next->content;
	while (first->token != V_EOF)
	{
		if (first->token == V_HDK)
			hdk_nb++;
		if ((first->token == V_APP || first->token == V_IN_RDIR || first->token == V_OUT_RDIR || first->token == V_HDK) && (second->token != V_STR))
			return (err("syntax error near unexpected token`", second->val, 0));
		if (first->token == V_STR)
		{
			if (check_str_look(first->val))
				return (1);
		}
		if (first->token == V_PIPE && (second->token == V_EOF || second->token == V_PIPE))
			return (err("syntax error near unexpected token `", first->val, 0));
		if (second->token == V_EOF)
			break ;
		lexer = lexer->next;
		first = (t_vals *)lexer->content;
		second = (t_vals *)lexer->next->content;
	}
	if (hdk_nb > 16)
		err("maximum here-document count exceeded ", "`<<", 2);
	return (0);