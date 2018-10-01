#include "screen-colour-fader.inc"


new bool:reverse, counter;


main() {}


public OnPlayerConnect(playerid) {
	SetPlayerScreenColour(playerid, 0x00000000);
	FadePlayerScreenColour(playerid, 0xFF0000AA, 1000, 25);
	return 1;
}


public OnScreenColourFadeComplete(playerid) {
	if (++counter == 10) {
		return 1;
	}

	FadePlayerScreenColour(playerid, reverse ? 0xFF0000AA : 0x00000000, 1000, 50);

	reverse = !reverse;

	return 1;
}
