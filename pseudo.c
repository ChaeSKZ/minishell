/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:12:16 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/28 12:21:13 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	quote(char *str)
{
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			//nouvelle ligne
		if (str[i] == '$')
			//expand
		if (str[i] == '"' && check_end_quote(str + i, '"'))
		{
			while (str[i] && satr[i] != '"')  //line = Double
			{
				if (str[i] == '$')
					expand(str);
				i++;
			}
			//generate line
		}
		if (str[i] == '\'' && check_end_quote(str + i, '\''))
		{
			//line = Single
		}
	}

}

/*
line = Salut ca va "oui ca va $HOME\n"

tab[0] = Salut;
tab[1] = ca;
tab[2] = va;
tab[3] = oui ca va [home_path]; + retour a la ligne

--------------------------------------------------------------

line = Salut ca ca 'Oui et toi $HOME\n'

tab[0] = Salut;
tab[1] = ca;
tab[2] = va;
tab[3] = oui ca va $HOME\n;
*/
