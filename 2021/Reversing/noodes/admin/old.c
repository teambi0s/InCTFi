#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#include <dirent.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

static const char alphabet[] =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789";

static const char solver[] = "dfxXdf5FcwL\\adsUddPedd}UdflZafn~af9TmflZcwlZafilddKYafM^dfxRmfENcwENddXmdf\\Raff\\df{xddL[adeiadJkdfW5cwiTdd7Ydf^zadkKcw:jadeudfU=dfj~dd[}dfM9cwp7dfhnmfTjcwTjddyQdfftdd5UdfIxddGydfgnddjYdfqZcwqPcwfpdflLddUoaf~vddWqafZJdf=Tcw{Zmf|Fcw|FddnkadUgdfj\\dfr^dd]SdfGJcwwJdfFtcwzFcwXVcwE|cwkPddWMdd]iadu:cwFRad\\IafXrafNxmfElcwElafJvafx9df4|dd8mmfH~cwH~mfT~cwT~afkFafvpdfj5dd}SafVRmfFpmfP|mfThmfNLmf5ZcwFpcwP|cw\\xcw=7cwyncwG|cwThcwNLcw\\pcwI^cw5ZcwOT";

static const int alphabetSize = sizeof(alphabet) - 1;

void ignore_me_init_buffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void kill_on_timeout(int sig) {
  if (sig == SIGALRM) {
  	printf("[!] Anti DoS Signal. Patch me out for testing.");
    _exit(0);
  }
}

void ignore_me_init_signal() {
	signal(SIGALRM, kill_on_timeout);
	alarm(60);
}

void
rmtree(const char path[])
{
    size_t path_len;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;

    stat(path, &stat_path);

    if (S_ISDIR(stat_path.st_mode) == 0) {
        exit(-1);
    }
    if ((dir = opendir(path)) == NULL) {
        exit(-1);
    }

    path_len = strlen(path);
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        full_path = calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);

        stat(full_path, &stat_entry);

        if (S_ISDIR(stat_entry.st_mode) != 0) {
            rmtree(full_path);
            continue;
        }

        unlink(full_path);
        free(full_path);
    }
    
    rmdir(path);
    closedir(dir);
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void initialize_dir(char *filename) {
    struct stat st = {0};

    if (stat(filename, &st) == -1) {
        mkdir(filename, 0700);
    } else {
        printf("Something wrong!\n");
        exit(-1);
    }


    char finname[60];
    char temp[3];
        
    for (int i = 0; i < alphabetSize; i++) {
        for (int j = 0; j < alphabetSize; j++) {
            memset(finname, 0, sizeof finname);
            temp[0] = alphabet[i];
            temp[1] = alphabet[j];

            strcat(finname, filename);
            strcat(finname, temp);
            
            if ((j % 2) == 0) {
                mkdir(finname, 0700);
            } else {
                FILE* fp = fopen(finname, "w");
                fputs(temp, fp);
                fclose(fp);
            }
        }
    }
}

void child_stuff(char *path) {
    char buf[1024];
    char finname[60];
    struct stat st = {0};

    char temp[4];
    FILE *FP_LIST[100];

    int ctr = 0;
    int fp_count = 0;

    printf("\n Enter the correct input : \n");
    fgets(buf, 1024, stdin);
    

    while (ctr < strlen(buf)) {
        memset(finname, 0, sizeof finname);

        char ch[2];
        ch[0] = buf[ctr++];
        int choice = atoi(ch);

        switch (choice)
        {
        case 1:
            // OPEN
            temp[0] = buf[ctr++];
            temp[1] = buf[ctr++];
            temp[2] = '\0';
        
            strcat(finname, path);
            strcat(finname, temp);
            
            if (is_regular_file(finname)) {
                FP_LIST[fp_count++] = fopen(finname, "a+");
                //printf("File opened\n");
            } else {
                //printf("dir in 1");
                goto error;
            }
            break;
        case 2:
            // close open FILE ptr
            if (fp_count == 0) {
                //printf("no fp to close in 2");
                goto error;
            } 
            fclose(FP_LIST[fp_count - 1]);
            fp_count--;
            break;
        case 3:
            // read to a FP
            if (fp_count == 0) {
                //printf("no fp to read in 3");
                goto error;
            }
            fputs("Wrong", FP_LIST[fp_count - 1]);
            break;
        case 4:
            // delete a file
            temp[0] = buf[ctr++];
            temp[1] = buf[ctr++];
            temp[2] = '\0';
        
            strcat(finname, path);
            strcat(finname, temp);
            
            if (is_regular_file(finname)) {
                unlink(finname);
            } else {
                //printf("regular file instead of dir in delete file in 4");
                goto error;
            }
            break;
        case 5:
            // attributes
            temp[0] = buf[ctr++];
            temp[1] = buf[ctr++];
            temp[2] = '\0';
        
            strcat(finname, path);
            strcat(finname, temp);

            //printf("chmod done\n");
            chmod(finname, S_IRUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH);
            break;        
        case 6:
            // delete a directory
            temp[0] = buf[ctr++];
            temp[1] = buf[ctr++];
            temp[2] = '\0';
        
            strcat(finname, path);
            strcat(finname, temp);

            if (is_regular_file(finname)) {
                //printf("regular file instead of dir in delete dir");
                goto error;
            } else {
                //printf("%s\n", finname);
                rmdir(finname);
                //printf("Directory deleted\n");
            }
            break;
        case 7:
            // create a new directory
            temp[0] = buf[ctr++];
            temp[1] = buf[ctr++];
            temp[2] = '\0';
        
            strcat(finname, path);
            strcat(finname, temp);
            
            if (stat(finname, &st) == -1) {
                mkdir(finname, 0700);
            } else {
                //printf("existing file in create dir");
                goto error;
            }

            break;
        case 8:
            printf("Exiting..\n");
            exit(0);
        default:
            //printf("unknown number : %c : %d", ch[0], ctr);
            goto error;
            break;
        }
    }

error:
    printf("Error!\n");
    exit(-1);
}

int main(int argc, char const *argv[])
{

    int length, i = 0;
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];
    char flagbuf[1000];
    int idx = 0;

   	ignore_me_init_buffering();
	ignore_me_init_signal();
    fd = inotify_init();

    if (fd < 0)
        perror("inotify_init");
    
    initialize_dir("/tmp/chall/");

    wd = inotify_add_watch(fd, "/tmp/chall/", IN_CREATE | IN_ACCESS | IN_ATTRIB | IN_DELETE | IN_CLOSE_WRITE | IN_CLOSE_NOWRITE | IN_MODIFY | IN_OPEN);

    pid_t p = fork();
    if (p == 0) {
        child_stuff("/tmp/chall/");
    }
    
    int status;
    if ( waitpid(p, &status, 0) == -1 ) {
        perror("waitpid failed\n");
        goto to_exit;
    }

    const int es = WEXITSTATUS(status);
    printf("%d", es);
    if (es != 0) {
        printf("Wrong!\n");
        goto to_exit;
    }
    
    printf("verifying....\n");

    length = read(fd, buffer, EVENT_BUF_LEN);

    if (length < 0)
    {
        perror("read");
    }

    while (i < length)
    {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];
        if (event->len)
        {
            if (event->mask & IN_CREATE)
            {
                if (event->mask & IN_ISDIR)
                {
                    flagbuf[idx++] = 'c';
                    flagbuf[idx++] = 'd';
                    flagbuf[idx++] = event->name[0] + 4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
                else
                {
                    flagbuf[idx++] = 'c';
                    flagbuf[idx++] = 'f';
                    flagbuf[idx++] = event->name[0] +  4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
            }
            else if (event->mask & IN_DELETE)
            {
                if (event->mask & IN_ISDIR)
                {
                    flagbuf[idx++] = 'd';
                    flagbuf[idx++] = 'd';
                    flagbuf[idx++] = event->name[0] +  4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
                else
                {
                    flagbuf[idx++] = 'd';
                    flagbuf[idx++] = 'f';
                    flagbuf[idx++] = event->name[0] +  4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
            }
            else if (event->mask & IN_CLOSE_WRITE) 
            {
                flagbuf[idx++] = 'c';
                flagbuf[idx++] = 'w';
                flagbuf[idx++] = event->name[0] +  4;
                flagbuf[idx++] = event->name[1] +  4;
            }
            else if (event->mask & IN_ACCESS) 
            {
                flagbuf[idx++] = 'a';
                flagbuf[idx++] = 'c';
                flagbuf[idx++] = event->name[0] +  4;
                flagbuf[idx++] = event->name[1] +  4;
            }
            else if (event->mask & IN_ATTRIB) 
            {
                if (event->mask & IN_ISDIR)
                {
                    flagbuf[idx++] = 'a';
                    flagbuf[idx++] = 'd';
                    flagbuf[idx++] = event->name[0] +  4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
                else
                {
                    flagbuf[idx++] = 'a';
                    flagbuf[idx++] = 'f';
                    flagbuf[idx++] = event->name[0] +  4;
                    flagbuf[idx++] = event->name[1] +  4;
                }
            }
            else if (event->mask & IN_MODIFY) 
            {
                flagbuf[idx++] = 'm';
                flagbuf[idx++] = 'f';
                flagbuf[idx++] = event->name[0] +  4;
                flagbuf[idx++] = event->name[1] +  4;
            }
        }
        flagbuf[idx++] = ' ';
        i += EVENT_SIZE + event->len;
    }

    printf("%s\n", flagbuf);
    
    if (strcmp(flagbuf, solver) == 0) {
        printf("Congrats!\n");
        printf("inctf{https://store.steampowered.com/app/1017900/Age_of_Empires_Definitive_Edition/}\n");
    } else {
        printf(":(\n");
    }

to_exit:
    inotify_rm_watch(fd, wd);
    close(fd);
    
    rmtree("/tmp/chall/");

    return 0;
}

