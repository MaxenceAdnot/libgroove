/* use groove to play several files in a row and then exit */

#include "groove.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
        return 1;
    }
    groove_set_logging(GROOVE_LOG_INFO);
    GroovePlayer *player = groove_create_player();
    for (int i = 1; i < argc; i += 1) {
        char * filename = argv[i];
        GrooveFile * file = groove_open(filename);
        if (!file) {
            fprintf(stderr, "Not queuing %s\n", filename);
            continue;
        }
        groove_player_queue(player, file);
    }
    groove_player_play(player);
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = 50000000;
    int count;
    int last_count = 0;
    for (;;) {
        count = groove_player_count(player);
        if (count <= 0)
            break;
        if (count != last_count) {
            GrooveTag *artist_tag = groove_file_metadata_get(player->queue_head->file,
                    "artist", NULL, 0);
            GrooveTag *title_tag = groove_file_metadata_get(player->queue_head->file,
                    "title", NULL, 0);
            if (artist_tag && title_tag) {
                printf("Now playing: %s - %s\n", groove_tag_value(artist_tag),
                        groove_tag_value(title_tag));
            } else {
                printf("Now playing: %s\n", groove_file_filename(player->queue_head->file));
            }
        }
        last_count = count;
        nanosleep(&sleep_time, NULL);
    }
    printf("done\n");
    groove_destroy_player(player);
    return 0;
}
