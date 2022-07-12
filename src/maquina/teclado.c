
void TECLADO_MAIN(MQDATA *data)
{
    if(IsKeyPressed(KEY_ESCAPE))
    {
        MQEXIT = MQMenu(*&data, 1);
    }
    if(IsKeyPressed(KEY_E) || IsKeyPressed(KEY_E))
    {
        int boxindex;
        boxindex = MQVerifyItemColision(*data, MQHitboxUpdateXYZ(data->queue.event[MQFindEvent(*data,"playeruse0")].hitbox, data->queue.event[MQFindEvent(*data,"playeruse0")].position));
        if(boxindex!=-1)
        {
            MQEventFunctions[data->queue.map.item[boxindex].function](*&data,0);
        }
    }   
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        if(data->game.personagem[0].rotacao == 0)
            data->game.personagem[0].rotacao = 360;
        //             data.game.personagem[0].posicao.x -= 0.03f;
        data->game.personagem[0].rotacao -= 6;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        if(data->game.personagem[0].rotacao == 360)
            data->game.personagem[0].rotacao = 0;
        //             data.game.personagem[0].posicao.x += 0.03f;
        data->game.personagem[0].rotacao += 6;

    }
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        data->queue.render.model[MQFindRenderModel(*data,"player0")].reverse = true;
        data->queue.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {

        data->game.personagem[0].posicao = MQPlayerMove(data->game.personagem[0].posicao, data->game.personagem[0].rotacao, (data->game.personagem[0].velocidade) * (-1));
        float reverseRotation;
        if(data->game.personagem[0].rotacao<180)
            reverseRotation = 180 + data->game.personagem[0].rotacao;
        else
            reverseRotation = data->game.personagem[0].rotacao-180;
        
        Vector3 Vec3buff = MQCheckWall(*data,"player-barriga0",reverseRotation);
        if(Vec3buff.x != __INT_MAX__)
        {
            if(data->game.personagem[0].posicao.x+0.5 > Vec3buff.x&&data->game.personagem[0].posicao.x-0.5<Vec3buff.x)
                data->game.personagem[0].posicao.x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            if(data->game.personagem[0].posicao.z+0.5 > Vec3buff.z&&data->game.personagem[0].posicao.z-0.5<Vec3buff.z)
                data->game.personagem[0].posicao.z = Vec3buff.z;
        }


        if(MQWALLEXCLUDEINDEX != __INT_MAX__)
        {
            MQWALLEXCLUDE=true;
            Vec3buff = MQCheckWall(*data,"player-barriga0",reverseRotation);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.personagem[0].posicao.x+0.5 > Vec3buff.x&&data->game.personagem[0].posicao.x-0.5<Vec3buff.x)
                    data->game.personagem[0].posicao.x = Vec3buff.x;
            } 
            if(Vec3buff.z != __INT_MAX__)
            {
                if(data->game.personagem[0].posicao.z+0.5 > Vec3buff.z&&data->game.personagem[0].posicao.z-0.5<Vec3buff.z)
                    data->game.personagem[0].posicao.z = Vec3buff.z;
            }
        }
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        data->queue.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        data->game.personagem[0].posicao = MQPlayerMove(data->game.personagem[0].posicao, data->game.personagem[0].rotacao, data->game.personagem[0].velocidade);
        Vector3 Vec3buff = MQCheckWall(*data,"player-barriga0",data->game.personagem[0].rotacao);
        if(Vec3buff.x != __INT_MAX__)
        {
            if(data->game.personagem[0].posicao.x+0.5 > Vec3buff.x&&data->game.personagem[0].posicao.x-0.5<Vec3buff.x)
                data->game.personagem[0].posicao.x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            if(data->game.personagem[0].posicao.z+0.5 > Vec3buff.z&&data->game.personagem[0].posicao.z-0.5<Vec3buff.z)
                data->game.personagem[0].posicao.z = Vec3buff.z;
        }


        if(MQWALLEXCLUDEINDEX != __INT_MAX__)
        {
            MQWALLEXCLUDE=true;
            Vec3buff = MQCheckWall(*data,"player-barriga0",data->game.personagem[0].rotacao);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.personagem[0].posicao.x+0.5 > Vec3buff.x&&data->game.personagem[0].posicao.x-0.5<Vec3buff.x)
                    data->game.personagem[0].posicao.x = Vec3buff.x;
            } 
            if(Vec3buff.z != __INT_MAX__)
            {
                if(data->game.personagem[0].posicao.z+0.5 > Vec3buff.z&&data->game.personagem[0].posicao.z-0.5<Vec3buff.z)
                    data->game.personagem[0].posicao.z = Vec3buff.z;
            }
        }
    }
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        data->game.personagem[0].velocidade = 0.2f;
    }
    if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        data->game.personagem[0].velocidade = 0.1f;
    }
    if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))
    {
        data->queue.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
    {
        data->queue.render.model[MQFindRenderModel(*data,"player0")].reverse = false;
        data->queue.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyDown(KEY_SPACE))
    {
        data->game.personagem[0].posicao.y +=0.14;
    }
}