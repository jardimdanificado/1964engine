//-----------------------------------
//HTIBOX
//-----------------------------------

BoundingBox MQHitboxUpdateX(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.x += targetPosi.x;
    hitboxbase.max.x += targetPosi.x;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateY(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.y += targetPosi.y;
    hitboxbase.max.y += targetPosi.y;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.z += targetPosi.z;
    hitboxbase.max.z += targetPosi.z;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateXYZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    BoundingBox hitbox;
    hitbox = hitboxbase;
    hitbox.max = Vector3Add(hitboxbase.max,targetPosi);
    hitbox.min = Vector3Add(hitboxbase.min, targetPosi);
    return hitbox;
}

//-----------------------------------
//FONT&STRING
//-----------------------------------

char *MQStrAddInt(char* string, int value)
{
    char buffer[sizeof(string)];
    strcpy(buffer,string);
    string = malloc(sizeof(string)+8);
    snprintf(string,sizeof(string)+8,"%s%d",buffer,value);
    return string;
}

char *MQStrAddStr(char* string1, char* string2)
{
    char buffer[sizeof(string1)];
    strcpy(buffer,string1);
    string1 = malloc(sizeof(buffer)+sizeof(string2));
    snprintf(string1,sizeof(buffer)+sizeof(string2),"%s%s",buffer,string2);
    return string1;
}

void MQLoadLang(DATA* data, char lang[4])
{
    remove("./data/temp/lang");
    char buffer[27];
    snprintf(buffer,27,"./data/lang/%s/text.text",lang);
    abinCoreFileCopy(buffer, "./data/temp/lang");
    for(int i = 0; i <atoi(abinCoreReturnData("./data/temp/lang","SIZE"));i++)
    {
        snprintf(buffer,4,"%d",i);
        strcpy(data->file.lang[data->session.LangCount],abinCoreReturnData("./data/temp/lang",buffer));
        data->session.LangCount++;
    }
}

Font MQFontStart(char *FontLoc, int FontSize)
{
    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData(FontLoc, &fileSize);
    // Default font generation from TTF font
    Font fontDefault = { 0 };
    fontDefault.baseSize = FontSize;
    fontDefault.glyphCount = 95;

    // Loading font data from memory data
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 95, FONT_DEFAULT);

    fontDefault.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 95, FONT_DEFAULT);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 4 px, pack method: 0 (default)
    Image atlas = GenImageFontAtlas(fontDefault.glyphs, &fontDefault.recs, 95, FontSize, 14, 0);
    fontDefault.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    // SDF font generation from TTF font
    Font fontSDF = { 0 };
    fontSDF.baseSize = FontSize;
    fontSDF.glyphCount = 95;
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 0 (defaults to 95)
    fontSDF.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 0, FONT_SDF);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 0 px, pack method: 1 (Skyline algorythm)
    atlas = GenImageFontAtlas(fontSDF.glyphs, &fontSDF.recs, 95, FontSize, 0, 1);
    fontSDF.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    UnloadFileData(fileData);      // Free memory from loaded file

    // Load SDF required shader (we use default vertex shader)
    //Shader shader = LoadShader(0, TextFormat("data/shaders/sdf.fs", 330));
    SetTextureFilter(fontSDF.texture, TEXTURE_FILTER_POINT);    // Required for SDF font

    return (fontDefault);
}


//-----------------------------------
//FIND
//-----------------------------------

int MQFindHitboxByName(DATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.session.LoadedNames[i].hitbox,name)==0)
            return i;
    }
    return -1;
}


int MQFindModelByName(DATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.session.LoadedNames[i].model,name)==0)
            return i;
    }
    return -1;
}

int MQFindRenderModelIndexByID(DATA data, char* id)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.model[i].id, id)==0)
        {
            return i;
        }
    }
    return -1;
}

int MQFindRenderTextIndexByID(DATA data, char* id)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.text[i].id, id)==0)
        {
            return i;
        }
    }
    return -1;
}

//-----------------------------------
//CALCULATE
//-----------------------------------

float MQDifferenceFloat(float a, float b)
{
    bool negativo = false;
    float resultado;
    if(a < 0)
    {
        a = a * (-1);
        negativo = true;
    }
    else if(b < 0)
    {
        b = b * (-1);
        negativo = true;
    }

    if(negativo == true)
    {
        resultado = a + b;
    }
    else if(a == b)
    {
        return 0;
    }
    else if(a > b)
    {
        resultado = a - b;
    }
    else if(a < b)
    {
        resultado = b - a;
    }
    return resultado;
}

Vector3 MQDifferenceVec3(Vector3 vec1, Vector3 vec2)
{
    return((Vector3) {MQDifferenceFloat(vec1.x, vec2.x), MQDifferenceFloat(vec1.y, vec2.y), MQDifferenceFloat(vec1.z, vec2.z)});
}

//-----------------------------------
//VERTICES
//-----------------------------------

Vector3 MQRotateVerticeSelf(float angle, Vector3 vertice)
{
    Vector3 NewVertice;
    NewVertice.y = vertice.y;
    NewVertice.x = vertice.x * cos(angle) - vertice.z * sin(angle);
    NewVertice.z = vertice.x * sin(angle) + vertice.z * cos(angle);
    return NewVertice;
}

Vector3 MQRotateVertice(Vector3 pivot, float angle, Vector3 vertice)
{
    Vector3 NewVertice;
    NewVertice.y = vertice.y;
    NewVertice.x = ((vertice.x - pivot.x) * cos(angle)) - ((vertice.z - pivot.z) * sin(angle)) + pivot.x;
    NewVertice.z = ((vertice.x - pivot.x) * sin(angle)) + ((vertice.z - pivot.z) * cos(angle)) + pivot.z;
    return NewVertice;
}

//-----------------------------------
//WINDOW
//-----------------------------------

void MQWindowStart()
{
    if(strcmp(abinCoreReturnData("./config.text", "MSAA"), "true") == 0)
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    if(strcmp(abinCoreReturnData("./config.text", "RESIZE"), "true") == 0)
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    char buffer[255];
    snprintf(buffer,255,"%s",abinCoreReturnData("config.text", "TITLE"));
    InitAudioDevice();
    InitWindow(atoi(abinCoreReturnData("config.text", "SCRX")), atoi(abinCoreReturnData("config.text", "SCRY")), buffer);
}

//-----------------------------------
//PLAYER
//-----------------------------------

#include "player.c"

//-----------------------------------
//AI
//-----------------------------------

//#include "ai.c"

//-----------------------------------
//COLISION
//-----------------------------------

float MQGravity(Vector3 posicao, float gravidade, int tempo)
{
    return(posicao.y - gravidade*((tempo*(tempo/5)))/60);
}

void MQGravit(DATA* data, int quem)
{
    if(MQReturnYMaxCollisionPoint(*data, data->game.personagem[quem].posicao) == MQFALSE)
    {
        data->game.personagem[quem].posicao.y = MQGravity(data->game.personagem[quem].posicao, 0.1, data->game.personagem[quem].tempoGravit);
        data->game.personagem[quem].tempoGravit++;
    }
    else 
    {
        data->game.personagem[quem].posicao.y = MQReturnYMaxCollisionPoint(*data, data->game.personagem[quem].posicao);
        data->game.personagem[quem].tempoGravit = 0;
    }
}

//-----------------------------------
//CAMERA
//-----------------------------------

Camera MQCameraStart(Camera *camera)
{
    camera->position = (Vector3)
    {
        10.0f, 10.0f, 10.0f
    };
    camera->target = (Vector3)
    {
        0.0f, 0.0f, 0.0f
    };
    camera->up = (Vector3)
    {
        0.0f, 1.0f, 0.0f
    };
    camera->fovy = 30.0f;
    camera->projection = CAMERA_PERSPECTIVE;
    SetCameraMode(*camera, CAMERA_CUSTOM);
    return (*camera);
}

//-----------------------------------
//MODELS
//-----------------------------------

#include "models.c"

//-----------------------------------
//DOORS
//-----------------------------------

/* #include "door.c" */

//-----------------------------------
//SAVE
//-----------------------------------

void MQLoadGame(DATA *data)
{
    FILE *file;
    file = fopen("data/save/savegame", "r+b");
    fread(&data->game, sizeof(struct DATA_GAME), 1, file);
    fclose(file);
}

void MQSaveGame(DATA data)
{
    remove("data/save/savegame");
    FILE *file = fopen("data/save/savegame", "w+b");
    fwrite(&data.game, sizeof(struct DATA_GAME), 1, file);
    fclose(file);
}

//-----------------------------------
//RENDER
//-----------------------------------

#include "render.c"

//-----------------------------------
//MENU
//-----------------------------------

#include "menu.c"

//-----------------------------------
//KEYBOARD
//-----------------------------------

#include "teclado.c"