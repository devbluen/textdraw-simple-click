
            // Macro
#define PlayerTextDrawClick:%0(%1) \
    forward txdclk_%0(%1); public txdclk_%0(%1)

#define PlayerTextDrawCreateClick(%0,%1, \
	PlayerTextDrawSetClick(%0, #%1,

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_TEXTDRAW_DATA {
    bool:E_TEXTDRAW_DATA_VALIDA,
    E_TEXTDRAW_DATA_PARAMS,
    E_TEXTDRAW_DATA_CALLBACK[30 + 1],
};

static 
    e_TextdrawData[MAX_PLAYERS][PlayerText:MAX_PLAYER_TEXT_DRAWS][E_TEXTDRAW_DATA];

hook OnPlayerConnect(playerid) {

    TextDrawDestruirAll(playerid, false);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {

    // Textdraw não é válida
    if(!e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_VALIDA])
        return Y_HOOKS_BREAK_RETURN_1;

    // Verificar se tem click dinamicos
    if(!isnull(e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_CALLBACK])) {
        new callback[(30 + 7) + 5 + 1];
        format(callback, sizeof callback, "txdclk_%s", e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_CALLBACK]);

        CallLocalFunction(
            callback, 
            "ii", 
            playerid, 
            e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_PARAMS]
        );
        return Y_HOOKS_BREAK_RETURN_1;
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

static stock IsValidPlayerTextDrawSimple(playerid, PlayerText:playertextid, bool:pularVariavel = false) {
    if(_:playertextid < 0 || playertextid >= PlayerText:MAX_PLAYER_TEXT_DRAWS) 
        return false;

    if(pularVariavel)
        return true;

    return e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_VALIDA];
}

stock PlayerTextDrawSetClick(playerid, const callback[], PlayerText:playertextid, params = -1) {
    if(!IsValidPlayerTextDrawSimple(playerid, playertextid))
        return false;

    e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_PARAMS] = params;
    strcopy(e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_CALLBACK], callback);
    return true;
}

static stock TextDrawDestruir(playerid, PlayerText:playertextid, bool:streamDestruicao = true) {

    if(streamDestruicao)
        PlayerTextDrawDestroy(playerid, playertextid);

    static const e_Clear[E_TEXTDRAW_DATA];
    e_TextdrawData[playerid][playertextid] = e_Clear;
}

static stock TextDrawDestruirAll(playerid, bool:streamDestruicao = true) {

    for(new PlayerText:i; _:i < _:MAX_PLAYER_TEXT_DRAWS; _:i++) 
        if(IsValidPlayerTextDrawSimple(playerid, i))
            TextDrawDestruir(playerid, i, streamDestruicao);

}



/*

                    ooo        ooooo       .o.         .oooooo.   ooooooooo.     .oooooo.    .oooooo..o 
                    `88.       .888'      .888.       d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 
                    888b     d'888      .8"888.     888           888   .d88' 888      888 Y88bo.      
                    8 Y88. .P  888     .8' `888.    888           888ooo88P'  888      888  `"Y8888o.  
                    8  `888'   888    .88ooo8888.   888           888`88b.    888      888      `"Y88b 
                    8    Y     888   .8'     `888.  `88b    ooo   888  `88b.  `88b    d88' oo     .d8P 
                    o8o        o888o o88o     o8888o  `Y8bood8P'  o888o  o888o  `Y8bood8P'  8""88888P'  

*/

stock PlayerText:alias_CreatePlayerTextDraw(playerid, Float:x, Float:y, const text[]) {
    new PlayerText:playertextid = CreatePlayerTextDraw(playerid, x, y, text);
    if(!IsValidPlayerTextDrawSimple(playerid, playertextid, true))
        return PlayerText:INVALID_TEXT_DRAW;

    e_TextdrawData[playerid][playertextid][E_TEXTDRAW_DATA_VALIDA] = true;
    return playertextid;
}

#if defined _ALS_CreatePlayerTextDraw
    #undef CreatePlayerTextDraw
#else
    #define _ALS_CreatePlayerTextDraw
#endif
 
#define CreatePlayerTextDraw alias_CreatePlayerTextDraw

stock alias_PlayerTextDrawDestroy(playerid, PlayerText:playertextid) {
    if(!IsValidPlayerTextDrawSimple(playerid, playertextid))
        return false;
    
    TextDrawDestruir(playerid, playertextid);
    return true;
}

#if defined _ALS_PlayerTextDrawDestroy
    #undef PlayerTextDrawDestroy
#else
    #define _ALS_PlayerTextDrawDestroy
#endif
 
#define PlayerTextDrawDestroy alias_PlayerTextDrawDestroy
