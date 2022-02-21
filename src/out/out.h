#pragma once

#include <openutils/sstring/sstring.h>
#include <sys/stat.h>

typedef struct out_wcat out_wcat;
struct out_wcat
{
    sstring *_M_content;
    sstring *_M_locations;
    size_t *_M_content_length;
    size_t _M_len;
};

int file_exists(const char *loc);
int init_wcat(out_wcat *data, const char **locs, size_t len);
int read_wcat(out_wcat *data);
size_t print_wcat(out_wcat *data, int print_line, int print_tab);
int free_wcat(out_wcat *data);

int file_exists(const char *loc)
{
    if (!loc)
        return false;
    FILE *fptr = fopen(loc, "rb");
    if (!fptr)
        return false;
    fclose(fptr);
    struct stat st;
    if (stat(loc, &st) != 0)
        return false;
    if (S_ISDIR(st.st_mode) == 0)
        return true;
    fprintf(stderr, "wcat: `%s` is a directory.\r\n", loc);
    exit(1);
}

int init_wcat(out_wcat *data, const char **locs, size_t len)
{
    if (!locs || len == 0 || !data)
        return false;
    data->_M_content = (sstring *)calloc(len, sizeof(sstring));
    data->_M_locations = (sstring *)calloc(len, sizeof(sstring));
    data->_M_content_length = (size_t *)calloc(len, sizeof(size_t));
    data->_M_len = len;
    if (!data->_M_content || !data->_M_locations)
    {
        fprintf(stderr, "wcat: could not allocate heap memory\r\nreport this issue: <>\r\n");
        exit(1);
    }
    for (size_t i = 0; i < len; i++)
    {
        if (init_sstr(&data->_M_content[i], 1) == false || init_sstr(&data->_M_locations[i], 1) == false)
        {
            fprintf(stderr, "wcat: could not initialize sstring:\r\nreport this issue: <https://www.github.com/Dark-CodeX/sstring/issues>\r\n");
            exit(1);
        }
        if (file_exists(locs[i]) == false)
        {
            fprintf(stderr, "wcat: could not find the file `%s`\r\n", locs[i]);
            exit(1);
        }
        data->_M_locations[i].set(&data->_M_locations[i], locs[i]);
    }
    return true;
}

int read_wcat(out_wcat *data)
{
    if (!data)
        return false;
    for (size_t i = 0; i < data->_M_len; i++)
        data->_M_content_length[i] = data->_M_content[i].open_binary(&data->_M_content[i], data->_M_locations[i].c_str(&data->_M_locations[i]));
    return true;
}

size_t print_wcat(out_wcat *data, int print_line, int print_tab)
{
    if (!data)
        return 0;
    size_t stdout_len = 0;
    fflush(stdout);
    for (size_t i = 0; i < data->_M_len; i++)
    {
        stdout_len += fprintf(stdout, "\r\n%s:\r\n", data->_M_locations[i].c_str(&data->_M_locations[i]));
        size_t ln = 1, x = 0;
        if (print_line == true)
            stdout_len += fprintf(stdout, "     %lu  ", ln++);
        while (x != data->_M_content_length[i])
        {
            if (print_tab == true)
            {
                if (((__str__ *)data->_M_content[i].str)->src[x] == '\t')
                {
                    stdout_len += fprintf(stdout, "^I");
                    x++;
                    continue;
                }
            }
            stdout_len += fprintf(stdout, "%c", ((__str__ *)data->_M_content[i].str)->src[x++]);
            if (print_line == true)
                if (((__str__ *)data->_M_content[i].str)->src[x - 1] == '\n')
                    stdout_len += fprintf(stdout, "     %lu  ", ln++);
        }
    }
    fflush(stdout);
    return stdout_len;
}

int free_wcat(out_wcat *data)
{
    if (!data)
        return false;
    for (size_t i = 0; i < data->_M_len; i++)
    {
        if (data->_M_content[i].destructor(&data->_M_content[i]) == false || data->_M_locations[i].destructor(&data->_M_locations[i]) == false)
        {
            fprintf(stderr, "wcat: could not de-allocate heap memory\r\nreport this issue: <>\r\n");
            exit(1);
        }
    }
    free(data->_M_content);
    free(data->_M_locations);
    free(data->_M_content_length);
    data->_M_len = 0;
    return true;
}
