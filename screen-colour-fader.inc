#include <a_samp>
#include <colour-manipulation>

#if defined _SCF_included
    #endinput
#endif
#define _SCF_included


#define SetPlayerScreenColor 		SetPlayerScreenColour
#define GetPlayerScreenColor 		GetPlayerScreenColour
#define FadePlayerScreenColor 		FadePlayerScreenColour
#define StopPlayerScreenColorFade 	StopPlayerScreenColourFade
#define OnScreenColorFadeComplete   OnScreenColourFadeComplete


enum screenColourFadeData {
    sSteps,
    sCurrentStep,

    sOriginalColour,
    sFinalColour,

    sTimer,
}


static
    ScreenColour[MAX_PLAYERS],
    PlayerText:ScreenColourTD[MAX_PLAYERS],
    ScreenColourFadeData[MAX_PLAYERS][screenColourFadeData]
;


forward public OnScreenColourFadeComplete(playerid);


static stock _SetPlayerScreenColour(playerid, colour) {
    ScreenColour[playerid] = colour;

    PlayerTextDrawBoxColor(playerid, ScreenColourTD[playerid], ScreenColour[playerid]);
    PlayerTextDrawShow(playerid, ScreenColourTD[playerid]);
}


stock SetPlayerScreenColour(playerid, colour) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    _SetPlayerScreenColour(playerid, colour);
    return 1;
}


stock GetPlayerScreenColour(playerid) {
    return IsPlayerConnected(playerid) ? ScreenColour[playerid] : 0x00000000;
}


static stock _KillScreenColourFadeTimer(playerid) {
    KillTimer(ScreenColourFadeData[playerid][sTimer]);

    ScreenColourFadeData[playerid][sTimer] = -1;
}


stock FadePlayerScreenColour(playerid, colour, time, steps) {
    if (!IsPlayerConnected(playerid) || steps < 1 || time < 0) {
        return 0;
    }

    if (ScreenColourFadeData[playerid][sTimer] != -1) {
        KillTimer(ScreenColourFadeData[playerid][sTimer]);
    }

    ScreenColourFadeData[playerid][sOriginalColour] = ScreenColour[playerid];
    ScreenColourFadeData[playerid][sFinalColour] = colour;

    ScreenColourFadeData[playerid][sSteps] = steps;
    ScreenColourFadeData[playerid][sCurrentStep] = 0;

    ScreenColourFadeData[playerid][sTimer] = SetTimerEx("ScreenColourFadeTimer", time / steps, true, "i", playerid);

    return 1;
}


stock StopPlayerScreenColourFade(playerid) {
    if (!IsPlayerConnected(playerid) || ScreenColourFadeData[playerid][sTimer] == -1) {
        return 0;
    }

    _KillScreenColourFadeTimer(playerid);
    return 1;
}


forward public ScreenColourFadeTimer(playerid);
public ScreenColourFadeTimer(playerid) {
    if (ScreenColourFadeData[playerid][sCurrentStep] == ScreenColourFadeData[playerid][sSteps]) {
        _KillScreenColourFadeTimer(playerid);

        CallLocalFunction("OnScreenColourFadeComplete", "i", playerid);
        return 1;
    }

    _SetPlayerScreenColour(playerid, LerpColour(ScreenColourFadeData[playerid][sOriginalColour], ScreenColourFadeData[playerid][sFinalColour], ScreenColourFadeData[playerid][sCurrentStep] / ScreenColourFadeData[playerid][sSteps]));

    ScreenColourFadeData[playerid][sCurrentStep]++;
    return 1;
}


public OnPlayerConnect(playerid) {
    ScreenColourFadeData[playerid][sTimer] = -1;

    ScreenColourTD[playerid] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_");
    PlayerTextDrawTextSize(playerid, ScreenColourTD[playerid], 640.0, 480.0);
    PlayerTextDrawLetterSize(playerid, ScreenColourTD[playerid], 0.0, 50.0);
    PlayerTextDrawUseBox(playerid, ScreenColourTD[playerid], true);

    _SetPlayerScreenColour(playerid, 0x00000000);

    #if defined SCF_OnPlayerConnect
        return SCF_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SCF_OnPlayerConnect

#if defined SCF_OnPlayerConnect
    forward SCF_OnPlayerConnect(playerid);
#endif


public OnPlayerDisconnect(playerid, reason) {
    if (ScreenColourFadeData[playerid][sTimer] != -1) {
        _KillScreenColourFadeTimer(playerid);
    }

    #if defined SCF_OnPlayerDisconnect
        return SCF_OnPlayerDisconnect(playerid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SCF_OnPlayerDisconnect

#if defined SCF_OnPlayerDisconnect
    forward SCF_OnPlayerDisconnect(playerid, reason);
#endif
