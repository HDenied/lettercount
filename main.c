#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define N_VOWELS 5

int8_t _count(int64_t counters[], const char *f_path)
{
    int res = 0;
    int64_t len = 0;
    FILE *f = NULL;

    if ((f = fopen(f_path, "r")) == NULL)
    {
        printf("Can't open file %s\n", f_path);
        res = -1;
    }
    else
    {
        fseek(f, 0, SEEK_END);
        if ((len = (int64_t)ftell(f)) < 0)
        {
            printf("Error calculating max file size\n");
            res = -1;
            fclose(f);

        }
        else if (len == 0)
        {
            printf("File is empty\n");
            fclose(f);
        }
        else
        {
            fseek(f, 0, 0);
            char ch = '\0';
            while ((ch = fgetc(f)) != EOF)
            {
                switch (tolower(ch))
                {
                case 'a':
                {
                    counters[0]++;
                    break;
                }
                case 'e':
                {
                    counters[1]++;
                    break;
                }
                case 'i':
                {
                    counters[2]++;
                    break;
                }
                case 'o':
                {
                    counters[3]++;
                    break;
                }
                case 'u':
                {
                    counters[4]++;
                    break;
                }
                default:
                {
                    break;
                }
                }
            }

            fclose(f);
        }
    }

    return res;
}

int main(int argc, char **argv)
{
    int64_t counters[N_VOWELS] = {0};
    int res = 0;

    if (argc != 2)
    {
        printf("Please provide file path to inspect: e.g. letterc /file/path/fname\n");
        res = -1;
    }
    else
    {
        if (_count(counters, argv[1]) != -1)
        {
            printf("Num 'a'=%ld, num 'e'=%ld, num 'i'=%ld, num 'o'=%ld, num 'u'=%ld\n", counters[0],counters[1],counters[2],counters[3],counters[4]);
        }
        else
        {
            printf("Error processing file\n");
            res = -1;

        }
    }
    return res;
}