/*
 * mplib - a library that enables you to edit ID3 tags
 *
 * Copyright (c) 2001,2002,2003,2004,2005,2006 Stefan Podkowinski
 *               2006                          Michal Kowalczuk
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the author nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "mplib.h"

#ifndef __MPLIB_S_H
#define __MPLIB_S_H

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif


__BEGIN_DECLS


/************************************/
/*              Members             */
/************************************/

/* Bitrates br_[version]_[layer] ) */
const static int br_1_1[16] = { -1, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0 };
const static int br_1_2[16] = { -1, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 0 };
const static int br_1_3[16] = { -1, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0 };
const static int br_2_1[16] = { -1, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0 };
const static int br_2_2[16] = { -1, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 0 };
const static int br_2_3[16] = { -1, 8, 16, 24, 32, 64, 80, 56, 64, 128, 160, 112, 128, 256, 320, 0 };

#define GLL 148
const static char *genre_list[GLL] = 
{ "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz",
  "Metal", "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno",
  "Industrial", "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno",
  "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental",
  "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "Alternative Rock", "Bass", "Soul", "Punk",
  "Space", "Meditative", "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
  "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", 
  "Cult", "Gangsta Rap", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret",
  "New Wave", "Psychedelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk",
  "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk/Rock", 
  "National Folk", "Swing", "Fast-Fusion", "Bebob", "Latin", "Revival", "Celtic", "Bluegrass",
  "Avantgarde", "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock",
  "Big Band", "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera",
  "Chamber Music", "Sonata", "Symphony", "Booty Bass", "Primus", "Porn Groove", "Satire", "Slow Jam",
  "Club", "Tango", "Samba", "Folklore", "Ballad", "Power Ballad", "Rythmic Soul", "Freestyle",
  "Duet", "Punk Rock", "Drum Solo", "A Cappella", "Euro-House", "Dance Hall", "Goa", "Drum & Bass",
  "Club-House", "Hardcore", "Terror", "Indie", "BritPop", "Negerpunk", "Polsk Punk", "Beat",
  "Christian Gangsta Rap", "Heavy Metal", "Black Metal", "Crossover", "Contemporary Christian",
  "Christian Rock", "Merengue", "Salsa", "Trash Metal", "Anime", "JPop", "Synthpop" };


/************************************/
/*               Macros             */
/************************************/

#define frame_is_read_only(id3v2_frame__) ((id3v2_frame__->status_flag >> 4) & 1)
#define frame_preserve_on_tag_altered(id3v2_frame__) ((id3v2_frame__->status_flag >> 6) & 1)
#define frame_preserve_on_file_altered(id3v2_frame__) ((id3v2_frame__->status_flag >> 5) & 1)

#define frame_has_group_information(id3v2_frame__) ((id3v2_frame__->format_flag >> 6) & 1)
#define frame_is_compressed(id3v2_frame__) ((id3v2_frame__->format_flag >> 3) & 1)
#define frame_is_encrypted(id3v2_frame__) ((id3v2_frame__->format_flag >> 2) & 1)
#define frame_is_unsynchronised(id3v2_frame__) ((id3v2_frame__->format_flag >> 1) & 1)
#define frame_has_data_length_indicator(id3v2_frame__) (id3v2_frame__->format_flag & 1)


/************************************/
/*         Static functions         */
/************************************/


/* Gets the v1/v2 tag */
static id3v1_tag *id3v1_get_tag(size_t (*read_func)(void *, size_t, void *),
		off_t (*lseek_func)(off_t, int, void *),
		void *arg);
static id3v2_tag *id3v2_get_tag(size_t (*read_func)(void *, size_t, void *),
		off_t (*lseek_func)(off_t, int, void *),
		void *arg);

/* Adds v1/v2 Tag to file */
static int id3v1_add_tag(int, id3v1_tag*);
static int id3v2_add_tag(int, id3v2_tag*, id3v2_tag*);

/* Removes v1/v2 Tag from file */
static int id3v1_del_tag(int);
static int id3v2_del_tag(int, id3v2_tag*);

/* Truncates the fields of the tag to the proper lengths */
static int id3v1_truncate_tag(id3v1_tag*);

/* Returns 1 or 0 whether arg 1 is just filled up with space (0x20) or not */
static int id3_is_only_space(char*, int);

/* Gets all frame names available in the tag */
static char **id3v2_get_names(id3v2_tag*);

/* Gets the content of the given field in the tag on the specified position. */
static id3_content* id3v2_get_content_at_pos(id3v2_tag*, const char*, int);
static id3_content* id3v1_get_content(id3v1_tag*, int);

/* Gets the number of available frames */
static int id3_get_no_frames(id3v2_tag*);

/* Returns string of the frames content */
/* static char* extract_frame_data(char *, int); */

/* Removes a frame from the frame list */
static int id3_remove_frame(id3v2_frame_list *, id3v2_frame *);

/* Adds a new frame to the list */
static int id3_add_frame(id3v2_frame_list *, char *, char *, int);

/* Lookups a frame by his identifier on the given position */
static id3v2_frame* id3_lookup_frame(id3v2_frame_list *, const char *, const int);

/* Sync functions */
static long id3_unsync(unsigned char*, long);
static long id3_sync(unsigned char*, long);
static unsigned int id3_unsync32(unsigned char*, int);
static unsigned char* id3_sync32(unsigned int);

static int id3_lseek_syncword(int);
static int id3_lseek_syncword_r(int, unsigned char *, int);

/* Gets a new allocated v1 or v2 tag */
static id3_tag* id3v1_alloc_tag(void);
static id3_tag* id3v2_alloc_tag(void);

/* free functions */
static void id3v1_free_tag(id3v1_tag*);
static void id3v2_free_tag(id3v2_tag*);

/* read and lseek wrappers for memory */
size_t read_mem(void *dest, size_t nbytes, void *varg);
off_t lseek_mem(off_t offset, int whence, void *varg);

/* read and lseek wrappers for files */
size_t read_file(void *dest, size_t nbytes, void *varg);
off_t lseek_file(off_t offset, int whence, void *varg);

__END_DECLS

#endif /* __MPLIB_S_H */
