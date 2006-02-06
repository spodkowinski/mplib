/*
 * mplib - a library that enables you to edit ID3 tags
 *
 * Copyright (c) 2001,2002,2003,2004,2005 Stefan Podkowinski
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

#include <sys/types.h>
#include <stdio.h>
/* define XMALLOC_CHECK 1 */
#include "xmalloc.h"
#ifdef USE_GC
# include <gc.h>
# define malloc(str) GC_MALLOC(str)
#endif

#ifdef XMALLOC_CHECK
typedef struct _xdelem {
    void* alloced;
    void* freed;
    char* descrl;
    struct _xdelem* next;
} xdelem;

xdelem* first = NULL;
#endif

#define errmsg "mplib: Memory exhausted: Could not allocate %d bytes\n"

void *
xmalloc(size_t s)
{
    return xmallocd(s, NULL);
}

void *
xmallocd(size_t s, char* descrl)
{
  void *new = (void*)malloc(s);
#ifdef XMALLOC_CHECK
  xdelem* cur = (xdelem*)malloc(sizeof(xdelem));
  cur->next = NULL;
  cur->freed = NULL;
  cur->descrl = descrl;
#endif
  if(!new) fprintf(stderr, errmsg, s);

#ifdef XMALLOC_CHECK
  cur->alloced = new;
 exists:
  if(!first) first = cur;
  else {
      xdelem* last = first;
      do {
	  if(last->alloced == cur->alloced) {
	      last->freed = NULL;
	      last->descrl = descrl;
	      free(cur);
	      goto exists;
	  }
      } while(last->next && (last = last->next));
      last->next = cur;
  }
#endif

  return new;
}

void *
xmallocd0(size_t s, char* descr)
{
#ifdef XMALLOC_CHECK
    void *new = (void*)xmallocd(s, descr);
#else
    void *new = (void*)malloc(s);
#endif
    if(!new) fprintf(stderr, errmsg, s);
    else memset(new, 0, s);
    return new;
}

void *
xmalloc0(size_t s)
{
#ifdef XMALLOC_CHECK
  void *new = (void*)xmalloc(s);
#else
  void *new = (void*)malloc(s);
#endif
  if(!new) fprintf(stderr, errmsg, s);
  else memset(new, 0, s);
  return new;
}

void *
xrealloc(void * ptr, size_t s)
{
  void *new;

  if(!ptr) return xmalloc(s);

  new = (void*)realloc(ptr, s);
  if(!new) fprintf(stderr, errmsg, s);
  return new;
}

void
xfree(void* ptr) {
    if(!ptr) return;
#ifdef XMALLOC_CHECK
    if(first) {
	xdelem* el = first;
	do {
	    if(el->freed == ptr) {
		if(el->descrl)
		    printf("XMALLOC: (%s) memory allready freed\n", el->descrl);
		else
		    printf("XMALLOC: memory allready freed at %h\n", ptr);
		break;
	    }
	    if(el->alloced == ptr) {
		el->freed = ptr;
		break;
	    }
	} while(el->next && (el = el->next));
    }
#endif
    free(ptr);
}


#ifdef XMALLOC_CHECK
void
xprint_malloc_stat(void) {
    long kb_alloc = 0;
    long kb_freed = 0;
    long kb_used = 0;
    int count_used = 0;
    xdelem* el = first;

    if(!first) {
	puts("XMALLOC: No statistic available");
    }
    puts("xmalloc statistic:");
    do {	
	if(!el->freed) {
	    if(el->descrl && !strstr(el->descrl, "ignore")) 
		printf("%s (not freed)\n", el->descrl);
	    else if(!el->descrl) printf("%p (not freed)\n", el->alloced);
	} else {
	    //if(el->descrl) printf("%s (freed)\n", el->descrl);
	    //else printf("%p (freed)\n", el->alloced);
	}
    } while(el->next && (el = el->next));
}
#endif
