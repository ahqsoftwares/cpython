#include "Python.h"

#ifndef DONT_HAVE_STDIO_H
#include <stdio.h>
#endif

#define DATE "May 17 2022"

#define TIME "16:36:42"

/* XXX Only unix build process has been tested */
#define GITVERSION "6de2ca5"

#define GITTAG "tags/v3.9.13"

#define GITBRANCH ""

const char *
Py_GetBuildInfo(void)
{
    static char buildinfo[50 + sizeof(GITVERSION) +
                          ((sizeof(GITTAG) > sizeof(GITBRANCH)) ?
                           sizeof(GITTAG) : sizeof(GITBRANCH))];
    const char *revision = _Py_gitversion();
    const char *sep = *revision ? ":" : "";
    const char *gitid = _Py_gitidentifier();
    if (!(*gitid)) {
        gitid = "main";
    }
    PyOS_snprintf(buildinfo, sizeof(buildinfo),
                  "%s%s%s, %.20s, %.9s", gitid, sep, revision,
                  DATE, TIME);
    return buildinfo;
}

const char *
_Py_gitversion(void)
{
    return GITVERSION;
}

const char *
_Py_gitidentifier(void)
{
    const char *gittag, *gitid;
    gittag = GITTAG;
    if ((*gittag) && strcmp(gittag, "undefined") != 0)
        gitid = gittag;
    else
        gitid = GITBRANCH;
    return gitid;
}
