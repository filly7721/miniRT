#include  <string.h> 
#include "miniRT.h"

#include <ctype.h> 

// rewrite isspace, strtod (or strtof) function 

char *remove_extra_spaces(const char *line)
{
    int i = 0, j = 0;
    char *removed;

    removed = ft_calloc(ft_strlen(line) + 1, sizeof(char));
    if (!removed)
        return (NULL);
    while (line[i])
    {
        if (!(isspace(line[i]) && (i == 0 || isspace(line[i - 1]))))
            removed[j++] = (isspace(line[i]) ? ' ' : line[i]);
        i++;
    }
    if (j > 0 && removed[j - 1] == ' ')
        removed[j - 1] = '\0';
    return (removed);
}


void free_split(char **split)
{ 
    int i = 0; 
    while (split[i] != NULL) 
    {
        free(split[i]); 
        i++; 
    } 
    free(split);
}
void parse_ambient(char* line, t_ambient* ambient)
{
    char** split;
    char** rgb_split;
    char* space_removed;
    char* rgb;

    space_removed = remove_extra_spaces(line);
    if (!space_removed)
        return;
    split = ft_split(space_removed, ' ');
    free(space_removed);
    if (!split)
    {
        printf("Error: ft_split returned NULL.\n");
        return;
    }

    if (!split[1] || !split[2])
    {
        printf("Error: Missing intensity or RGB values.\n");
        free_split(split);
        return;
    }
    ambient->intensity = strtod(split[1], NULL);
    printf("Intensity: %f\n", ambient->intensity);
    rgb = split[2];
    rgb_split = ft_split(rgb, ',');
    if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2])
    {
        printf("Error: Missing R, G, or B values.\n");
        free_split(split);
        free_split(rgb_split);
        return;
    }

    ambient->r = ft_atoi(rgb_split[0]);
    ambient->g = ft_atoi(rgb_split[1]);
    ambient->b = ft_atoi(rgb_split[2]);
    printf("R: %d, G: %d, B: %d\n", ambient->r, ambient->g, ambient->b);

    free_split(split);
    free_split(rgb_split);
    printf("Parsing completed successfully.\n");
}
