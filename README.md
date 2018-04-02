# Screen Colour Fader


## Introduction

This include lets you add colour filters to players' screens and fade between them. Until today I was using a modified version of Joe Staff's fader include, but since it was using a separate argument for each part of an RGBA colour and the original was outdated in general, I decided to create my own. Here's what I came up with.


## Functions


```pawn
native SetPlayerScreenColour(playerid, colour);
```
Will set the player's screen colour to the specified colour. Can be used during a fade, but the fade will continue after the current step is finished. Returns `1` if the specified player is connected or `0` if not.


```pawn
native GetPlayerScreenColour(playerid);
```
Can be used during a fade. Returns the current colour of the player's screen if the player is connected or `0x00000000` if not.

```pawn
native FadePlayerScreenColour(playerid, colour, time, steps);
```
Fades the player's screen from the current colour to the colour specified in the function. `time` specifies the duration of the fade and `steps` specifies the amount of steps made during the fade. Returns `1` if the specified player is connected and the values of `time` and `steps` are valid or `0` if not.

```pawn
native StopPlayerScreenColourFade(playerid);
```
Stops the ongoing fade. The colour of the player's screen will remain as it is at the time of the function call. Returns `1` if the specified player is connected and has an ongoing fade or `0` if not.

## Callbacks

```pawn
forward public OnScreenColourFadeComplete(playerid);
```


## Notes

* Both for the functions and the callback, the American spelling (color instead of colour) is also supported.


## Example

The following piece of code fades the player's screen to red and back to transparent five times.

```pawn
new bool:reverse, counter;

public OnPlayerConnect(playerid)
{
	SetPlayerScreenColour(playerid, 0x00000000);
	FadePlayerScreenColour(playerid, 0xFF0000AA, 1000, 25);
	return 1;
}


public OnScreenColourFadeComplete(playerid)
{
	if (++counter == 10)
	    return 1;

    	FadePlayerScreenColour(playerid, reverse ? 0xFF0000AA : 0x00000000, 1000, 50);

	reverse = !reverse;

	return 1;
}
```
