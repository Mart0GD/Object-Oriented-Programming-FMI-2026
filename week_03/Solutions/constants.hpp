#pragma once

static const int ALPHABET_SIZE = 26;
static const int MAX_FILE_NAME = 1024;

enum commnad
{
    UNKNOWN = -1,

    MOV,
    ADD,
    SUB,
    MUL,

    COMMANDS_CNT
};

static const char* commands_names[COMMANDS_CNT] =
{
    "MOV",
    "ADD",
    "SUB",
    "MUL",
};

static const char FAIL_MESSAGE[] = "ERROR";
static const char END_LINE[] = "END";