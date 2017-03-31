#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int num_dirs(char* path)
{
    int dir_count = 0;
    struct dirent* dent;
    DIR* srcdir = opendir(path);

    if (srcdir == NULL)
    {
        perror("opendir");
        return -1;
    }

    while((dent = readdir(srcdir)) != NULL)
    {
        struct stat st;

        if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
            continue;

        if (fstatat(dirfd(srcdir), dent->d_name, &st, 0) < 0)
        {
            perror(dent->d_name);
            continue;
        }

        if (S_ISDIR(st.st_mode)) dir_count++;
    }
    closedir(srcdir);
    return dir_count;
}

int main(){
    num_dirs("./py_assignment2");
    return 0;
}
