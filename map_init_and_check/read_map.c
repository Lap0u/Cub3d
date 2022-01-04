#include "../cub3d.h"
#include "../libft/libft.h"

t_map	*read_map(const char *filename)
{
	int		fd;
	char	*line;
	t_map	*head;
	t_map	*new;
	int		ret;

	ret = 0;
	if (check_filename(filename) != 1)
		message_error(8);
	fd = is_file(filename);
	if (fd < 0)
		message_error(6);
	ret = get_next_line(fd, &line);
	head = ft_lstnew(line);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		new = ft_lstnew(line);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

int	is_file(const char *filename)
{
	int	fd;

	fd = 0;
	fd = open(filename, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		message_error(7);
	}
	else
		fd = open(filename, O_RDONLY);
	return (fd);
}

int	check_filename(const char *filename)
{
	int			len;
	const char	*s;

	s = filename;
	len = ft_strlen(s);
	if (len < 5)
		return (0);
	if (s[len - 1] == 'r' && s[len - 2] == 'e' && s[len - 3] == 'b'
		&& s[len - 4] == '.')
	{
		if (s[len - 5] != '.' && s[len - 5] != '/')
			return (1);
	}
	return (0);
}
