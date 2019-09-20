#define stdout 1
#define true 1
#define false 0

int stringlen(const char * s);
int my_file_puts(int fd, const char * s);

int main()
{
    my_file_puts(1, "Hello World!\n");
}

// max of 2^31 chars
int stringlen(const char * s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

// Write string s to file fd.
// File must be less than 2^31 B (~ 2.14 GB).
int my_file_puts(int fd, const char * s)
{
    int bytes_written = 0;
    int total_bytes_written;
    int len = stringlen(s);

    // write() not gauranteed to write whole buffer to file.
    // Use a while loop to keep trying until an error occurs or the whole buffer
    // gets written.
    while (true)
    {
        bytes_written = write(fd, s, len);
        if (bytes_written == -1)
        {
            // write resulted in error, pass up to main.
            return -1;
        }
        total_bytes_written += bytes_written;
        if (total_bytes_written == len)
        {
            // successfully wrote all of s
            return total_bytes_written;
        }
    }
}
