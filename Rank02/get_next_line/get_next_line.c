#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int ft_strlen(const char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

char    *ft_substr(char *str, unsigned int start, int len)
{
    char    *substr;
    int     i = 0;
    int     j = 0;

    substr = (char *)malloc(sizeof(char) * (len + 1));
    if (!substr)
        return (NULL);
    while (str[i])
    {
        if (i >= start && j < len)
            substr[j++] = str[i];
        i++;
    }
    substr[j] = '\0';
    return (substr);
}

char    *ft_strchr(const char *s, int c)
{
    if (!c)
        return ((char *)s);
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (0);
}

char    *ft_strdup(const char *s)
{
    char    *dup;
    int     i = 0;

    dup = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
    if (!dup)
        return (NULL);
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *str;
    int     i = 0;
    int     j = 0;

    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
        return (0);
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }    
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
}

static char *read_n_append(int fd, char *buffer, char *remainder)
{
    int      bytes_read;
    char    *temp;

    bytes_read = 1;
    while (bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            return (NULL);
        if (bytes_read == 0)
            break ;
        buffer[bytes_read] = '\0';
        if (!remainder)
            remainder = ft_strdup("");
        temp = remainder;
        remainder = ft_strjoin(temp, buffer);
        free(temp);
        temp = NULL;
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (remainder);
}

static char *update_next_line(char *line)
{
    char    *remainder;
    int     idx = 0;

    while (line[idx] != '\0' && line[idx] != '\n')
        idx++;
    if (line[idx] == '\0' || line[1] == '\0')
        return (NULL);
    remainder = ft_substr(line, idx + 1, ft_strlen(line) - 1);
    if (*remainder == '\0')
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
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE * 1));
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


int main(void)
{
    int     fd;
    char    *str;

    fd = open("test.txt", O_RDWR);
    str = get_next_line(fd);
    while (str != NULL)
    {
        printf("%s", str);
        str = get_next_line(fd);
    }
    
    return (0);
}