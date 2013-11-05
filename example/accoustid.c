/* accoustid scanner */

#include "groove.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
        return 1;
    }

    groove_init();
    atexit(groove_finish);
    groove_set_logging(GROOVE_LOG_INFO);

    struct GroovePlaylist *playlist = groove_playlist_create();

    for (int i = 1; i < argc; i += 1) {
        char * filename = argv[i];
        struct GrooveFile * file = groove_file_open(filename);
        if (!file) {
            fprintf(stderr, "Unable to open %s\n", filename);
            continue;
        }
        groove_playlist_insert(playlist, file, 1.0, NULL);
    }

    struct GrooveChromaprinter *chromaprinter = groove_chromaprinter_create();
    groove_chromaprinter_attach(chromaprinter, playlist);

    struct GrooveChromaprinterInfo info;
    while (groove_chromaprinter_info_get(chromaprinter, &info, 1) == 1) {
        if (info.item) {
            fprintf(stderr, "\nfile complete: %s\n", info.item->file->filename);
            fprintf(stderr, "suggested gain: %.2f dB, sample peak: %f, duration: %fs\n",
                    loudness_to_replaygain(info.loudness),
                    info.peak,
                    info.duration);
        } else {
            fprintf(stderr, "\nAll files complete.\n");
            fprintf(stderr, "suggested gain: %.2f dB, sample peak: %f, duration: %fs\n",
                    loudness_to_replaygain(info.loudness),
                    info.peak,
                    info.duration);
            break;
        }
    }

    struct GroovePlaylistItem *item = playlist->head;
    while (item) {
        struct GrooveFile *file = item->file;
        struct GroovePlaylistItem *next = item->next;
        groove_playlist_remove(playlist, item);
        groove_file_close(file);
        item = next;
    }

    groove_loudness_detector_detach(detector);
    groove_loudness_detector_destroy(detector);
    groove_playlist_destroy(playlist);

    return 0;
}