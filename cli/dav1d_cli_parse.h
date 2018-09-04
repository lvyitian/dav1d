/*
 * ..
 */

#ifndef __DAV1D_CLI_PARSE_H__
#define __DAV1D_CLI_PARSE_H__

#include "dav1d.h"

typedef struct {
    const char *outputfile;
    const char *inputfile;
    const char *muxer;
    unsigned limit;
    int quiet;
} CLISettings;

void parse(const int argc, char *const *const argv,
           CLISettings *const cli_settings, Dav1dSettings *const lib_settings);

#endif /* __DAV1D_CLI_PARSE_H__ */
