/*  character-set based brute-forcing algorithm
 *  Copyright (C) 2004 by mimayin@aciiid.ath.cx
 *  Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013 by bofh28@gmail.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 only of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  crunch version 1.0 was written by mimayin@aciiid.ath.cx
 *  all later versions of crunch have been updated by bofh28@gmail.com
 *
 *  Changelog:
 *  version 1.0 initial release in 2004 (guess based on copyright date) 194 lines of code
 *  version 1.1 added support to read character list from a specified file
 *  version 1.2 added output parameter
 *  version 1.3 added -c parameter to break apart output file. I would prefer to break
 *                 apart on file size instead of number of lines, but there is no reliable
 *                 way to get that information while the file is being created.
 *  version 1.4 added better help documentation and fixed some bugs:
 *              space character was sometimes getting stripped off in charset
 *              replace if (pattern[0]==0) { with if ((strncmp(&pattern[0],"\0",1)==0)) {
 *                 to make splint happy
 *              rename templ variable to pattern
 *              changed some fixed size local buffers to dynamically allocated buffers
 *              if max-len was larger than strlen of the -t parameter crunch would generate
 *                 duplicate words
 *              document some of the code
 *  version 1.5 fixed length and -s parameter.  Before if you did ./crunch 1 3 -s 	
 *                 you would only get j-z and not j-zzz
 *              converted some fixed length buffers to variable length
 *              added checks to fclose
 *              fixed it so that -s and -t can now work together
 *              added support to generate wordlists greater than 2GB even though several
 *                 programs can't access files of this size (john the ripper for example)
 *              This support works on Ubuntu intrepid.  This probably works on most Linux
 *                 platforms.  Support for Solaris, HP-UX, Windows, BSD is unknown.
 *  version 1.6 add option (-p) to support factorial instead of exponentail processing.  i.e.
 *                 if you did ./crunch 3 3 abc you would get 27 results (3x3x3): a through ccc
 *                 This new option will give you 6 results (3! = 3x2x1)
 *                 i.e. (abc, acb, bac, bca, cab, cba)
 *                 the permute function was written by Richard Heathfield
 *                 and copied from
 *                 http://bytes.com/groups/c/536779-richard-heathfields-tsp-permutation-algorithm
 *                 I did change temp from an int to char to make splint happy.
 *                 Richard Heathfield may be contacted at rjh@cpax.org.uk
 *  version 1.7 add option (-m) to support factoring words instead of characters
 *  version 1.8 add option (-z) to support compressing the output
 *  version 1.9 only need permute2 (remove permute and renamed permute2 to permute)
 *              fix off by 1 error - reported by MikeCa
 *              fix issue where output file wasn't being renamed
 *              fork progress process
 *              really fix it so that -s and -t can now work together
 *              when using -c sometimes the output was 1 larger than requested
 *              cstring_cmp from http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml to sort words to permute so the results will be in sorted order
 *  version 2.0 permute now supports -c -o & -z. -f is also supported for permuting letters
 *              really really fix it so that -s and -t can now work together
 *              added null checks for parameter values to prevent segmentation faults
 *              added support to invert chunk output - written by Pillenski
 *              added support to breakup file based on size - written by Pillenski
 *  version 2.1 permute now supports -b
 *              add signal handling - pressing ctrl break will cause crunch
 *                 to finish the word it is processing and then gracefully exit instead
 *                 of leaving files open and words half finished.  This is the first
 *                 step in supporting resume.
 *              chunk now supports resume
 *  version 2.2 pattern supports numbers and symbols
 *  version 2.3 fix bytecount
 *              add new options to usage
 *  version 2.4 fix usage (-m and not -n) - reported by Tape
 *              clarified -b option in help and man file - reported by Tape
 *              fix Makefile install to /pentest/passwords not /pentest/password -
 *                 reported by Tape
 *              make bytecount behave consistently - reported by Tape
 *              fixed up copyrights
 *  version 2.5 -q permute supports reading from strings from file
 *              sorted parameters in code and usage
 *              -t supports upper and lower case letters
 *              -f supports multiple charsets
 *              add -v option to show version information
 *              add correct gpl.txt (version 2 not 3)
 *              fix charset.lst (some symbol14 had 15 chars)
 *              add symbol14, symbol14-space, symbol-all, and symbol-all-space to charset.lst
 *              removed examples and parameters from usage.  I added a sentence
 *                 telling people to refer to the man page.  It is easier to update
 *                 the man only.
 *              combined -m and -p into -p
 *              got rid of some unnecessary casts
 *              changed all mallocs to callocs, this shuts up a few splint warnings
 *  version 2.6 fix -p seg fault - reported by Tape
 *              improve -p documentation - reported by Tape
 *              fix Makefile to install to correct directory again - reported by Tape
 *              fix Makefile to install charset.lst - reported by Tape
 *              fix memory leak
 *              replace if (argv[i+1] != NULL) with if (i+1 < argc) as argv[i+1]
 *                 can be filled garbage so it is not an accurate test
 *              fix an off by 1 in resume counter
 *              resume now respects the -b parameter, previously it was ignored
 *              -s now supports the @*%^ symbols in -t
 *              added status report when saving to file
 *              renamed some variables to better names
 *              added a few comments to variables
 *              added a hex string 0123456789abcdef to charset.lst
 *  version 2.7 fix progress bar when using -s
 *              fixed typo man file - Thanks Tape
 *              add -u option to suppress all filesize and linecount so crunch
 *                 can feed another program
 *              fork a child process for progress %%
 *              Niclas Kroon added swedish characters to the charset.lst
 *              permute supports -t
 *              added -std=c99 to Makefile since unsigned long long isn't in c89
 *              ran valgrind and fixed a small memory issue.  I forgot to allocate
 *                 space for the \0 character in a few places.  Doh!
 *              improved documentation of the charset field
 *  version 2.8 fix progress message.  It could cause a fatal error under certain
 *                 circumstances
 *  version 2.9 fix divide by zero error.
 *  version 3.0 fix wrong version number
 *              changed the * character of -t option to a , (comma) as * is a reserved character
 *              strip off blank lines when reading file for permute (-q option)
 *              I fixed a problem with using -i and -t together
 *              add -l to allow for literal characters of @,%^
 *              fix -b and -c and % output
 *              fix permute -t to work with -b and -c
 *              fixed crash when / character was in filename
 *                 replace / with space - reported by Nazagul
 *  version 3.0.1 fix printpermutepattern - it was using $ instead of ,
 *  version 3.1 make -l take a string so you can have @ and characters
 *              add TB and PB to output size
 *              fix comments referencing $ that should be ,
 *              add -e to end generation after user specified string (useful
 *                 when piping crunch to a program)
 *  version 3.2 add -d to limit duplicate characters
 *              put correct function name into error messages to help with debugging
 *              fix Makefile uninstall to remove crunch directory and install GPL.TXT
 *              removed flag5 as it wasn't needed
 *              if you press Ctrl-C crunch will now print where it stops so you
 *                 can resume piping crunch into another program
 *  version 3.3 add more information to help section
 *              Fixed mem leaks, invalid comparisons - fixed by JasonC
 *              Error messages and startup summary now go to stderr (-u now 
 *                 unnecessary) - fixed by JasonC
 *              Fixed startup delay due to long sequences of dupe-skipped 
 *                 strings - fixed by JasonC
 *              Added unicode support - written by JasonC
 *              fix write and compress error - reported and fixed by amontero
 *              fix printpercentage -> linecounter should be ->linetotal
 *              add support for 7z
 *  version 3.4 fix -e problem reported by hajjid
 *              test compile using Ubuntu 12.10 and fixed the following issues:
 *                 reorder flags in Makefile so crunch can compile successfully
 *                 remove finall variable from printpercentage
 *                 remove loaded from main
 *  version 3.5 make changes to the man based on suggestions from Jari Aalto
 *              pass pidret to void to make warning go away
 *              rename GPL.TXT to COPYING
 *              removed need for -o to use -c i.e. you can use -c any time now
 *              fixed resume
 *              fixed linecount and size when using -c and/or -e
 *  version 3.6 fix endstring problem reported and fixed by mr.atreat@gmail.com
 *              fix a memory allocation reported and fixed by Hxcan Cai
 *              allow Makefile to detect Darwin so make will work properly reported and fixed by Marcin
 *
 *  TODO: Listed in no particular order
 *         add resume support to permute (I am not sure this is possible)
 *         make permute more intelligent (min, max) (I am not sure this is possible either)
 *         support SIGINFO when Linux supports it, use SIGUSR1 until SIGINFO is available
 *         finalbytecount isn't currently correct for unicode chars unless -p used
 *         let user specify placeholder characters (@,%^)
 *         add date support?
 *         specify multiple charset names using -f i.e. -f charset.lst + ualpha 123 +
 *         make permute use -e
 *         revamp compression part of renamefile 7z doesn't delete original file
 *         size calculations are wrong when min or max is larger than 12
 *         write word to temp file for resuming after power outage
 *
 *  usage: ./crunch <min-len> <max-len> [charset]
 *  e.g: ./crunch 3 7 abcdef
 *
 *  This example will compute all passwords between 3 and 7 chars
 *  using 'abcdef' as the character set and dump it to stdout.
 *
 *  usage: ./crunch <from-len> <to-len> [-f <path to charset.lst> charset-name] [-o wordlist.txt or START] [-t [FIXED]@@@@] [-s startblock]
 *
 *  Options:
 *  -b          : maximum bytes to write to output file. depending on the blocksize
 *                files may be some bytes smaller than specified but never bigger.
 *  -c          : numbers of lines to write to output file, only works if "-o START"
 *                is used, eg: 60  The output files will be in the format of starting
 *                letter - ending letter for example:
 *                crunch 1 5 -f /pentest/password/charset.lst mixalpha -o START -c 52
 *                will result in 2 files: a-7.txt and 8-\ .txt  The reason for the
 *                slash in the second filename is the ending character is space and
 *                ls has to escape it to print it.  Yes you will need to put in
 *                the \ when specifying the filename.
 *  -d          : specify -d [n][@,%^] to suppress generation of strings with more
 *                than [n] adjacent duplicates from the given character set. For example:
 *                ./crunch 5 5 -d 2@
 *                Will print all combinations with 2 or less adjacent lowercase duplicates.
 *  -e          : tells crunch to stop generating words at string.  Useful when piping
 *                crunch to another program.
 *  -f          : path to a file containing a list of character sets, eg: charset.lst
 *                name of the character set in the above file eg:
 *                mixalpha-numeric-all-space
 *  -i          : inverts the output so the first character will change very often
 *  -l          : literal characters to use in -t @,%^
 *  -o          : allows you to specify the file to write the output to, eg:
 *                wordlist.txt
 *  -p          : prints permutations without repeating characters.  This option
 *                CANNOT be used with -s.  It also ignores min and max lengths.
 *  -q          : Like the -p option except it reads the strings from the specified
 *                file.  It CANNOT be used with -s.  It also ignores min and max.
 *  -r          : resume a previous session.  You must use the same command line as
 *                the previous session.
 *  -s          : allows you to specify the starting string, eg: 03god22fs
 *  -t [FIXED]@,%^  : allows you to specify a pattern, eg: @@god@@@@
 *                where the only the @'s will change with lowercase letters
 *                the ,'s will change with uppercase letters
 *                the %'s will change with numbers
 *                the ^'s will change with symbols
 *  -u          : The -u option disables the printpercentage thread.  This should be the last option.
 *  -z          : adds support to compress the generated output.  Must be used
 *                with -o option.  Only supports gzip, bzip, lzma, and 7z.
 *
 *  This code can be easily adapted for use in brute-force attacks
 *  against network services or cryptography.
 *
 *  Compiles on: linux (32 and 64 bit Ubuntu for sure, 32 and 64 bit Linux in
 *     general works.  I have received word that crunch compiles on MacOS.
 *     Juan reports Freebsd x64, i386 and OSX Mountain Lion compiles and works
 *     perfectly. It should compile on the other Unix and Linux OSs but I don't
 *     don't have access to any of the those systems.  Please let me know.
 */

#include <assert.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>

/* largest output string */
#define MAXSTRING 128
/* longest character set */
#define MAXCSET 256

/* invalid index for size_t's */
#define NPOS ((size_t)-1)

static const wchar_t def_low_charset[] = L"abcdefghijklmnopqrstuvwxyz";
static const wchar_t def_upp_charset[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const wchar_t def_num_charset[] = L"0123456789";
static const wchar_t def_sym_charset[] = L"!@#$%^&*()-_+=~`[]{}|\\:;\"'<>,.?/ ";
static const char version[] = "3.6";

static size_t inc[128];
static size_t numofelements = 0;
static size_t inverted = 0;  /* 0 for normal output 1 for aaa,baa,caa,etc */

static unsigned long long linecount = 0; /* user specified break output into count lines */

static unsigned long long bytecount = 0 ;  /* user specified break output into size */

static volatile sig_atomic_t ctrlbreak = 0; /* 0 user did NOT press Ctrl-C 1 they did */

static FILE *fptr;        /* file pointer */

static int output_unicode = 0; /* bool. If nonzero, all output will be unicode. Can be set even if non-unicode input*/

/* When unicode input is given, the code cannot [currently] always calculate
  the exact final file size.  In those cases this var simply suppresses
  the output.  For what it's worth, the calculated size is always the minimum size. */
static int suppress_finalsize = 0; /* bool */

/*
Need a largish global buffer for converting wide chars to multibyte
to avoid doing an alloc on every single output line
leading to heap frag.  Only alloc'd once at startup.
Size is MAXSTRING*MB_CUR_MAX+1
*/
static char* gconvbuffer = NULL;
static size_t gconvlen = 0;

struct thread_data{
unsigned long long finalfilesize; /* total size of output */
unsigned long long bytetotal;  /* total number of bytes so far */
unsigned long long bytecounter; /* count number of bytes in output resets to 0 */
unsigned long long finallinecount; /* total size of output */
unsigned long long linetotal; /* total number of lines so far */
unsigned long long linecounter; /* counts number of lines in output resets to 0 */
};

/* pattern info */
struct pinfo {
  wchar_t *cset; /* character set pattern[i] is member of */
  size_t clen;
  int is_fixed; /* whether pattern[i] is a fixed value */
  size_t start_index, end_index; /* index into cset for the start and end strings */
  size_t duplicates;
};

/* program options */
struct opts_struct {
  wchar_t *low_charset;
  wchar_t *upp_charset;
  wchar_t *num_charset;
  wchar_t *sym_charset;
  size_t clen, ulen, nlen, slen;
  wchar_t *pattern;
  size_t plen;
  wchar_t *literalstring;
  wchar_t *startstring;
  wchar_t *endstring;
  size_t duplicates[4]; /* allowed number of duplicates for each charset */

  size_t min, max;

  wchar_t *last_min;  /* last string of length min */
  wchar_t *first_max; /* first string of length max */
  wchar_t *min_string;
  wchar_t *max_string; /* either startstring/endstring or calculated using the pattern */

  struct pinfo *pattern_info; /* information generated from pattern */
};
typedef struct opts_struct options_type;

static struct thread_data my_thread;

static int wcstring_cmp(const void *a, const void *b) {
  const wchar_t **ia = (const wchar_t **)a;
  const wchar_t **ib = (const wchar_t **)b;
  return wcscmp(*ia, *ib);
}

static void ex_program() {
  ctrlbreak = 1;
  (void) signal(SIGINT, SIG_DFL);
}

static size_t force_wide_string(wchar_t *wout, const char *s, size_t n) {
size_t i;
const unsigned char *ucp = (const unsigned char*)s;
size_t slen = strlen(s);

  /*
  Blindly convert all characters to the numerically equivalent wchars.
  This is intended to be used after a call to mbstowcs fails.
  Like mbstowcs(), output may not be null terminated if returns n
  */

  for (i=0; i<n && i<slen; ++i) {
    wout[i] = (wchar_t)ucp[i];
  }

  if (i<n)
    wout[i] = 0;

  return i;
}

static size_t make_wide_string(wchar_t *wout, const char *s, size_t n, int* r_is_unicode) {
size_t stres;
const char* cp;
int contains_upp128 = 0;

  /*
  If 's' contains a UTF-8 string which is not plain 7bit,
  is_unicode is set nonzero and wout contains the proper wide string.
  Otherwise the code points are assumed to be the exact values in s.
  Unlike mbstowcs, result is always null terminated as long as
  n is nonzero.
  Leave r_is_unicode undisturbed unless setting to nonzero!
    (must never be changed from 1 to 0 regardless of this call's data)
  */

  for (cp = s; *cp; ++cp) {
    if ((int)*cp < 0) {
      contains_upp128 = 1;
      break;
    }
  }

  stres = mbstowcs(wout,s,n);
  if (stres != NPOS) {
    if (contains_upp128 && r_is_unicode)
      *r_is_unicode = 1;
  }
  else
    stres = force_wide_string(wout,s,n);

  if (n != 0)
    wout[n-1]=0;

  return stres;
}

static wchar_t *alloc_wide_string(const char *s, int* r_is_unicode) {
wchar_t* wstr = NULL;  
size_t len = s ? strlen(s)+1 : 1;

  wstr = (wchar_t*)malloc(len*sizeof(wchar_t));
  if (!wstr) {
    fprintf(stderr,"alloc_wide_string: Can't allocate mem!\n");
    exit(EXIT_FAILURE);
  }
  (void)make_wide_string(wstr,s?s:"",len,r_is_unicode);
  return wstr;
}

static size_t force_narrow_string(char *out, const wchar_t* src, size_t n) {
size_t i;
  for (i=0; i<n && src[i]!=L'\0'; ++i) {
    out[i] = (char)(src[i]&0xFF);
  }

  if (i<n)
    out[i] = '\0';

  return i;
}

static size_t make_narrow_string(char *out, const wchar_t* src, size_t n) {
size_t retval;

  /*
  If global output_unicode is true, src is converted to a UTF-8 string.
  If not, the low 8 bits are copied to the output string
  which is most definitely not what you want unless the input
  wasn't unicode in the first place.
  Unlike wcstomb(), output is always null terminated as long as n!=0
  */

  if (output_unicode != 0) {
    retval = wcstombs(out, src, n);
    if (retval == NPOS) {
      fprintf(stderr,"Error: wcstombs() failed.  This shouldn't have happened.\n");
      exit(EXIT_FAILURE);
    }
  }
  else
    retval = force_narrow_string(out, src, n);

  if (n!=0)
    out[n-1]='\0';

  return retval;
}

static int getmblen(wchar_t wc) {
  /* returns number of bytes required for wide char wc, taking into account current setting of global output_unicode */
  int mblen = 1;
  if (output_unicode) {
    char mb[MB_CUR_MAX+1];
    mblen = wctomb(mb,wc);
    if (mblen == -1) {
      fprintf(stderr,"Warning: wctomb failed for char U+%04lX\n",(unsigned long)wc);
      mblen = 1;
    }
  }
  return mblen;
}

static wchar_t *dupwcs(const wchar_t *s) {
  /* replacement for wcsdup, where not avail (it's POSIX) */
  size_t n;
  wchar_t *p = NULL;

  if (s != NULL)
  {
    n = (1 + wcslen(s)) * sizeof(wchar_t);
    if ((p = (wchar_t*)malloc(n))!=NULL)
      memcpy(p, s, n);
  }

  return p;
}

/* return 0 if string1 does not comply with options.pattern and options.literalstring */
static int check_member(const wchar_t *string1, const options_type* options) {
const wchar_t *cset;
size_t i;

  for (i = 0; i < wcslen(string1); i++) {
    cset = NULL;
    switch (options->pattern[i]) {
      case L'@':
        if (options->literalstring[i] != L'@')
          cset = options->low_charset;
        break;
      case L',':
        if (options->literalstring[i] != L',')
          cset = options->upp_charset;
        break;
      case L'%':
        if (options->literalstring[i] != L'%')
          cset = options->num_charset;
        break;
      case L'^':
        if (options->literalstring[i] != L'^')
          cset = options->sym_charset;
        break;
      default: /* constant part of pattern */
        break;
    }

    if (cset == NULL) {
      if (string1[i] != options->pattern[i])
        return 0;
      continue;
    }
    
    while (*cset)
      if (string1[i] == *cset)
        break;
      else
        cset++;
    if (*cset == L'\0')
      return 0;
  }
  return 1;
}

/* NOTE: similar to strpbrk but length limited and only searches for a single char */
static size_t find_index(const wchar_t *cset, size_t clen, wchar_t tofind) {
size_t i;
  for (i = 0; i < clen; i++)
    if (cset[i] == tofind)
      return i;
  return NPOS;
}

static void fill_minmax_strings(options_type *options) {
size_t i;
wchar_t *last_min; /* last string of size min */
wchar_t *first_max; /* first string of size max */
wchar_t *min_string, *max_string; /* first string of size min, last string of size max */

  last_min = calloc(options->min + 1,sizeof(wchar_t));
  if (last_min == NULL) {
    fprintf(stderr,"fill_minmax_strings: can't allocate memory for last_min\n");
    exit(EXIT_FAILURE);
  }
  last_min[options->min] = L'\0';

  first_max = calloc(options->max + 1,sizeof(wchar_t));
  if (first_max == NULL) {
    fprintf(stderr,"fill_minmax_strings: can't allocate memory for first_max\n");
    exit(EXIT_FAILURE);
  }
  first_max[options->max] = L'\0';

  min_string = calloc(options->min + 1,sizeof(wchar_t));
  if (min_string == NULL) {
    fprintf(stderr,"fill_minmax_strings: can't allocate memory for min_string\n");
    exit(EXIT_FAILURE);
  }
  min_string[options->min] = L'\0';

  max_string = calloc(options->max + 1,sizeof(wchar_t));
  if (max_string == NULL) {
    fprintf(stderr,"fill_minmax_strings: can't allocate memory for max_string\n");
    exit(EXIT_FAILURE);
  }
  max_string[options->max] = L'\0';

  /* fill last_min and first_max */
  for (i = 0; i < options->max; i++) {
    if (options->pattern == NULL) {
      if (i < options->min) {
        last_min[i] = options->low_charset[options->clen-1];
        min_string[i] = options->low_charset[0];
      }
      first_max[i] = options->low_charset[0];
      max_string[i] = options->low_charset[options->clen-1];
    }
    else { /* min == max */
      min_string[i] = max_string[i] = last_min[i] = first_max[i] = options->pattern[i];
      switch (options->pattern[i]) {
      case L'@':
        if (options->literalstring[i] != L'@') {
          max_string[i] = last_min[i] = options->low_charset[options->clen - 1];
          min_string[i] = first_max[i] = options->low_charset[0];
        }
        break;
      case L',':
        if (options->literalstring[i] != L',') {
          max_string[i] = last_min[i] = options->upp_charset[options->ulen - 1];
          min_string[i] = first_max[i] = options->upp_charset[0];
        }
        break;
      case L'%':
        if (options->literalstring[i] != L'%') {
          max_string[i] = last_min[i] = options->num_charset[options->nlen - 1];
          min_string[i] = first_max[i] = options->num_charset[0];
        }
        break;
      case L'^':
        if (options->literalstring[i] != L'^') {
          max_string[i] = last_min[i] = options->sym_charset[options->slen - 1];
          min_string[i] = first_max[i] = options->sym_charset[0];
        }
        break;
      default:
        break;
      }
    }
  }
  
  options->last_min = last_min;
  options->first_max = first_max;

  if (options->startstring)
    for (i = 0; i < options->min; i++)
      min_string[i] = options->startstring[i];
  if (options->endstring)
    for (i = 0; i < options->max; i++)
      max_string[i] = options->endstring[i];

  options->min_string = min_string;
  options->max_string = max_string;
}

static void fill_pattern_info(options_type *options) {
struct pinfo *p;
wchar_t *cset;
size_t i, clen, index, si, ei;
int is_fixed;
size_t dupes;

  options->pattern_info = calloc(options->max, sizeof(struct pinfo));
  if (options->pattern_info == NULL) {
    fprintf(stderr,"fill_pattern_info: can't allocate memory for pattern info\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < options->max; i++) {
    cset = NULL;
    clen = 0;
    index = 0;
    is_fixed = 1;
    dupes = options->duplicates[0];
    if (options->pattern == NULL) {
      cset = options->low_charset;
      clen = options->clen;
      is_fixed = 0;
    }
    else {
      cset = NULL;
      switch (options->pattern[i]) {
        case L'@':
          if (options->literalstring[i] != L'@') {
            cset = options->low_charset;
            clen = options->clen;
            is_fixed = 0;
            dupes = options->duplicates[0];
          }
          break;
        case L',':
          if (options->literalstring[i] != L',') {
            cset = options->upp_charset;
            clen = options->ulen;
            is_fixed = 0;
            dupes = options->duplicates[1];
          }
          break;
        case L'%':
          if (options->literalstring[i] != L'%') {
            cset = options->num_charset;
            clen = options->nlen;
            is_fixed = 0;
            dupes = options->duplicates[2];
          }
          break;
        case L'^':
          if (options->literalstring[i] != L'^') {
            cset = options->sym_charset;
            clen = options->slen;
            is_fixed = 0;
            dupes = options->duplicates[3];
          }
          break;
        default: /* constant part of pattern */
          break;
      }
    }

    if (cset == NULL) {
      /* fixed character.  find its charset and index within. */

      cset = options->low_charset;
      clen = options->clen;
      dupes = options->duplicates[0];

      if (options->pattern == NULL) {
        fprintf(stderr,"fill_pattern_info: options->pattern is NULL!\n");
        exit(EXIT_FAILURE);
      }

      if ((index = find_index(cset, clen, options->pattern[i])) == NPOS) {
        cset = options->upp_charset;
        clen = options->ulen;
        dupes = options->duplicates[1];
        if ((index = find_index(cset, clen, options->pattern[i])) == NPOS) {
          cset = options->num_charset;
          clen = options->nlen;
          dupes = options->duplicates[2];
          if ((index = find_index(cset, clen, options->pattern[i])) == NPOS) {
            cset = options->sym_charset;
            clen = options->slen;
            dupes = options->duplicates[3];
            if ((index = find_index(cset, clen, options->pattern[i])) == NPOS) {
              cset = NULL;
              clen = 0;
              dupes = (size_t)-1;
              index = 0;
            }
          }
        }
      }
      si = ei = index;
    }
    else {
      /*
      si = find_index(cset, clen, options->min_string[i]);
      */

      /* That can't be right.  Would only work when we have a pattern
          or min==max, neither is guaranteed here.  Or is it?  -jC */

      if (i < wcslen(options->min_string))
        si = find_index(cset, clen, options->min_string[i]);
      else
        si = 0;

      ei = find_index(cset, clen, options->max_string[i]);

      if (si == NPOS || ei == NPOS) {
        fprintf(stderr,"fill_pattern_info: Internal error: "\
          "Can't find char at pos #%lu in cset\n",
          (unsigned long)i+1);
        exit(EXIT_FAILURE);
      }
    }
    p = &(options->pattern_info[i]);
    p->cset = cset;
    p->clen = clen;
    p->is_fixed = is_fixed;
    p->start_index = si;
    p->end_index = ei;
    p->duplicates = dupes;
  }

#ifdef DEBUG
  printf("pattern_info duplicates: ");
  for (i = 0; i < options->max; i++) {
    p = &(options->pattern_info[i]);
    printf("(%d %d %d %d %d %d)", p->cset, p->clen, p->is_fixed, p->start_index, p->end_index, p->duplicates);
  }
  printf("\n");
#endif
}

static unsigned long long fill_next_count(size_t si, size_t ei, int repeats, unsigned long long sum, /*@null@*/ unsigned long long *current_count, /*@out@*/ unsigned long long *next_count, size_t len) {
size_t i;
unsigned long long nextsum = 0;

  for (i = 0; i < si; i++)
    next_count[i] = 0;

  if (repeats == 0 || current_count == NULL)
    nextsum = sum;
  else if (repeats == 1)
    for (; i <= ei; i++) {
      next_count[i] = sum - current_count[i];
      nextsum += next_count[i];
    }
  else /* repeats > 1 */
    for (; i <= ei; i++) {
      next_count[i] = current_count[i];
      nextsum += next_count[i];
    }

  for (; i < len; i++)
    next_count[i] = 0;

  return nextsum;
}

/* calculate the number of strings from start to end taking into account duplicate removal worst case: O(2^n), could be improved using memoize */
static unsigned long long calculate_with_dupes(int start_point, int end_point, size_t first, size_t last, size_t pattern_index, int repeats, unsigned long long current_sum, /*@null@*/ unsigned long long *current_count, const options_type options, size_t plen) {
/* start_point and end_point are bools */

unsigned long long count[MAXCSET];
unsigned long long *next_count;
unsigned long long total = 0, sum = 0;
size_t start_index, end_index;
size_t i;

  if (first == NPOS || last == NPOS || first > last || pattern_index > plen) /* sanity check */
    return 0;

   /* check for too many duplicates */
  if (pattern_index > 0 && (size_t)repeats > options.pattern_info[pattern_index-1].duplicates) {
    return 0;
  }

  /* create the result count for pattern_index - 1 */
  if (pattern_index == 0) {
    sum = current_sum;
    next_count = NULL;
  }
  else if (pattern_index == 1 ||
      (options.pattern_info[pattern_index-1].cset != NULL &&
      options.pattern_info[pattern_index-2].cset != options.pattern_info[pattern_index-1].cset) ||
      (options.pattern_info[pattern_index-1].cset == NULL &&
      options.pattern[pattern_index-2] != options.pattern[pattern_index-1])) {
    /* beginning new cset */
    if (repeats > 1) {
      return 0;
    }
    if (options.pattern_info[pattern_index-1].cset != NULL) {
      for (i = 0; i < first; i++)
        count[i] = 0;
      for (; i <= last; i++)
        count[i] = current_sum;
      for (; i < options.pattern_info[pattern_index-1].clen; i++)
        count[i] = 0;
      next_count = count;
    } else
      next_count = NULL;
    sum = current_sum * (last - first + 1);
  }
  else if (options.pattern_info[pattern_index-1].cset == NULL &&
      options.pattern[pattern_index-2] == options.pattern[pattern_index-1]) {
    /* continuing unknown cset */
    sum = current_sum;
    next_count = NULL;
  }
  else {
    /* continuing previous cset */
    sum = fill_next_count(first, last, repeats, current_sum, current_count, count, options.pattern_info[pattern_index-1].clen);
    next_count = count;
  }

  if (sum == 0) {
    return 0;
  }

  if (pattern_index == plen) { /* check for the end of the pattern */
    return sum;
  }

  if (options.pattern_info[pattern_index].is_fixed) {
    start_index = end_index = options.pattern_info[pattern_index].start_index;
  }
  else {
    start_index = 0;
    end_index = options.pattern_info[pattern_index].clen - 1;
    if (start_point)
      start_index = options.pattern_info[pattern_index].start_index;
    if (end_point)
      end_index = options.pattern_info[pattern_index].end_index;
  }

  if (start_index == end_index) {
    /* [0..si..0](sp, ep) */
    if (repeats > 0)
      total += calculate_with_dupes(start_point, end_point, start_index, end_index, pattern_index + 1, repeats + 1, sum, next_count, options, plen);
    total += calculate_with_dupes(start_point, end_point, start_index, end_index, pattern_index + 1, 1, sum, next_count, options, plen);
  }
  else {
    if (start_point) {
      /* [0..si..0](sp, 0) */
      if (repeats > 0)
        total += calculate_with_dupes(start_point, 0, start_index, start_index, pattern_index + 1, repeats + 1, sum, next_count, options, plen);
      total += calculate_with_dupes(start_point, 0, start_index, start_index, pattern_index + 1, 1, sum, next_count, options, plen);
      start_index++;
    }

    if (end_point) {
      /* [0..ei..0](0, ep) */
      if (repeats > 0)
        total += calculate_with_dupes(0, end_point, end_index, end_index, pattern_index + 1, repeats + 1, sum, next_count, options, plen);
      total += calculate_with_dupes(0, end_point, end_index, end_index, pattern_index + 1, 1, sum, next_count, options, plen);
      end_index--;
    }

    if (start_index <= end_index) {  /* middle */
      /* [0..si..ei..0](0,0) */
      if (repeats > 0)
        total += calculate_with_dupes(0, 0, start_index, end_index, pattern_index + 1, repeats + 1, sum, next_count, options, plen);
      total += calculate_with_dupes(0, 0, start_index, end_index, pattern_index + 1, 1, sum, next_count, options, plen);
    }
  }

  return total;
}

/* calculate the number of strings from start to end O(n)  */
static unsigned long long calculate_simple(const wchar_t *startstring, const wchar_t *endstring, const wchar_t *cset, size_t clen) {
unsigned long long total = 1;
size_t index1, index2;

  for (; *endstring && *startstring; endstring++, startstring++) {
    for (index1 = 0; cset[index1] != L'\0' && cset[index1] != *endstring;)
      index1++;
    if (cset[index1] == L'\0')
      index1 -= 1;
    for (index2 = 0; cset[index2] != L'\0' && cset[index2] != *startstring;)
      index2++;
    if (cset[index2] == L'\0')
      index2 = 0;
    total = (total - 1) * (unsigned long long)clen + (unsigned long long)index1 - (unsigned long long)index2 + 1;
  }
  return total;
}

/* calculate the number of strings from start to end, inclusive, taking into account the pattern O(n) */
static unsigned long long calculate_with_pattern(const wchar_t *startstring, const wchar_t *endstring, const options_type options) {
unsigned long long total_strings = 1;
size_t temp, clen;
const wchar_t *cset;
size_t index1, index2;

  if (options.pattern == NULL) {
    return calculate_simple(startstring, endstring, options.low_charset, options.clen);
  }

  for (temp = 0; temp < options.plen; temp++) {
    cset = NULL;
    clen = 0;
    switch (options.pattern[temp]) {
      case L'@':
        if (options.literalstring[temp] != L'@') {
          clen = options.clen;
          cset = options.low_charset;
        }
        break;
      case L',':
        if (options.literalstring[temp] != L',') {
          clen = options.ulen;
          cset = options.upp_charset;
        }
        break;
      case L'%':
        if (options.literalstring[temp] != L'%') {
          clen = options.nlen;
          cset = options.num_charset;
        }
        break;
      case L'^':
        if (options.literalstring[temp] != L'^') {
          clen = options.slen;
          cset = options.sym_charset;
        }
        break;
      default: /* constant part of pattern */
        break;
    }
    if (cset) {
      for (index1 = 0; index1 < clen && cset[index1] != endstring[temp];)
        index1++;
      if (index1 == clen)
        index1 = clen - 1;
      for (index2 = 0; index2 < clen && cset[index2] != startstring[temp];)
        index2++;
      if (index2 == clen)
        index2 = 0;

      total_strings = (total_strings - 1) * clen + (unsigned long long)index1 - (unsigned long long)index2 + 1;
    }
  }

  return total_strings;
}

/* calculate the number of lines and bytes to output */
static void count_strings(unsigned long long *lines, unsigned long long *bytes, const options_type options) {
const wchar_t *startstring = options.startstring, *endstring = options.endstring;
size_t min = options.min, max = options.max;
size_t i, j;
unsigned long long temp;
int check_dupes; /* need to take duplicates into account */
unsigned long long extra_unicode_bytes = 0;

/* parameters for counting taking dupes into consideration */
size_t first, last; /* index of the first character and last character */
int start_point = 0, end_point = 0; /* bool; whether to consider a starting or ending string */

  if (max == 0) {
    *lines = 0;
    *bytes = 0;
    return;
  }

  if (output_unicode)
    suppress_finalsize = 1;

  /* Notes on unicode addition:
    If unicode output is enabled, *bytes will be wrong in here because
    it doesn't take into account the extra width of the unicode chars.
    But maybe we can easily calculate how many extra bytes will result
    and turn the suppress_finalsize flag back off so user gets the real size.
    We can only do this (with this approach anyway) if duplicates are not a
    factor, and if start/end strings are not specified.  So you will see this
    similar calculation done each time after the "normal" size is calculated.
    I have attempted to leave everything else as it was.  -jC */

  /* Check this just once up here so we don't have to clutter up stuff below -jC */
  if (options.pattern == NULL) {
    for (i = 0; i < max; i++) {
      if (options.pattern_info[i].is_fixed!=0 || options.pattern_info[i].cset==NULL || options.pattern_info[i].clen==0) {
        fprintf(stderr,"Error: pattern is unexpectedly NULL in unicode size calc sanity check\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  if (min == max) { /* strings of the same length */
    check_dupes = 0;
    for (i = 0; i < min; i++)
      if (options.pattern_info[i].duplicates < min)
        check_dupes = 1;
    if (check_dupes) { /* must take duplicates into account */
      first = 0;
      last = options.pattern_info[0].clen - 1;
      if (startstring) {
        first = options.pattern_info[0].start_index;
        start_point = 1;
      }
      if (endstring) {
        last = options.pattern_info[0].end_index;
        end_point = 1;
      }
      temp = calculate_with_dupes(start_point, end_point, first, last, 0, 0, 1, NULL, options, min);
    }
    else {
      temp = calculate_with_pattern(options.min_string, options.max_string, options);
    }

    if ((linecount > 0) && (options.endstring==NULL)) {
      *lines = linecount;
      *bytes = linecount * (max + 1);
    }
    else {
      *lines = temp;
      *bytes = temp * (max + 1);
    }

    extra_unicode_bytes = 0;

    if (output_unicode!=0 && check_dupes==0 && options.startstring==NULL && options.endstring==NULL) {
      for (i = 0; i < max; i++) {
        if (options.pattern_info[i].is_fixed!=0 || options.pattern_info[i].cset==NULL || options.pattern_info[i].clen==0)
          extra_unicode_bytes += (getmblen(options.pattern[i])-1)*(*lines);
        else
          extra_unicode_bytes += (wcstombs(NULL,options.pattern_info[i].cset,0)-options.pattern_info[i].clen)*(*lines)/options.pattern_info[i].clen;
      }
      *bytes += extra_unicode_bytes;

      /* Got the exact size in bytes so we can turn this off */
      suppress_finalsize = 0;
    }
  }
  else {
    /* add beginning from startstring to last_min */
    check_dupes = 0;
    for (i = 0; i < min; i++)
      if (options.pattern_info[i].duplicates < min)
        check_dupes = 1;
    if (check_dupes) { /* must take duplicates into account */
      first = 0;
      last = options.pattern_info[0].clen - 1;
      if (startstring) {
        first = options.pattern_info[0].start_index;
        start_point = 1;
      }
      temp = calculate_with_dupes(start_point, 0, first, last, 0, 0, 1, NULL, options, min);
    }
    else {
      if (startstring)
        temp = calculate_simple(startstring, options.last_min, options.low_charset, options.clen);
      else
        temp = (unsigned long long)pow((double)options.clen, (double)min);
    }

    *lines = temp;
    *bytes = temp * (min + 1);

    /* Extra unicode calc for what he calls the "beginning" (len=1->min) */
    if (output_unicode!=0 && check_dupes==0 && options.startstring==NULL && options.endstring==NULL) {
      extra_unicode_bytes = 0;
      for (i = 0; i < min; i++) {
        if (options.pattern_info[i].is_fixed!=0 || options.pattern_info[i].cset==NULL || options.pattern_info[i].clen==0)
          extra_unicode_bytes += (getmblen(options.pattern[i])-1)*(*lines);
        else
          extra_unicode_bytes += (wcstombs(NULL,options.pattern_info[i].cset,0)-options.pattern_info[i].clen)*(*lines)/options.pattern_info[i].clen;
      }
      *bytes += extra_unicode_bytes;
      suppress_finalsize = 0;
    }
    /* From here on out we will only do that similar calc
      if suppress_finalsize was already false, and actually
      we'll set it to true if we encounter anything we can't handle.*/

    /* add middle permutations */
    for (i = min + 1; i < max; i++) {
      /* i is 1 past the array index, careful here -jC */
      first = 0;
      last = options.pattern_info[0].clen - 1;
      check_dupes = 0;
      for (j = 0; j < i; j++)
        if (options.pattern_info[j].duplicates < i)
          check_dupes = 1;
      if (check_dupes)  /* must take duplicates into account */
        temp = calculate_with_dupes(0, 0, first, last, 0, 0, 1, NULL, options, i);
      else
        temp = (unsigned long long)pow((double)options.clen, (double)i);

      *lines += temp;
      *bytes += temp * (i+1);

      if (output_unicode!=0) {
        if (suppress_finalsize==0 && check_dupes==0) {
          extra_unicode_bytes = 0;
          for (j = 0; j < i; j++) {
            if (options.pattern_info[j].is_fixed!=0 || options.pattern_info[j].cset==NULL || options.pattern_info[j].clen==0)
              extra_unicode_bytes += (getmblen(options.pattern[j])-1)*temp;
            else
              extra_unicode_bytes += (wcstombs(NULL,options.pattern_info[j].cset,0)-options.pattern_info[j].clen)*temp/options.pattern_info[j].clen;
          }
          *bytes += extra_unicode_bytes;
        }
        else
          suppress_finalsize = 1;
      }
    }

    /* add ending from first_max to endstring */
    check_dupes = 0;
    for (i = 0; i < max; i++)
      if (options.pattern_info[i].duplicates < max)
        check_dupes = 1;
    if (check_dupes) { /* must take duplicates into account */
      first = 0;
      last = options.pattern_info[0].clen - 1;
      if (endstring) {
        last = options.pattern_info[0].end_index;
        end_point = 1;
      }
      temp = calculate_with_dupes(0, end_point, first, last, 0, 0, 1, NULL, options, max);
    }
    else {
      if (endstring)
        temp = calculate_simple(options.first_max, endstring, options.low_charset, options.clen);
      else
        temp = (unsigned long long)pow((double)options.clen, (double)max);
    }

    if ((linecount > 0) && (options.endstring==NULL)) {
      *lines += linecount;
      *bytes += linecount * (max + 1);
    }
    else {
      *lines += temp;
      *bytes += temp * (max + 1);
    }

    if (output_unicode!=0) {
      if (suppress_finalsize==0 && check_dupes==0) {
        extra_unicode_bytes = 0;
        for (j = 0; j < max; j++) {
          if (options.pattern_info[j].is_fixed!=0 || options.pattern_info[j].cset==NULL || options.pattern_info[j].clen==0)
            extra_unicode_bytes += (getmblen(options.pattern[j])-1)*temp;
          else
            extra_unicode_bytes += (wcstombs(NULL,options.pattern_info[j].cset,0)-options.pattern_info[j].clen)*temp/options.pattern_info[j].clen;
        }
        *bytes += extra_unicode_bytes;
      }
      else
        suppress_finalsize = 1;
    }
  }
}

static int finished(const wchar_t *block, const options_type options) {
size_t i;
  if (options.pattern == NULL) {
    for (i = 0; i < wcslen(block); i++)
      if (inc[i] < options.clen-1)
        return 0;
  }
  else {
    for (i = 0; i < wcslen(block); i++) {
      if (((options.pattern[i] == L'@') && (inc[i] < options.clen-1) && (options.literalstring[i] != L'@')) || \
          ((options.pattern[i] == L',') && (inc[i] < options.ulen-1) && (options.literalstring[i] != L',')) || \
          ((options.pattern[i] == L'%') && (inc[i] < options.nlen-1) && (options.literalstring[i] != L'%')) || \
          ((options.pattern[i] == L'^') && (inc[i] < options.slen-1) && (options.literalstring[i] != L'^'))) {
        return 0;
      }
    }
  }
  return 1;
}

static int too_many_duplicates(const wchar_t *block, const options_type options) {
wchar_t current_char = L'\0';
size_t dupes_seen = 0;
  
  while (*block != L'\0') {
    if (*block == current_char) {
      dupes_seen += 1;
      /* check for overflow of duplicates */
      if (dupes_seen > options.duplicates[0]) {
        if (find_index(options.low_charset, options.clen, current_char) != NPOS)
          return 1;
      }
      if (dupes_seen > options.duplicates[1]) {
        if (find_index(options.upp_charset, options.ulen, current_char) != NPOS)
          return 1;
      }
      if (dupes_seen > options.duplicates[2]) {
        if (find_index(options.num_charset, options.nlen, current_char) != NPOS)
          return 1;
      }
      if (dupes_seen > options.duplicates[3]) {
        if (find_index(options.sym_charset, options.slen, current_char) != NPOS)
          return 1;
      }
    }
    else {
      current_char = *block;
      dupes_seen = 1;
    }
    block++;
  }
  return 0;
}

static void increment(wchar_t *block, const options_type options) {
size_t i, start, stop;
int step;
size_t blocklen = wcslen(block);
size_t violator_pos = NPOS;
int can_inc_before_violator = 0; /*bool*/
int reached_violator = 0; /*bool*/
wchar_t prev_char = L'\0';
size_t consecutive_dupes = 0;

const wchar_t *matching_set;
size_t mslen = 0;

  if ((options.low_charset == NULL) || (options.upp_charset == NULL) || (options.num_charset == NULL) || (options.sym_charset == NULL)) {
     fprintf(stderr,"increment: SOMETHING REALLY BAD HAPPENED\n");
     exit(EXIT_FAILURE);
  }

  /*
      Starting at the "beginning" of string (assuming !inverted),
      find first character which violates max duplicates
      which is NOT a fixed character.
      Be aware that block2 may contain e.g.
      "dddaaa" but if pattern is "ddd@@@" only the 'a's should
      can be examined.  This is necessary because permute may
      be in use and we obviously can't skip over combinations of duplicate
      characters which are used as placeholders for the permuted words.

      If we do find such a character we will be forcing an increment
      at that position (or in front of it) and zero everything behind it.

      There must be one incrementable before that position though,
      otherwise we are completely done and can ignore what we found above.
      If this check wasn't done we'd run through the end because
      finish() and everything else expects that last combination
      to be returned even if it has too many dupes.
  */

  if (inverted == 1) {
    start = blocklen-1;
    stop = (size_t)-1;
    step = -1;
  }
  else {
    start = 0;
    stop = blocklen;
    step = 1;
  }

  for (i = start; i != stop; i += step) {
    if (options.pattern == NULL || (wcschr(L"@,%^",options.pattern[i])!=NULL
        && options.pattern[i]!=options.literalstring[i])) {

      if (can_inc_before_violator==0 && inc[i] < options.pattern_info[i].clen-1)
        can_inc_before_violator = 1;

      if (block[i] == prev_char) {
        if (++consecutive_dupes > options.pattern_info[i].duplicates) {
          if (can_inc_before_violator==1)
            violator_pos = i; /* Found him.  Bad boy! */
          break;
        }
      }
      else {
        prev_char = block[i];
        consecutive_dupes = 1;
      }
    }
    else
      prev_char = L'\0';
  }

  /* increment from end of string */

  if (inverted == 0) {
    start = blocklen-1;
    stop = (size_t)-1;
    step = -1;
  }
  else {
    start = 0;
    stop = blocklen;
    step = 1;
  }

  if (violator_pos == NPOS)
    reached_violator = 1; /*already handled because wasn't there to begin with*/

  for (i = start; i != stop; i += step) {
    if (i==violator_pos)
      reached_violator = 1;

    if (options.pattern == NULL) {
      matching_set = options.low_charset;
      mslen = options.clen;
    }
    else {
      switch (options.pattern[i]) {
        case L'@':
          matching_set = options.low_charset;
          mslen = options.clen;
          break;
        case L',':
          matching_set = options.upp_charset;
          mslen = options.ulen;
          break;
        case L'%':
          matching_set = options.num_charset;
          mslen = options.nlen;
          break;
        case L'^':
          matching_set = options.sym_charset;
          mslen = options.slen;
          break;
        default:
          matching_set = NULL;
      }
    }
    if (matching_set == NULL || (options.pattern != NULL && options.literalstring[i] == options.pattern[i])) {
      /* options.pattern cannot be null here due to logic above at top of loop */
      block[i] = options.pattern[i]; /* add pattern letter to word */
    }
    else {
      if (inc[i] < mslen-1 && reached_violator==1) {
        block[i] = matching_set[++inc[i]];
        break;
      }
      else {
        block[i] = matching_set[0];
        inc[i] = 0;
      }
    }
  }
}

static void *PrintPercentage(void *threadarg) {
struct thread_data *threaddata;
unsigned long long linec;
unsigned long long counter;
unsigned long long calc = 0;

  threaddata = (struct thread_data *) threadarg;

  while (1 != 0) {
    (void)sleep(10);

    /* Progress calc now based on line count rather than bytes due to unicode issues */

    linec = threaddata->finallinecount;
    counter = threaddata->linetotal;

    if (linec)
      calc = 100L * counter / linec;

    if (calc < 100)
      fprintf(stderr,"\ncrunch: %3llu%% completed generating output\n", calc);
  }

  pthread_exit(NULL);

  return (void *)1;
}

static void renamefile(const size_t end, const char *fpath, const char *outputfilename, const char *compressalgo) {
FILE *optr;     /* ptr to START output file; will be renamed later */
char *newfile;  /* holds the new filename */
char *finalnewfile; /*final filename with escape characters */
char *comptype; /* build -t string for 7z */
char *compoutput; /* build archive string for 7z */
char *findit = NULL;   /* holds location of / character */
int status;     /* rename returns int */
char buff[512]; /* buffer to hold line from wordlist */
pid_t pid; /*  pid and pid return */

  errno=0;
  memset(buff,0,sizeof(buff));

  fprintf(stderr,"\ncrunch: %3d%% completed generating output\n", (int)(100L * my_thread.linetotal / my_thread.finallinecount));

  finalnewfile = calloc((end*3)+5+strlen(fpath), sizeof(char)); /* max length will be 3x outname */
  if (finalnewfile == NULL) {
    fprintf(stderr,"rename: can't allocate memory for finalnewfile\n");
    exit(EXIT_FAILURE);
  }

  newfile = calloc((end*3)+5+strlen(fpath), sizeof(char)); /* max length will be 3x outname */
  if (newfile == NULL) {
    fprintf(stderr,"rename: can't allocate memory for newfile\n");
    exit(EXIT_FAILURE);
  }

  if (compressalgo != NULL) {
    comptype = calloc(strlen(compressalgo)+3, sizeof(char)); /* -t bzip2 plus CR */
    if (newfile == NULL) {
      fprintf(stderr,"rename: can't allocate memory for comptype\n");
      exit(EXIT_FAILURE);
    }
  }
  
  compoutput = calloc((end*3)+5+strlen(fpath), sizeof(char)); /* max length will be 3x outname */
  if (newfile == NULL) {
    fprintf(stderr,"rename: can't allocate memory for compoutput\n");
    exit(EXIT_FAILURE);
  }

  if (strncmp(outputfilename, fpath, strlen(fpath)) != 0) {
    status = rename(fpath, outputfilename); /* rename from START to user specified name */
    if (status != 0) {
      fprintf(stderr,"Error renaming file.  Status1 = %d  Code = %d\n",status,errno);
      fprintf(stderr,"The problem is = %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  else {
    if ((optr = fopen(fpath,"r")) == NULL) {
      fprintf(stderr,"rename: File START could not be opened\n");
      exit(EXIT_FAILURE);
    }
    else {  /* file opened above now read first line */
      (void)fgets(buff, (int)sizeof(buff), optr);
      strncat(newfile, buff, strlen(buff)-1); /* get rid of CR */
      while (feof(optr) == 0) {
        (void)fgets(buff, (int)sizeof(buff), optr);
      } /* all of this just to get last line */
      if (fclose(optr) != 0) {
        fprintf(stderr,"rename: fclose returned error number = %d\n", errno);
        fprintf(stderr,"The problem is = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
    }
    strcat(newfile, "-"); /* build new filename */
    strncat(newfile, buff, strlen(buff)-1); /* get rid of CR */

    strncpy(finalnewfile,fpath,strlen(fpath)-5);

    findit = strstr(newfile,"/");
    if (findit == NULL) {
      strncat(finalnewfile,newfile,strlen(newfile));
      strncat(finalnewfile, ".txt", 4);
    }
    else {
      while ((findit = strchr(newfile, '/')) != NULL) {
        *findit++ = ' ';
      }
      strncat(finalnewfile,newfile,strlen(newfile));
      strncat(finalnewfile, ".txt", 4);
    }

    status = rename(fpath, finalnewfile); /* rename START to proper filename */
    if (status != 0) {
      fprintf(stderr,"Error renaming file.  Status2 = %d  Code = %d\n",status,errno);
      fprintf(stderr,"The problem is = %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (compressalgo != NULL) {
    /*@-type@*/
    pid = fork();
    (void)wait(&status);

    /*@=type@*/
    if (pid == 0) {
      strncat(comptype,"-t", 2);
      strncat(comptype, compressalgo, strlen(compressalgo));

      if (strncmp(outputfilename, fpath, 5) == 0) {
        strcat(compoutput, finalnewfile);

        if (strncmp(compressalgo, "lzma", 4) == 0) {
          fprintf(stderr,"Beginning lzma compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", finalnewfile, NULL);
        }
        if (strncmp(compressalgo, "bzip2", 5) == 0) {
          fprintf(stderr,"Beginning bzip2 compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", finalnewfile, NULL);
        }
        if (strncmp(compressalgo, "gzip", 4) == 0) {
          fprintf(stderr,"Beginning gzip compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", finalnewfile, NULL);
        }
        if (strncmp(compressalgo, "7z", 2) == 0) {
          strcat(compoutput, ".7z");
          status=execlp("7z", "7z", "a", comptype, "-mx=9", compoutput, finalnewfile, NULL);
        }
      }
      else {
        strcat(compoutput, outputfilename);

        if (strncmp(compressalgo, "lzma", 4) == 0) {
          strcat(compoutput, ".lzma");
          fprintf(stderr,"Beginning lzma compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", outputfilename, NULL);
        }
        if (strncmp(compressalgo, "bzip2", 5) == 0) {
          fprintf(stderr,"Beginning bzip2 compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", outputfilename, NULL);
        }
        if (strncmp(compressalgo, "gzip", 4) == 0) {
          fprintf(stderr,"Beginning gzip compression.  Please wait.\n");
          status=execlp(compressalgo, compressalgo, "-9", "-f", "-v", outputfilename, NULL);
        }
        if (strncmp(compressalgo, "7z", 2) == 0) {
          strcat(compoutput, ".7z");
          status=execlp("7z", "7z", "a", comptype, "-mx=9", compoutput, outputfilename, NULL);
        }
      }

      if (status != 0) {
        fprintf(stderr,"Error compressing file.  Status = %d  Code = %d\n", status, errno);
        fprintf(stderr,"The problem is = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }

      if (strncmp(compressalgo, "lzma", 4) != 0) {
        if (strncmp(outputfilename, fpath, 5) == 0) 
          status = remove(finalnewfile);
        else
          status = remove(outputfilename);

        if (status != 0) {
          fprintf(stderr,"Error deleting file.  Status = %d  Code = %d\n", status, errno);
          fprintf(stderr,"The problem is = %s\n", strerror(errno));
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  free(newfile);
  free(finalnewfile);
  free(compoutput);
  if (compressalgo != NULL)
    free(comptype);
}


static void printpermutepattern(const wchar_t *block2, const wchar_t *pattern, const wchar_t *literalstring, wchar_t **wordarray) {
size_t j, t;
char mb[MB_CUR_MAX+1];
int mblen = 0;

  for (t = 0, j = 0; t < wcslen(pattern); t++) {
    if ((pattern[t] == L'@') || (pattern[t] == L',') || (pattern[t] == L'%') ||  (pattern[t] == L'^')) {
      switch (pattern[t]) {
      case L'@':
        if (literalstring[t] == L'@') {
          fprintf(fptr, "@");
          break;
        }
        /*@fallthrough@*/
      case L',':
        if (literalstring[t] == L',') {
          fprintf(fptr, ",");
          break;
        }
        /*@fallthrough@*/
      case L'%':
        if (literalstring[t] == L'%') {
          fprintf(fptr, "%%");
          break;
        }
        /*@fallthrough@*/
      case L'^':
        if (literalstring[t] == L'^') {
          fprintf(fptr, "^");
          break;
        }
        /*@fallthrough@*/
      default:
        /*fprintf(fptr, "%c", block2[t]);*/
        if (!output_unicode)
          fprintf(fptr, "%c", (char)(block2[t]&0xFF));
        else {
          mblen = wctomb(mb,block2[t]);
          if (mblen == -1) {
            fprintf(stderr,"Error: wctomb failed for char U+%04lX\n",(unsigned long)block2[t]);
            exit(EXIT_FAILURE);
          }
          mb[mblen]='\0';
          fprintf(fptr, "%s", mb);

          if (mblen > 1) {
            /* bytecounter will be incremented by 1 below, so just do one less here*/
            my_thread.bytecounter += (mblen-1);
          }
        }
      }
      my_thread.bytecounter+=1;
    }
    else {
      (void)make_narrow_string(gconvbuffer,wordarray[j],gconvlen);
      fprintf(fptr, "%s", gconvbuffer);
      my_thread.bytecounter+=strlen(gconvbuffer);

      j++;
    }
  }
  fprintf(fptr, "\n");
  my_thread.bytecounter++;
  my_thread.linecounter++;
}

static void Permute(const char *fpath, const char *outputfilename, const char *compressalgo, wchar_t **wordarray, const options_type options, const size_t sizePerm, size_t unchanged) {
size_t outer = 0;
size_t inner = 0;
size_t wordlength = 0;
size_t t;
wchar_t *temp[1];
wchar_t *block2;      /* block is word being created */

  errno = 0;

  if (sizePerm > unchanged) {
    for(outer = unchanged; outer < sizePerm; outer++) {
      *temp = wordarray[outer];
      for(inner = outer; inner > unchanged; inner--) {
        wordarray[inner] = wordarray[inner - 1];
      }
      wordarray[unchanged] = *temp;
      Permute(fpath, outputfilename, compressalgo, wordarray, options, sizePerm, unchanged+1);

      for(inner = unchanged; inner < outer; inner++) {
        wordarray[inner] = wordarray[inner + 1];
      }
      wordarray[outer] = *temp;
    }
  }
  else {
    if (outputfilename == NULL) {
      if (options.pattern == NULL) {
        for (t = 0; t < sizePerm; t++) {
          (void)make_narrow_string(gconvbuffer,wordarray[t],gconvlen);
          fprintf(fptr, "%s", gconvbuffer);
        }
        fprintf(fptr, "\n");
      }
      else {
          block2 = calloc(options.plen+1,sizeof(wchar_t)); /* block can't be bigger than max size */
          if (block2 == NULL) {
            fprintf(stderr,"permute: can't allocate memory for block2\n");
            exit(EXIT_FAILURE);
          }

          for (t = 0; t < options.plen; t++) {
            switch (options.pattern[t]) {
              case L'@':
                block2[t] = options.low_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              case L',':
                block2[t] = options.upp_charset[0]; /* placeholder is set so add   character */
                inc[t] = 0;
                break;
              case L'%':
                block2[t] = options.num_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              case L'^':
                block2[t] = options.sym_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              default:
                block2[t] = ' '; /* add pattern letter to word */
            }
          } /* for t=0 */

          while (!finished(block2, options) && !ctrlbreak) {
              if (!too_many_duplicates(block2, options))
                printpermutepattern(block2, options.pattern, options.literalstring, wordarray);
              increment(block2, options);
          }
          if (!too_many_duplicates(block2, options))
            printpermutepattern(block2, options.pattern, options.literalstring, wordarray);
          free(block2);
      }
    }
    else {
      size_t outlen;
      
      if ((fptr = fopen(fpath,"a+")) == NULL) { /* append to file */
        fprintf(stderr,"permute: File START could not be opened\n");
        fprintf(stderr,"The problem is = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      else {
        for (t = 0; t < sizePerm; t++) {
          outlen = make_narrow_string(gconvbuffer,wordarray[t],gconvlen);
          wordlength += outlen;
        }
        wordlength++; /*for cr*/
        if (options.pattern == NULL) {
          if ((my_thread.linecounter <= (linecount-1)) && (my_thread.bytecounter <= (bytecount - wordlength))) { /* not time to create a new file */
            for (t = 0; t < sizePerm; t++) {
              (void)make_narrow_string(gconvbuffer,wordarray[t],gconvlen);
              fprintf(fptr, "%s", gconvbuffer);
            }
            my_thread.bytecounter+=wordlength;
            fprintf(fptr, "\n");
            my_thread.linecounter++;
          }
          else {
            my_thread.bytetotal+=my_thread.bytecounter;
            my_thread.linetotal+=my_thread.linecounter;

            if (fclose(fptr) != 0) {
              fprintf(stderr,"permute: fclose returned error number = %d\n", errno);
              fprintf(stderr,"The problem is = %s\n", strerror(errno));
              exit(EXIT_FAILURE);
            }

            renamefile(((wordlength*2)+5), fpath, outputfilename, compressalgo);
            if ((fptr = fopen(fpath, "w")) == NULL) {
              fprintf(stderr,"permute2: Ouput file START could not be opened\n");
              exit(EXIT_FAILURE);
            }
            my_thread.linecounter = 0;
            my_thread.bytecounter = 0;
            for (t = 0; t < sizePerm; t++) {
              (void)make_narrow_string(gconvbuffer,wordarray[t],gconvlen);
              fprintf(fptr, "%s", gconvbuffer);
            }
            my_thread.bytecounter+=wordlength;
            fprintf(fptr, "\n");
            my_thread.linecounter++;
          }
        }
        else { /* user specified a pattern */
          block2 = calloc(options.plen+1,sizeof(wchar_t)); /* block can't be bigger than max size */
          if (block2 == NULL) {
            fprintf(stderr,"permute2: can't allocate memory for block2\n");
            exit(EXIT_FAILURE);
          }

          for (t = 0; t < options.plen; t++) {
            switch (options.pattern[t]) {
              case L'@':
                block2[t] = options.low_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              case L',':
                block2[t] = options.upp_charset[0]; /* placeholder is set so add   character */
                inc[t] = 0;
                break;
              case L'%':
                block2[t] = options.num_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              case L'^':
                block2[t] = options.sym_charset[0]; /* placeholder is set so add character */
                inc[t] = 0;
                break;
              default:
                block2[t] = L' '; /* add pattern letter to word */
            }
          } /* for t=0 */

          while (!finished(block2, options) && !ctrlbreak) {
            if ((my_thread.linecounter <= (linecount-1)) && (my_thread.bytecounter <= (bytecount - wordlength))) { /* not time to create a new file */
              if (!too_many_duplicates(block2, options))
                printpermutepattern(block2, options.pattern, options.literalstring, wordarray);
              increment(block2, options);
            }
            else {
              my_thread.bytetotal+=my_thread.bytecounter;
              my_thread.linetotal+=my_thread.linecounter;

              if (fptr == NULL) {
                fprintf(stderr,"permute: something really bad happened!\n");
                exit(EXIT_FAILURE);
              }
              else {
                if (fclose(fptr) != 0) {
                  fprintf(stderr,"permute2: fclose returned error number = %d\n", errno);
                  fprintf(stderr,"The problem is = %s\n", strerror(errno));
                  exit(EXIT_FAILURE);
                }
              }

              renamefile(((wordlength*2)+5), fpath, outputfilename, compressalgo);
              if ((fptr = fopen(fpath, "w")) == NULL) {
                fprintf(stderr,"permute2: Ouput file START could not be opened\n");
                free(block2);
                exit(EXIT_FAILURE);
              }
              my_thread.linecounter = 0;
              my_thread.bytecounter = 0;
            }
          }
          if (!too_many_duplicates(block2, options))
            printpermutepattern(block2, options.pattern, options.literalstring, wordarray);
          free(block2);
        }

        if (fptr == NULL) {
          fprintf(stderr,"permute2: something really bad happened!\n");
          exit(EXIT_FAILURE);
        }
        else {
          if (ferror(fptr) != 0) {
            fprintf(stderr,"permute2: fprintf failed = %d\n", errno);
            fprintf(stderr,"The problem is = %s\n", strerror(errno));
            exit(EXIT_FAILURE);
          }
          if (fclose(fptr) != 0) {
            fprintf(stderr,"permute3: fclose returned error number = %d\n", errno);
            fprintf(stderr,"The problem is = %s\n", strerror(errno));
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
}

static void Permutefilesize(wchar_t **wordarray, const size_t sizePerm, const size_t length, size_t unchanged) {
size_t outer = 0;
size_t inner = 0;
size_t t;
wchar_t *temp[1];

  if (sizePerm > unchanged) {
    for(outer = unchanged; outer < sizePerm; outer++) {
      *temp = wordarray[outer];
      for(inner = outer; inner > unchanged; inner--) {
        wordarray[inner] = wordarray[inner - 1];
      }
      wordarray[unchanged] = *temp;
      Permutefilesize(wordarray, sizePerm, length, unchanged+1);

      for(inner = unchanged; inner < outer; inner++) {
        wordarray[inner] = wordarray[inner + 1];
      }
      wordarray[outer] = *temp;
    }
  }
  else {
    for (t = 0; t < length; t++) {
      if (!output_unicode)
        my_thread.bytecounter += wcslen(wordarray[t]);
      else
        my_thread.bytecounter += wcstombs(NULL,wordarray[t],0);
    }
    my_thread.bytecounter++;
  }
}

static void loadstring(wchar_t *block2, const size_t j, const wchar_t *startblock, const options_type options) {
size_t k;

  if (startblock == NULL) { /* is startblock null? */
    if (options.pattern == NULL) { /* Yes so now test if pattern null? */
      block2[j] = options.low_charset[0]; /* pattern is null so add character */
      inc[j] = 0;
    }
    else { /* pattern is not null */
      switch (options.pattern[j]) {
        case L'@':
          if (options.literalstring[j] != L'@') {
            block2[j] = options.low_charset[0]; /* placeholder is set so add character */
            inc[j] = 0;
          }
          else {
           block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
          break;
        case L',':
          if (options.literalstring[j] != L',') {
            block2[j] = options.upp_charset[0]; /* placeholder is set so add character */
            inc[j] = 0;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
          break;
        case L'%':
          if (options.literalstring[j] != L'%') {
            block2[j] = options.num_charset[0]; /* placeholder is set so add character */
            inc[j] = 0;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
          break;
        case L'^':
          if (options.literalstring[j] != L'^') {
            block2[j] = options.sym_charset[0]; /* placeholder is set so add character */
            inc[j] = 0;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
          break;
        default:
          block2[j] = options.pattern[j]; /* add pattern letter to word */
        }
      }
    }
  else { /* startblock is not null */
    if (options.pattern == NULL) { /* Yes so now test if pattern null? */
      block2[j] = startblock[j]; /* pattern is null so add character */
      for(k = 0; k < wcslen(options.low_charset); k++) {
        if (block2[j] == options.low_charset[k]) {
          inc[j] = k;
        }
      }
    }
    else {
      switch (options.pattern[j]) {
        case L'@':
          if (options.literalstring[j] != L'@') {
            block2[j] = startblock[j]; /* pattern is null so add character */
            for(k = 0; k < wcslen(options.low_charset); k++)
              if (block2[j] == options.low_charset[k])
                inc[j] = k;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
        break;
        case L',':
          if (options.literalstring[j] != L',') {
            block2[j] = startblock[j]; /* pattern is null so add character */
            for(k = 0; k < wcslen(options.upp_charset); k++)
              if (block2[j] == options.upp_charset[k])
                inc[j] = k;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
        break;
        case L'%':
          if (options.literalstring[j] != L'%') {
            block2[j] = startblock[j]; /* pattern is null so add character */
            for(k = 0; k < wcslen(options.num_charset); k++)
              if (block2[j] == options.num_charset[k])
                inc[j] = k;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
        break;
        case L'^':
          if (options.literalstring[j] != L'^') {
            block2[j] = startblock[j]; /* pattern is null so add character */
            for(k = 0; k < wcslen(options.sym_charset); k++)
              if (block2[j] == options.sym_charset[k])
                inc[j] = k;
          }
          else {
            block2[j] = options.pattern[j]; /* add pattern letter to word */
          }
        break;
        default:
          block2[j] = options.pattern[j]; /* add pattern letter to word */
      }
    }
  }
}

static void chunk(const size_t start, const size_t end, const wchar_t *startblock, const options_type options, const char *fpath, const char *outputfilename, const char *compressalgo) {
size_t i,j;      /* loop counters */
wchar_t *block2;      /* block is word being created */
size_t outlen; /* temp for size of narrow output string */

  errno = 0;
  block2 = calloc(end+1,sizeof(wchar_t)); /* block can't be bigger than max size */
  if (block2 == NULL) {
    fprintf(stderr,"chunk: can't allocate memory for block2\n");
    exit(EXIT_FAILURE);
  }

  for (i = start; (i <= end) && !ctrlbreak; i++) {
    for (j = 0; j < i; j++) {
      loadstring(block2, j, startblock, options);
    }
    startblock = NULL;

    if (outputfilename == NULL) { /* user wants to display words on screen */
      if (options.endstring == NULL) {
        while ((!finished(block2,options) && !ctrlbreak) && (my_thread.linecounter < (linecount-1))) {
          if (!too_many_duplicates(block2, options)) {
            (void)make_narrow_string(gconvbuffer,block2,gconvlen);
            fprintf(fptr, "%s\n", gconvbuffer);
            my_thread.linecounter++;
          }
          increment(block2, options);
        }
        if (!too_many_duplicates(block2, options)) { /*flush last word */
          (void)make_narrow_string(gconvbuffer,block2,gconvlen);
          fprintf(fptr, "%s\n", gconvbuffer);
        }
        if (my_thread.linecounter == (linecount-1)) {
          goto killloop;
        }
      }
      else {
        while (!finished(block2,options) && !ctrlbreak && (wcsncmp(block2,options.endstring,wcslen(options.endstring)) != 0) ) {
          if (!too_many_duplicates(block2, options)) {
            (void)make_narrow_string(gconvbuffer,block2,gconvlen);
            fprintf(fptr, "%s\n", gconvbuffer);
            my_thread.linecounter++;
          }
          increment(block2, options);
        }
        if (!too_many_duplicates(block2, options)) { /*flush last word */
          (void)make_narrow_string(gconvbuffer,block2,gconvlen);
          fprintf(fptr, "%s\n", gconvbuffer);
        }
        if (wcsncmp(block2,options.endstring,wcslen(options.endstring)) == 0)
          break;
      }
    }
    else { /* user wants to generate a file */
      if ((fptr = fopen(fpath,"a+")) == NULL) { /* append to file */
        fprintf(stderr,"chunk1: File START could not be opened\n");
        fprintf(stderr,"The problem is = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      else { /* file opened start writing.  file will be renamed when done */
        while (!finished(block2, options) && (ferror(fptr) == 0) && !ctrlbreak) {
          if ((options.endstring != NULL) && (wcsncmp(block2,options.endstring,wcslen(options.endstring)) == 0))
            break;

          outlen = make_narrow_string(gconvbuffer,block2,gconvlen);

          if ((my_thread.linecounter <= (linecount-1)) && (my_thread.bytecounter <= (bytecount - outlen))) { /* not time to create a new file */
            if (!too_many_duplicates(block2, options)) {
              fprintf(fptr, "%s\n", gconvbuffer);
              if (ferror(fptr) != 0) {
                fprintf(stderr,"chunk1: fprintf failed = %d\n", errno);
                fprintf(stderr,"The problem is = %s\n", strerror(errno));
                free(block2);
                exit(EXIT_FAILURE);
              }
              my_thread.bytecounter += (unsigned long long)outlen+1;
              my_thread.linecounter++;
              my_thread.linetotal++;
            }
            increment(block2,options);
          }
          else { /* time to create a new file */
            my_thread.bytetotal+=my_thread.bytecounter;

            if (fclose(fptr) != 0) {
              fprintf(stderr,"chunk1: fclose returned error number = %d\n",errno);
              fprintf(stderr,"The problem is = %s\n", strerror(errno));
              free(block2);
              exit(EXIT_FAILURE);
            }
            renamefile(end, fpath, outputfilename, compressalgo);

            if ((options.endstring == NULL) || (wcsncmp(block2,options.endstring,wcslen(options.endstring)) != 0)) {
              if ((fptr = fopen(fpath, "w")) == NULL) {
                fprintf(stderr,"chunk2: Ouput file START could not be opened\n");
                free(block2);
                exit(EXIT_FAILURE);
              }
              my_thread.linecounter = 0;
              my_thread.bytecounter = 0;
            }
            else {
              goto killloop;
            }
          }
        }

        if (fptr == NULL) {
          fprintf(stderr,"chunk: something really bad happened\n");
          exit(EXIT_FAILURE);
        }
        else {
          if (!too_many_duplicates(block2, options)) {

            outlen = make_narrow_string(gconvbuffer,block2,gconvlen);
            fprintf(fptr, "%s\n", gconvbuffer); /* flush the last word */

            my_thread.linecounter++;
            my_thread.linetotal++;
            my_thread.bytecounter += (unsigned long long)outlen+1;

            if (ferror(fptr) != 0) {
              fprintf(stderr,"chunk2: fprintf failed = %d\n", errno);
              fprintf(stderr,"The problem is = %s\n", strerror(errno));
              free(block2);
              exit(EXIT_FAILURE);
            }
          }
          if (fclose(fptr) != 0) {
            fprintf(stderr,"chunk2: fclose returned error number = %d\n", errno);
            fprintf(stderr,"The problem is = %s\n", strerror(errno));
            free(block2);
            exit(EXIT_FAILURE);
          }

          if ((options.endstring != NULL) && (wcsncmp(block2,options.endstring,wcslen(options.endstring)) == 0))
            break;

          if (ctrlbreak == 1)
            break;
        }
      } /* else from if fopen */
    } /* else from outputfilename == NULL */
  } /* for start < end loop */

  if (ctrlbreak == 1 ) {
    (void)make_narrow_string(gconvbuffer,block2,gconvlen);
    fprintf(stderr,"Crunch ending at %s\n",gconvbuffer);
  }

  killloop:
  my_thread.bytetotal += my_thread.bytecounter;

  if ((outputfilename != NULL) && !ctrlbreak) {
    renamefile(end, fpath, outputfilename, compressalgo);
  }

  free(block2);
}

static void usage() {
  fprintf(stderr,"crunch version %s\n\n", version);
  fprintf(stderr,"Crunch can create a wordlist based on criteria you specify.  The outout from crunch can be sent to the screen, file, or to another program.\n\n");
  fprintf(stderr,"Usage: crunch <min> <max> [options]\n");
  fprintf(stderr,"where min and max are numbers\n\n");
  fprintf(stderr,"Please refer to the man page for instructions and examples on how to use crunch.\n");
}

static wchar_t *resumesession(const char *fpath, const wchar_t *charset) {
FILE *optr;     /* ptr to START output file; will be renamed later */
char buff[512]; /* buffer to hold line from wordlist */
wchar_t *startblock;
size_t j, k;

  errno = 0;
  memset(buff, 0, sizeof(buff));

  if ((optr = fopen(fpath,"r")) == NULL) {
    fprintf(stderr,"resume: File START could not be opened\n");
    exit(EXIT_FAILURE);
  }
  else {  /* file opened above now read first line */
    while (feof(optr) == 0) {
      (void)fgets(buff, (int)sizeof(buff), optr);
      ++my_thread.linecounter;
      my_thread.bytecounter += (unsigned long long)strlen(buff);
    } /* all of this just to get last line */
    my_thread.linecounter--; /* -1 to get correct num */
    my_thread.bytecounter -= (unsigned long long)strlen(buff);

    if (fclose(optr) != 0) {
      fprintf(stderr,"resume: fclose returned error number = %d\n", errno);
      fprintf(stderr,"The problem is = %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (buff[0])
      buff[strlen(buff)-1]='\0';

    startblock = alloc_wide_string(buff,NULL);

    fprintf(stderr,"Resuming from = %s\n", buff);

    for (j = 0; j < wcslen(startblock); j++) {
      for(k = 0; k < wcslen(charset); k++)
        if (startblock[j] == charset[k])
          inc[j] = k;
    }
    return startblock;
  }
}

/*@null@*/ static wchar_t *readcharsetfile(const char *charfilename, const char *charsetname, int* r_is_unicode) {
FILE *optr;  /* ptr to user specified charset file */
char *temp;  /* holds character set name from charset file */
char *chars; /* holds characters from specified charsetname i.e. stuff after [ */
char *charset = NULL; /* holds the characters to use (narrow) */
wchar_t* wcharset = NULL; /* wide version of charset, this is the return */
char buff[512]; /* buffer to hold line from charset file */

  errno = 0;
  memset(buff, 0, sizeof(buff));
  if ((optr = fopen(charfilename,"r")) == NULL) { /* open file to read from */
    fprintf(stderr,"readcharset: File %s could not be opened\n", charfilename);
    fprintf(stderr,"The problem is = %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  else {  /* file opened above now scan file for charsetname */
    while (fgets(buff, (int)sizeof(buff), optr) != NULL) {
      temp = strtok(buff, " ");
      if (strcmp(charsetname, temp)==0) {
        chars = strtok(NULL, "["); /* move to = sign in file */
        if ((chars = strtok(NULL, "\n")) != NULL) { /* get rest of string after [ */
          charset = calloc(strlen(chars), sizeof(char));
          if (charset == NULL) {
            fprintf(stderr,"readcharset: can't allocate memory for charset\n");
            exit(EXIT_FAILURE);
          }
          if (strncmp(&chars[(strlen(chars)-1)], "]", 1) == 0)
            memcpy(charset, chars, strlen(chars)-1); /* don't strip off space only ]*/
          else
            memcpy(charset, chars, strlen(chars)-2); /* strip off ] */

          wcharset = alloc_wide_string(charset, r_is_unicode);
          free(charset);
        }
        break;
      }
    }
    if (fclose(optr) != 0) {
      fprintf(stderr,"readcharset: fclose returned error number = %d\n", errno);
      fprintf(stderr,"The problem is = %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  return wcharset;
}

static wchar_t **readpermute(const char *charfilename, int* r_is_unicode) {
FILE *optr;  /* ptr to user specified charset file */
wchar_t **wordarray2; /* holds characters from specified charsetname */
/*@notnull@*/ char buff[512]; /* buffer to hold line from charset file */
size_t temp = 0;

  errno = 0;
  numofelements = 0;
  memset(buff, 0, sizeof(buff));
  if ((optr = fopen(charfilename,"r")) == NULL) { /* open file to read from */
    fprintf(stderr,"readpermute: File %s could not be opened\n", charfilename);
    fprintf(stderr,"The problem is = %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  else {  /* file opened above now get the number of line in file */
    while (fgets(buff, (int)sizeof(buff), optr) != NULL) {
      if (buff[0] != '\n')
        numofelements++;
    }
    (void)fseek(optr, 0, SEEK_SET);

    wordarray2 = calloc(numofelements, sizeof(wchar_t*));
    if (wordarray2 == NULL) {
      fprintf(stderr,"readpermute: can't allocate memory for wordarray1\n");
      exit(EXIT_FAILURE);
    }
    while (fgets(buff, (int)sizeof(buff), optr) != NULL) {
      if (buff[0] != '\n' && buff[0]!='\0') {
        buff[strlen(buff)-1]='\0';
        wordarray2[temp++] = alloc_wide_string(buff,r_is_unicode);
      }
    }

    if (fclose(optr) != 0) {
      fprintf(stderr,"readpermute: fclose returned error number = %d\n", errno);
      fprintf(stderr,"The problem is = %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  return wordarray2;
  }
}

static void copy_without_dupes(wchar_t* dest, wchar_t* src) {
  size_t i;
  size_t len = wcslen(src);

  dest[0]=L'\0';

  for (i = 0; i < len; ++i) {
    if (wcschr(dest,src[i])==NULL)
      wcsncat(dest,&src[i],1);
  }
}

int main(int argc, char **argv) {
size_t flag = 0;   /* 0 for chunk 1 for permute */
size_t flag3 = 0;  /* 0 display file size info 1 supress file size info */
size_t flag4 = 0;  /* 0 don't create thread 1 create print % done thread */
size_t resume = 0; /* 0 new session 1 for resume */
size_t arglen = 0; /* used in -b option to hold strlen */
size_t min, max;   /* minimum and maximum size */
size_t temp;       /* temp varible */
size_t templen;    /* another temp var */

unsigned long calc = 0;  /* recommend count */
size_t dupvalue; /* value for duplicates option */

int i = 3;      /* minimum number of parameters */
int ret = 0;    /* return value of pthread_create */
int multi = 0;

int saw_unicode_input = 0;

wchar_t *charset; /* character set */
wchar_t *upp_charset = NULL;
wchar_t  *num_charset = NULL;
wchar_t *sym_charset = NULL;
wchar_t *startblock = NULL; /* user specified starting point */
wchar_t *pattern = NULL;    /* user specified pattern */
char *fpath = NULL;          /* path to outputfilename if specified*/
char *outputfilename = NULL; /* user specified filename to write output to */
char *compressalgo = NULL;   /* user specified compression program */
wchar_t *endstring = NULL;      /* hold -e option */
char *charsetfilename = NULL;
char *tempfilename = NULL;
char *bcountval = NULL;
wchar_t *literalstring = NULL; /* user passed something using -l */
char *hold;
char *endptr; /* temp pointer for duplicates option */

wchar_t *tempwcs; /* temp used while converting input */

options_type options; /* store validated parameters passed to the program */

wchar_t **wordarray = NULL; /* array to store words */

pthread_t threads;

  (void) signal(SIGINT, ex_program);
//  (void) signal(SIGINFO, printme);

  memset(&threads,0,sizeof(threads));
  fptr = stdout;

  if (setlocale(LC_ALL, "")==NULL) {
    fprintf(stderr,"Error: setlocale() failed\n");
    exit(EXIT_FAILURE);
  }

  options.low_charset = options.upp_charset = options.num_charset = options.sym_charset = NULL;
  options.pattern = options.literalstring = NULL;
  options.startstring = options.endstring = NULL;
  options.last_min = options.first_max = NULL;
  options.min_string = options.max_string = NULL;
  options.pattern_info = NULL;

  if ((argc == 2) && (strncmp(argv[1], "-v", 2) == 0)) {  /* print version information */
    fprintf(stderr,"crunch version %s\n", version);
    return 0;
  }

  if (argc < 3) {
    usage();
    return 0;
  }

  gconvlen = MAXSTRING*MB_CUR_MAX+1;
  gconvbuffer = (char*)malloc(gconvlen);
  if (!gconvbuffer) {
    fprintf(stderr,"Error: Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  charset = dupwcs(def_low_charset);
  if (charset == NULL) {
    fprintf(stderr,"crunch: can't allocate memory for default charset\n");
    exit(EXIT_FAILURE);
  }

  upp_charset = dupwcs(def_upp_charset);
  if (upp_charset == NULL) {
    fprintf(stderr,"crunch: can't allocate memory for default upp_charset\n");
    exit(EXIT_FAILURE);
  }

  num_charset = dupwcs(def_num_charset);
  if (num_charset == NULL) {
    fprintf(stderr,"crunch: can't allocate memory for default num_charset\n");
    exit(EXIT_FAILURE);
  }

  sym_charset = dupwcs(def_sym_charset);
  if (sym_charset == NULL) {
    fprintf(stderr,"crunch: can't allocate memory for default sym_charset\n");
    exit(EXIT_FAILURE);
  }

  my_thread.finallinecount = my_thread.linecounter = my_thread.linetotal = 0;

  if (argc >= 4) {
    if ((argc > i) && (*argv[i] != '-')) { /*test for ./crunch 1 2 -? */
      if (*argv[i] != '+') {
        /* user specified charset */
        free(charset);

        templen = strlen(argv[i])+1;
        tempwcs = (wchar_t*)malloc(templen*sizeof(wchar_t));
        charset = (wchar_t*)malloc(templen*sizeof(wchar_t));
        if (tempwcs==NULL || charset==NULL) {
          fprintf(stderr,"crunch: can't allocate memory for user charset\n");
          exit(EXIT_FAILURE);
        }

        (void)make_wide_string(tempwcs,argv[i],templen,&saw_unicode_input);
        copy_without_dupes(charset, tempwcs);
        free(tempwcs);
      }
      i++; /* user specified a charset and a parameter */
    }

    if ((argc > i) && (*argv[i] != '-')) { /*test for ./crunch 1 2 -? */
      if (*argv[i] != '+') {
        /* user specified upp_charset */
        free(upp_charset);

        templen = strlen(argv[i])+1;
        tempwcs = (wchar_t*)malloc(templen*sizeof(wchar_t));
        upp_charset = (wchar_t*)malloc(templen*sizeof(wchar_t));

        if (tempwcs==NULL || upp_charset==NULL) {
          fprintf(stderr,"crunch: can't allocate memory for upp_charset\n");
          exit(EXIT_FAILURE);
        }

        (void)make_wide_string(tempwcs,argv[i],templen,&saw_unicode_input);
        copy_without_dupes(upp_charset, tempwcs);
        free(tempwcs);
      }
      i++; /* user specified a upp_charset and a parameter */
    }
    if ((argc > i) && (*argv[i] != '-')) { /*test for ./crunch 1 2 -? */
      if (*argv[i] != '+') {
        /* user specified num_charset */
        free(num_charset);

        templen = strlen(argv[i])+1;
        tempwcs = (wchar_t*)malloc(templen*sizeof(wchar_t));
        num_charset = (wchar_t*)malloc(templen*sizeof(wchar_t));

        if (tempwcs==NULL || num_charset==NULL) {
          fprintf(stderr,"crunch: can't allocate memory for num_charset\n");
          exit(EXIT_FAILURE);
        }

        (void)make_wide_string(tempwcs,argv[i],templen,&saw_unicode_input);
        copy_without_dupes(num_charset, tempwcs);
        free(tempwcs);
      }
      i++; /* user specified a num_charset and a parameter */
    }
    if ((argc > i) && (*argv[i] != '-')) { /*test for ./crunch 1 2 -? */
      if (*argv[i] != '+') {
        /* user specified sym_charset */
        free(sym_charset);

        templen = strlen(argv[i])+1;
        tempwcs = (wchar_t*)malloc(templen*sizeof(wchar_t));
        sym_charset = (wchar_t*)malloc(templen*sizeof(wchar_t));

        if (tempwcs==NULL || sym_charset==NULL) {
          fprintf(stderr,"crunch: can't allocate memory for sym_charset\n");
          exit(EXIT_FAILURE);
        }

        (void)make_wide_string(tempwcs,argv[i],templen,&saw_unicode_input);
        copy_without_dupes(sym_charset, tempwcs);
        free(tempwcs);
      }
      i++; /* user specified a sym_charset and a parameter */
    }
  }

  min = (size_t)atoi(argv[1]);
  max = (size_t)atoi(argv[2]);

  if (max < min) {
    fprintf(stderr,"Starting length is greater than the ending length\n");
    exit(EXIT_FAILURE);
  }

  if (max > MAXSTRING) {
    fprintf(stderr,"Crunch can only make words with a length of less than %d characters\n", MAXSTRING+1);
    exit(EXIT_FAILURE);
  }

  for (temp = 0; temp < 4; temp++)
    options.duplicates[temp] = (size_t)-1;

  for (; i<argc; i+=2) { /* add 2 to skip the parameter value */
    if (strncmp(argv[i], "-b", 2) == 0) { /* user wants to split files by size */
      if (i+1 < argc) {
        bcountval = argv[i+1];
        if (bcountval != NULL) {
          arglen = strlen(bcountval);

          for (temp = 0; temp < arglen; temp++)
            bcountval[temp] = tolower(bcountval[temp]);

          if (strstr(bcountval, "kb") != 0) multi=1000;
          else if (strstr(bcountval, "mb")  != 0) multi = 1000000;
          else if (strstr(bcountval, "gb")  != 0) multi = 1000000000;
          else if (strstr(bcountval, "kib") != 0) multi = 1024;
          else if (strstr(bcountval, "mib") != 0) multi = 1048576;
          else if (strstr(bcountval, "gib") != 0) multi = 1073741824;

          calc = strtoul(bcountval, NULL, 10);
          bytecount = calc * multi;
          if (calc > 4 && multi >= 1073741824 && bytecount <= 4294967295ULL) {
            fprintf(stderr,"ERROR: Your system is unable to process numbers greater than 4.294.967.295. Please specify a filesize <= 4GiB.\n");
            exit(EXIT_FAILURE);
          }
        }
        else {
          fprintf(stderr,"bvalue has a serious problem\n");
          exit(EXIT_FAILURE);
        }
      }
      else {
        fprintf(stderr,"Please specify a value\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-c", 2) == 0) {
      if (i+1 < argc) {
        linecount = strtoul(argv[i+1], NULL, 10);
        if ((linecount*max) > 2147483648UL) {
          calc = (2147483648UL/(unsigned long)max);
          fprintf(stderr,"WARNING: resulting file will probably be larger than 2GB \n");
          fprintf(stderr,"Some applications (john the ripper) can't use wordlists greater than 2GB\n");
          fprintf(stderr,"A value of %lu ",calc);
          fprintf(stderr,"or less should result in a file less than 2GB\n");
          fprintf(stderr,"The above value is calcualated based on 2147483648UL/max\n");
          exit(EXIT_FAILURE);
        }
      }
      else {
        fprintf(stderr,"Please specify the number of lines you want\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-d", 2) == 0) {  /* specify duplicates to skip */
      if (i+1 < argc) {
        dupvalue = (size_t)strtoul(argv[i+1], &endptr, 10);
        if (argv[i+1] == NULL || endptr == argv[i+1]) {
          fprintf(stderr,"-d must be followed by [n][@,%%^]\n");
          exit(EXIT_FAILURE);
        }
        if (*endptr == '\0') /* default to @ charset */
          options.duplicates[0] = dupvalue;
        while (*endptr != '\0') {
          switch (*endptr) {
            case '@':
              options.duplicates[0] = dupvalue;
              break;
            case ',':
              options.duplicates[1] = dupvalue;
              break;
            case '%':
              options.duplicates[2] = dupvalue;
              break;
            case '^':
              options.duplicates[3] = dupvalue;
              break;
            default:
              fprintf(stderr,"the type of duplicates must be one of [@,%%^]\n");
              exit(EXIT_FAILURE);
              /*@notreached@*/
              break;
          }
          endptr++;
        }
      }
      else {
        fprintf(stderr,"Please specify the type of duplicates to skip\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-e", 2) == 0) {
      if (i+1 < argc) {
        templen = strlen(argv[i+1])+1;
        endstring = (wchar_t*)malloc(templen*sizeof(wchar_t));
        if (endstring == NULL) {
          fprintf(stderr,"Error: Can;t allocate mem for endstring\n");
          exit(EXIT_FAILURE);
        }
        (void)make_wide_string(endstring, argv[i+1], templen, &saw_unicode_input);
      }
      else {
        fprintf(stderr,"Please specify the string you want crunch to stop at\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-f", 2) == 0) { /* user specified a charset.lst */
      if (i+1 < argc) {
        charsetfilename = calloc(strlen(argv[i+1])+1, sizeof(char));
        if (charsetfilename == NULL) {
          fprintf(stderr,"can't allocate memory for charsetfilename\n");
          exit(EXIT_FAILURE);
        }
        memcpy(charsetfilename, argv[i+1], strlen(argv[i+1]));
        i += 2; /* skip -f and filename */
      }

      if ((i < argc) && (argv[i] != NULL) && (*argv[i] != '-')) { /* lowercase */
        free(charset);
        charset = readcharsetfile(charsetfilename, argv[i], &saw_unicode_input);
        if (charset == NULL) {
          fprintf(stderr,"charset = %s not found in %s\n", argv[i], charsetfilename);
          exit(EXIT_FAILURE);
        }
        else {
          numofelements = wcslen(charset);
          wordarray = calloc(numofelements, sizeof(wchar_t*));
          if (wordarray == NULL) {
            fprintf(stderr,"can't allocate memory for wordarray1\n");
            exit(EXIT_FAILURE);
          }
          for (temp = 0; temp < numofelements; temp++) {
            wordarray[temp] = calloc(2, sizeof(wchar_t)); /* space for letter + \0 */
            if (wordarray[temp] == NULL) {
              fprintf(stderr,"can't allocate memory for wordarray2\n");
              exit(EXIT_FAILURE);
            }
            wordarray[temp][0] = charset[temp];
            wordarray[temp][1] = L'\0';
          }
          i++;
        }

/* uppercase */
        if (i < argc && argv[i]!=NULL && *argv[i] != '-') {
          if (*argv[i] != '+') {
            free(upp_charset);
            upp_charset = readcharsetfile(charsetfilename, argv[i], &saw_unicode_input);
            if (upp_charset == NULL) {
              fprintf(stderr,"upp_charset = %s not found in %s\n", argv[i], charsetfilename);
              exit(EXIT_FAILURE);
            }
          }
          i++;
        }
/* numbers */
        if (i < argc && argv[i]!=NULL && *argv[i] != '-') {
          if (*argv[i] != '+') {
            free(num_charset);
            num_charset = readcharsetfile(charsetfilename, argv[i], &saw_unicode_input);
            if (num_charset == NULL) {
              fprintf(stderr,"num_charset = %s not found in %s\n", argv[i], charsetfilename);
              exit(EXIT_FAILURE);
            }
          }
          i++;
        }
/* symbols */
        if (i < argc && argv[i]!=NULL && *argv[i] != '-') {
          if (*argv[i] != '+') {
            free(sym_charset);
            sym_charset = readcharsetfile(charsetfilename, argv[i], &saw_unicode_input);
            if (sym_charset == NULL) {
              fprintf(stderr,"sym_charset = %s not found in %s\n", argv[i], charsetfilename);
              exit(EXIT_FAILURE);
            }
          }
        }
        i -= 2; /* have to subtract 2 to continue processing parameter values */
      }
      else {
        fprintf(stderr,"Please specify a filename and character set\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-i", 2) == 0) { /* user wants to invert output calculation */
      inverted = 1;
      i--; /* decrease by 1 since -i has no parameter value */
    }

    if (strncmp(argv[i], "-l", 2) == 0) { /* user wants to list literal characters */
      if (i+1 < argc) {
        literalstring = alloc_wide_string(argv[i+1],&saw_unicode_input);
      }
      else {
        fprintf(stderr,"Please specify a list of characters you want to treat as literal @?%%^\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-o", 2) == 0) {  /* outputfilename specified */
      flag4=1;
      if (i+1 < argc) {
        hold = strrchr(argv[i+1], '/');
        outputfilename = argv[i+1];
        if (hold == NULL) {
          fpath = calloc(6, sizeof(char));
          if (fpath == NULL) {
            fprintf(stderr,"crunch: can't allocate memory for fpath1\n");
            exit(EXIT_FAILURE);
          }
          memcpy(fpath, "START", 5);
          tempfilename = outputfilename;
        }
        else {
          temp = strlen(argv[i+1])-strlen(hold)+1;
          tempfilename = &argv[i+1][temp];
          fpath = calloc(temp+6, sizeof(char)); /* 6 for START +1 */
          if (fpath == NULL) {
            fprintf(stderr,"crunch: can't allocate memory for fpath2\n");
            exit(EXIT_FAILURE);
          }
          memcpy(fpath, argv[i+1], temp);
          strncat(fpath, "START", 5);
        }
      }
      else {
        fprintf(stderr,"Please specify a output filename\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-p", 2) == 0) { /* user specified letters/words to permute */
      if (i+1 < argc) {
        flag = 1;
        numofelements = (size_t)(argc-i)-1;

        if (numofelements == 1) {
          tempwcs = alloc_wide_string(argv[i+1],&saw_unicode_input);
          numofelements = wcslen(tempwcs);

          wordarray = calloc(numofelements, sizeof(wchar_t*));
          if (wordarray == NULL) {
            fprintf(stderr,"can't allocate memory for wordarray3\n");
            exit(EXIT_FAILURE);
          }

          for (temp = 0; temp < numofelements; temp++) {
            wordarray[temp] = calloc(2, sizeof(wchar_t)); /* space for letter + \0 char */
            if (wordarray[temp] == NULL) {
              fprintf(stderr,"can't allocate memory for wordarray2\n");
              exit(EXIT_FAILURE);
            }
            wordarray[temp][0] = tempwcs[temp];
            wordarray[temp][1] = '\0';
          }

          free(tempwcs);
        }
        else {
          wordarray = calloc(numofelements, sizeof(wchar_t*));
          if (wordarray == NULL) {
            fprintf(stderr,"can't allocate memory for wordarray3\n");
            exit(EXIT_FAILURE);
          }

          for (temp = 0; temp < numofelements; temp++, i++) {
            wordarray[temp] = alloc_wide_string(argv[i+1],&saw_unicode_input);
          }
        }
        /* sort wordarray so the results are sorted */
        qsort(wordarray, temp, sizeof(char *), wcstring_cmp);
      }
      else {
        fprintf(stderr,"Please specify a word or words to permute\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-q", 2) == 0) { /* user specified file of words to permute */
      if (i+1 < argc) {
        wordarray = readpermute(argv[i+1],&saw_unicode_input);
        /* sort wordarray so the results are sorted */
        qsort(wordarray, numofelements, sizeof(char *), wcstring_cmp);
        flag = 1;
      }
      else {
        fprintf(stderr,"Please specify a filename for permute to read\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-r", 2) == 0) { /* user wants to resume a previous session */
      resume = 1;
      i--; /* decrease by 1 since -r has no parameter value */
    }

    if (strncmp(argv[i], "-s", 2) == 0) { /* startblock specified */
      if (i+1 < argc && argv[i+1]) {
        startblock = alloc_wide_string(argv[i+1],&saw_unicode_input);
        if (wcslen(startblock) != min) {
          fprintf(stderr,"Warning: minimum length should be %d\n", (int)wcslen(startblock));
          exit(EXIT_FAILURE);
        }
      }
      else {
        fprintf(stderr,"Please specify the word you wish to start at\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-t", 2) == 0) { /* pattern specified */
      if (i+1 < argc) {
        pattern = alloc_wide_string(argv[i+1],&saw_unicode_input);

        if ((max > wcslen(pattern)) || (min < wcslen(pattern))) {
          fprintf(stderr,"The maximum and minimum length should be the same size as the pattern you specified. \n");
          fprintf(stderr,"min = %d  max = %d  strlen(%s)=%d\n",(int)min, (int)max, argv[i+1], (int)wcslen(pattern));
          exit(EXIT_FAILURE);
        }
      }
      else {
        fprintf(stderr,"Please specify a pattern\n");
        exit(EXIT_FAILURE);
      }
    }

    if (strncmp(argv[i], "-u", 2) == 0) {  /* suppress filesize info */
      fprintf(stderr,"Disabling printpercentage thread.  NOTE: MUST be last option\n\n");
      flag4=0;
      i--;
    }

    if (strncmp(argv[i], "-z", 2) == 0) {  /* compression algorithm specified */
      if (i+1 < argc) {
        compressalgo = argv[i+1];
        if ((compressalgo != NULL) && (strcmp(compressalgo, "gzip") != 0) && (strcmp(compressalgo, "bzip2") != 0) && (strcmp(compressalgo,"lzma") != 0) && (strcmp(compressalgo,"7z") != 0)) {
          fprintf(stderr,"Only gzip, bzip2, lzma, and 7z are supported\n");
          exit(EXIT_FAILURE);
        }
      }
      else {
        fprintf(stderr,"Only gzip, bzip2, lzma, and 7z are supported\n");
        exit(EXIT_FAILURE);
      }
    }
  } /* end parameter processing */

  /* parameter validation */
  if ((literalstring != NULL) && (pattern == NULL)) {
    fprintf(stderr,"you must specify -t when using -l\n");
    exit(EXIT_FAILURE);
  }

  if ((literalstring != NULL) && (pattern != NULL)) {
    if (wcslen(literalstring) != wcslen(pattern)) {
      fprintf(stderr,"Length of literal string should be the same length as pattern^\n");
      exit(EXIT_FAILURE);
    }
  }

  if (tempfilename != NULL) {
    if ((bytecount > 0) && (strcmp(tempfilename, "START") != 0)) {
      fprintf(stderr,"you must use -o START if you specify a count\n");
      exit(EXIT_FAILURE);
    }
  }

  if (endstring != NULL) {
    if (max != wcslen(endstring)) {
      fprintf(stderr,"End string length must equal maximum string size\n");
      exit(EXIT_FAILURE);
    }
  }

  if (startblock != NULL && endstring != NULL) {
    for (temp = 0; temp < wcslen(startblock); temp++) {

/*Added by mr.atreat@gmail.com
  The previous endstring function was broken because it used the ASCII/unicode
  values to check if endstring was greater than startblock. This revision uses
  the actual input charset character order to determine which is greater. */
      wchar_t startcharsrch = startblock[temp];
      wchar_t * startpos;
      startpos = wcschr(charset, startcharsrch);
      int startplace = startpos - charset;

      wchar_t endcharsrch = endstring[temp];
      wchar_t * endpos;
      endpos = wcschr(charset, endcharsrch);
      int endplace = endpos - charset;

      if (startplace > endplace) {
        fprintf(stderr,"End string must be greater than start string\n");
        exit(EXIT_FAILURE);
      }
      if (startplace < endplace)
	break;

/*Removed by mr.atreat@gmail.com
     if (startblock[temp] > endstring[temp]) {
        fprintf(stderr,"End string must be greater than start string\n");
        exit(EXIT_FAILURE);
      }
      if (startblock[temp] < endstring[temp])
       exit(EXIT_FAILURE);
       break;
*/
    }
  }

  if (literalstring == NULL) { /* create a default literalstring */
    size_t sizectr;
    literalstring = calloc(max+1, sizeof(wchar_t));
    if (literalstring == NULL) {
      fprintf(stderr,"can't allocate memory for literalstring\n");
      exit(EXIT_FAILURE);
    }
    for (sizectr = 0; sizectr < max; ++sizectr)
      literalstring[sizectr] = L'-';
    literalstring[max] = L'\0';
  }
    
  options.low_charset = charset;
  options.upp_charset = upp_charset;
  options.num_charset = num_charset;
  options.sym_charset = sym_charset;
  options.clen = charset ? wcslen(charset) : 0;
  options.ulen = upp_charset ? wcslen(upp_charset) : 0;
  options.nlen = num_charset ? wcslen(num_charset) : 0;
  options.slen = sym_charset ? wcslen(sym_charset) : 0;
  options.pattern = pattern;
  options.plen = pattern ? wcslen(pattern) : 0;
  options.literalstring = literalstring;
  options.endstring = endstring;
  options.max = max;

  if (pattern != NULL && startblock != NULL)
      if (!check_member(startblock, &options)) {
        fprintf(stderr,"startblock is not valid according to the pattern/literalstring\n");
        exit(EXIT_FAILURE);
      }
  if (pattern != NULL && endstring != NULL)
      if (!check_member(endstring, &options)) {
        fprintf(stderr,"endstring is not valid according to the pattern/literalstring\n");
        exit(EXIT_FAILURE);
      }

  if (endstring && too_many_duplicates(endstring, options)) {
    fprintf(stderr,"Error: End string set by -e will never occur (too many duplicate chars)\n");
    exit(EXIT_FAILURE);
  }

  if (saw_unicode_input) {
    char response[8];
    fprintf(stderr,
      "Notice: Detected unicode characters.  If you are piping crunch output\n"\
      "to another program such as john or aircrack please make sure that program\n"\
      "can handle unicode input.\n"\
      "\n");

    fprintf(stderr,"Do you want to continue? [Y/n] ");

    fgets(response,8,stdin);
    if (toupper(response[0])=='N') {
      fprintf(stderr,"Aborted by user.\n");
      exit(EXIT_FAILURE);
    }

    output_unicode = 1;
  }

  /* start processing */
  options.startstring = startblock;
  options.min = min;
  fill_minmax_strings(&options);
  fill_pattern_info(&options);

  if (resume == 1) {
    if (startblock != NULL) {
      fprintf(stderr,"you cannot specify a startblock and resume\n");
      exit(EXIT_FAILURE);
    }
    if (flag == 0) {
      startblock = resumesession(fpath, charset);
      min = wcslen(startblock);
      increment(startblock, options);
    }
    if (flag == 1) {
      fprintf(stderr,"permute doesn't support resume\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    if (fpath != NULL)
      (void)remove(fpath);
  }

  if (flag == 0) { /* chunk */
    count_strings(&my_thread.linecounter, &my_thread.finalfilesize, options);

    /* subtract already calculated data size */
    my_thread.finallinecount = my_thread.linecounter - my_thread.linetotal;
    my_thread.finalfilesize -= my_thread.bytetotal;

    /* Appears that linetotal can never be nonzero there,
      so why are we subtracting it?  -jC */


    /* if ((linecount > 0) && (finallinecount > linecount)) {
      finallinecount = linecount - linetotal;
    */ /* TODO: must calculate finalfilesize during line calculation */

    if (flag3 == 0) {
      if (suppress_finalsize == 0) {
        fprintf(stderr,"Crunch will now generate the following amount of data: ");
        fprintf(stderr,"%llu bytes\n",my_thread.finalfilesize);
        fprintf(stderr,"%llu MB\n",my_thread.finalfilesize/1048576);
        fprintf(stderr,"%llu GB\n",my_thread.finalfilesize/1073741824);
        fprintf(stderr,"%llu TB\n",my_thread.finalfilesize/1099511627776);
        fprintf(stderr,"%llu PB\n",my_thread.finalfilesize/1125899906842624);
      }
      fprintf(stderr,"Crunch will now generate the following number of lines: ");


      /* I don't see any case where finallinecount is not set there
          which would require the finalfilesize/(max+1) calc.
          I'm assuming this was a leftover from previous versions.
          At any rate, finallinecount must now always be correct or else
          other stuff will break.  So if something's wrong with line
          count output, don't code around it here like it was. -jC */

      /*
      if (pattern == NULL)
        fprintf(stderr,"%llu \n",my_thread.finallinecount);
      else
        fprintf(stderr,"%llu \n",my_thread.finalfilesize/(max+1));
      */

      fprintf(stderr,"%llu \n",my_thread.finallinecount);

      (void) sleep(3);
      if (flag4 == 1) {
        /* valgrind may report a memory leak here, because the progress report
          thread never actually terminates cleanly.  No big whoop. */
        ret = pthread_create(&threads, NULL, PrintPercentage, (void *)&my_thread);
        if (ret != 0){
          fprintf(stderr,"pthread_create error is %d\n", ret);
          exit(EXIT_FAILURE);
        }
        (void) pthread_detach(threads);
      }
    }
    my_thread.finalfilesize+=my_thread.bytetotal;
    my_thread.linecounter = 0;

    chunk(min, max, startblock, options, fpath, outputfilename, compressalgo);
  }
  else { /* permute */
    my_thread.finallinecount = 1;
    temp = 1;
    min = 0;

    /* calculate number of lines per section */
    while (temp <= numofelements) {
      my_thread.finallinecount *= temp;
      temp++;
    }
    my_thread.linecounter=my_thread.finallinecount; /* hold factoral */

    if (pattern == NULL) {
      if (wordarray == NULL) {
        fprintf(stderr,"Internal error: wordarray is NULL (it shouldn't be)\n");
        exit(EXIT_FAILURE);
      }

      my_thread.finalfilesize = 1;
      for (temp = 0; temp <numofelements; temp++) {
        templen = make_narrow_string(gconvbuffer,wordarray[temp],gconvlen);
        my_thread.finalfilesize += templen;
      }
      my_thread.finalfilesize *= my_thread.linecounter;
    }
    else {
      unsigned long long extra_unicode_bytes = 0;

      for (temp = 0; temp < wcslen(pattern); temp++) {
        switch (pattern[temp]) {
        case L'@':
          if (literalstring[temp] != L'@') {
            my_thread.finallinecount *= wcslen(charset);
          }
          break;
        case L',':
          if (literalstring[temp] != L',') {
            my_thread.finallinecount *= wcslen(upp_charset);
          }
          break;
        case L'%':
          if (literalstring[temp] != L'%') {
            my_thread.finallinecount *= wcslen(num_charset);
          }
          break;
        case L'^':
          if (literalstring[temp] != L'^') {
            my_thread.finallinecount *= wcslen(sym_charset);
          }
          break;
        default:
          min++;
          break;
        }
      }

      if (output_unicode != 0 && my_thread.finallinecount!=0) {
        /* Need one more pass to calculate how many extra bytes this will generate.
          Can't be in the first loop because we need the total product.  */

        for (temp = 0; temp < wcslen(pattern); temp++) {
          switch (pattern[temp]) {
          case L'@':
            if (literalstring[temp] != L'@') {
              extra_unicode_bytes += (wcstombs(NULL,charset,0)-wcslen(charset))*my_thread.finallinecount/wcslen(charset);
            }
            break;
          case L',':
            if (literalstring[temp] != L',') {
              extra_unicode_bytes += (wcstombs(NULL,upp_charset,0)-wcslen(upp_charset))*my_thread.finallinecount/wcslen(upp_charset);
            }
            break;
          case L'%':
            if (literalstring[temp] != L'%') {
              extra_unicode_bytes += (wcstombs(NULL,num_charset,0)-wcslen(num_charset))*my_thread.finallinecount/wcslen(num_charset);
            }
            break;
          case L'^':
            if (literalstring[temp] != L'^') {
              extra_unicode_bytes += (wcstombs(NULL,sym_charset,0)-wcslen(sym_charset))*my_thread.finallinecount/wcslen(sym_charset);
            }
            break;
          default:
            break;
          }
        }
      }

      /* calculate filesize */
      Permutefilesize(wordarray, numofelements, min, 0);

      my_thread.finalfilesize = (my_thread.finallinecount/my_thread.linecounter) * (my_thread.linecounter*(max-min)+my_thread.bytecounter);
      my_thread.finalfilesize += extra_unicode_bytes;
    }

    if (flag3 == 0) {
      if (suppress_finalsize == 0) {
        fprintf(stderr,"Crunch will now generate approximately the following amount of data: ");
        fprintf(stderr,"%llu bytes\n",my_thread.finalfilesize);
        fprintf(stderr,"%llu MB\n",my_thread.finalfilesize/1048576);
        fprintf(stderr,"%llu GB\n",my_thread.finalfilesize/1073741824);
        fprintf(stderr,"%llu TB\n",my_thread.finalfilesize/1099511627776);
        fprintf(stderr,"%llu PB\n",my_thread.finalfilesize/1125899906842624);
      }
      fprintf(stderr,"Crunch will now generate the following number of lines: ");
      fprintf(stderr,"%llu \n",my_thread.finallinecount);
      (void) sleep(3);
    }

    my_thread.bytecounter = 0;
    my_thread.linecounter=0;

    Permute(fpath, outputfilename, compressalgo, wordarray, options, numofelements, 0);

    my_thread.bytetotal+=my_thread.bytecounter;
    my_thread.linetotal+=my_thread.linecounter;
    if ((outputfilename != NULL) && (my_thread.linecounter != 0))
      renamefile(((size_t)(my_thread.finallinecount*2)+5), fpath, outputfilename, compressalgo);
  }

  if (wordarray) {
    for (temp = 0; temp < numofelements; temp++)
      free(wordarray[temp]);
    free(wordarray);
  }

  free(gconvbuffer);

  free(fpath);
  free(charsetfilename);
  free(charset);
  free(upp_charset);
  free(num_charset);
  free(sym_charset);

  free(pattern);
  free(startblock);
  free(endstring);
  free(literalstring);

  free(options.last_min);
  free(options.first_max);
  free(options.min_string);
  free(options.max_string);
  free(options.pattern_info);

  return 0;
}
