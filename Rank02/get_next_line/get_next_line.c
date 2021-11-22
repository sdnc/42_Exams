#include <unistd.h>

static char *read_n_append(int fd, char *buffer, char *remainder)
{
    int     bytes_read;
    char    *temp;

    bytes_read = 1;
    while (bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            return (NULL);
        if (bytes_read == 0)
            break ;
        buffer[bytes_read] + '\0';
        if (!remainder)
            remainder = ft_strdup("");
        temp = remainder;
        remainder = ft_strjoin(temp, remainder);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (remainder);
}

static char *update_next_line(char *line)
{
    int         idx = 0;
    static char *remainder;

    while (line[idx] != '\0' && line[idx] != '\n')
        idx++;
    if (line[idx] == '\0' || line[1] == '\0')
        return (NULL);
    remainder = ft_substr(line, idx + 1, ft_strlen(line) - idx);
    if (!(*remainder))
    {
        free(remainder);
        remainder = NULL;
    }
    line[idx + 1] = '\0';
    return (remainder);
    }

char    *get_next_line(int fd)
{
    char        *line;
    char        *buffer;
    static char *remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (0);
    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    line = read_n_append(fd, buffer, remainder);
    free(buffer);
    buffer = NULL;
    if (!line)
        return (NULL);
    remainder = update_next_line(line);
    return (line);
}