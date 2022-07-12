//MAQUINA
//AKA MQEngine

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//RAYLIB
#include "./raylib/raylib.h"
#include "./raylib/raymath.h"

//ABIN Files
#include "./abin.h"

#define COR_VERMELHO CLITERAL(Color){235, 64, 52,255}
#define COR_SELECIONADO   CLITERAL(Color){202,137,109,255}
#define COR_SELECIONADO2 CLITERAL(Color){145, 39, 32,255}
#define COR_PRETO CLITERAL(Color){31, 9, 7,255}
#define COR_VAZIO   CLITERAL(Color){55,55,55,255}
#define COR_BRANCO   CLITERAL(Color){250,239,229,255}
#define COR_CINZA   CLITERAL(Color){115,105,97,255}
#define COR_LARANJA   CLITERAL(Color){202,137,109,255}

#define COR_PELE0 CLITERAL(Color){240, 199, 156,255}
#define COR_ROUPA0 CLITERAL(Color){103, 122, 137,255}
#define COR_ROUPA1 CLITERAL(Color){110, 125, 103,255}

#define MQFALSE __INT_MAX__*(-1)
#define MQTRUE __INT_MAX__

#define MAXOBJ 64

unsigned int MAXANIM = 1;

bool MQEXIT = false;

//-----------------------------------
//DATA_GAME
//-----------------------------------

struct MQDATA_PLAYER
{
    float velocidade;
    int tempoGravit;
    Vector3 posicao;
    float rotacao;
};
typedef struct MQDATA_PLAYER MQDATA_PLAYER;

struct MQDATA_GAME
{
    MQDATA_PLAYER personagem[MAXOBJ];
};
typedef struct MQDATA_GAME MQDATA_GAME;

//-----------------------------------
//DATA_FILE
//-----------------------------------

struct MQDATA_FILE_MODEL
{
    Model model;
    ModelAnimation *anim;
    char name[255];
};
typedef struct MQDATA_FILE_MODEL MQDATA_FILE_MODEL;

struct MQDATA_FILE_HITBOX
{
    BoundingBox hitbox;
    char name[255];
};
typedef struct MQDATA_FILE_HITBOX MQDATA_FILE_HITBOX;

struct MQDATA_FILE_FONT
{
    Font font;
    char name[255];
};
typedef struct MQDATA_FILE_FONT MQDATA_FILE_FONT;

struct MQDATA_FILE_TEXT
{
    char text[255];
    char name[255];
};
typedef struct MQDATA_FILE_TEXT MQDATA_FILE_TEXT;

struct MQDATA_FILE_MUSIC
{
    Music music;
    char name[255];
};
typedef struct MQDATA_FILE_MUSIC MQDATA_FILE_MUSIC;

struct MQDATA_FILE_SOUND
{
    Sound sound;
    char name[255];
};
typedef struct MQDATA_FILE_SOUND MQDATA_FILE_SOUND;

struct MQDATA_FILES
{
    MQDATA_FILE_MODEL models[MAXOBJ];
    MQDATA_FILE_HITBOX hitboxes[MAXOBJ];
    MQDATA_FILE_HITBOX eventboxes[MAXOBJ];
    MQDATA_FILE_FONT fonts[MAXOBJ];
    MQDATA_FILE_TEXT texts[MAXOBJ];
    MQDATA_FILE_TEXT langs[MAXOBJ];
    MQDATA_FILE_MUSIC musics[MAXOBJ];
    MQDATA_FILE_SOUND sounds[MAXOBJ];
};
typedef struct MQDATA_FILES MQDATA_FILES;

//-----------------------------------
//DATA_SESSION
//-----------------------------------

struct MQDATA_SESSION
{
    long int frame;
};
typedef struct MQDATA_SESSION MQDATA_SESSION;

//-----------------------------------
//DATA_QUEUE_RENDER
//-----------------------------------

struct MQDATA_RENDER_MODEL
{
    bool visible, playing, reverse;
    int modelIndex;
    int currentAnim;
    int currentFrame;
    Color color;
    Vector3 position;
    float rotation;
    char *name;
};
typedef struct MQDATA_RENDER_MODEL MQDATA_RENDER_MODEL;

struct MQDATA_RENDER_TEXT
{
    bool visible;
    int textIndex;
    Vector2 position;
    Color color;
    char* string;
    int fontSize;
    int fontIndex;
    char *name;
};
typedef struct MQDATA_RENDER_TEXT MQDATA_RENDER_TEXT;

//-----------------------------------
//DATA_QUEUE
//-----------------------------------

struct MQDATA_QUEUE_RENDER
{
    MQDATA_RENDER_MODEL model[MAXOBJ];
    MQDATA_RENDER_TEXT text[MAXOBJ];
    Color background;
    Camera camera;
};
typedef struct MQDATA_QUEUE_RENDER MQDATA_QUEUE_RENDER;

struct MQDATA_EVENTBOX_SLOT
{
    bool active;
    bool persistent;
    int function;
    BoundingBox hitbox;
    Vector3 position;
    float rotation;
    char *name;
};
typedef struct MQDATA_EVENTBOX_SLOT MQDATA_EVENTBOX_SLOT;

struct MQDATA_QUEUE_ITEM
{
    char *name;
    char *type;
    int index;
    float content;
    bool active;
    BoundingBox hitbox;
    Vector3 position;
    float rotation;
    int function;
};
typedef struct MQDATA_QUEUE_ITEM MQDATA_QUEUE_ITEM;

struct MQDATA_QUEUE_MAP
{
    MQDATA_QUEUE_ITEM item[MAXOBJ];
};
typedef struct MQDATA_QUEUE_MAP MQDATA_QUEUE_MAP;

struct MQDATA_QUEUE
{
    MQDATA_QUEUE_RENDER render;
    MQDATA_EVENTBOX_SLOT event[MAXOBJ];
    MQDATA_QUEUE_MAP map;
};
typedef struct MQDATA_QUEUE MQDATA_QUEUE;

//-----------------------------------
//DATA
//-----------------------------------

struct MQDATA
{
    MQDATA_GAME game;
    MQDATA_FILES files;
    MQDATA_SESSION session;
    MQDATA_QUEUE queue;
};
typedef struct MQDATA MQDATA;

#include "maquina.c"