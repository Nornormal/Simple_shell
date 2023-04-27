#include "shell.h"

/**
 * add_aliasend - fun adds a node to the end of list.
 * @hd: pointer to the head of list.
 * @nme: name of the new alias.
 * @val: value of the new alias.
 *
 * Return: NULL - if error occur.
 *         Or - a pointer to the new node.
 */
alias_t *add_aliasend(alias_t **hd, char *nme, char *val)
{
	alias_t *n_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!n_node)
		return (NULL);

	n_node->nxt = NULL;
	n_node->nme = malloc(sizeof(char) * (_strlen(nme) + 1));
	if (!n_node->nme)
	{
		free(n_node);
		return (NULL);
	}
	n_node->val = val;
	_strcpy(n_node->nme, nme);

	if (*hd)
	{
		last = *hd;
		while (last->nxt != NULL)
			last = last->nxt;
		last->nxt = n_node;
	}
	else
		*hd = n_node;

	return (n_node);
}

/**
 * add_nodeend - fun add a node to the end of list.
 * @hd: pointer to the head of list.
 * @dir: directory path for the new node to contain.
 *
 * Return: NULL - if error occur.
 *         Or pointer to the new node.
 */
lst_t *add_nodeend(lst_t **hd, char *dir)
{
	lst_t *n_node = malloc(sizeof(lst_t));
	lst_t *last;

	if (!n_node)
		return (NULL);

	n_node->dir = dir;
	n_node->nxt = NULL;

	if (*hd)
	{
		last = *hd;
		while (last->nxt != NULL)
			last = last->nxt;
		last->nxt = n_node;
	}
	else
		*hd = n_node;

	return (n_node);
}

/**
 * fre_alias_lst - func frees a list.
 * @hd: head of list.
 */
void fre_alias_lst(alias_t *hd)
{
	alias_t *nxt;

	while (hd)
	{
		nxt = hd->nxt;
		free(hd->nme);
		free(hd->val);
		free(hd);
		hd = nxt;
	}
}

/**
 * fre_lst - func frees a list.
 * @hd: hd of the list.
 */
void free_lst(lst_t *hd)
{
	lst_t *nxt;

	while (hd)
	{
		nxt = hd->nxt;
		free(hd->dir);
		free(hd);
		hd = nxt;
	}
}
