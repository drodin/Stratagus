//   ___________		     _________		      _____  __
//   \_	  _____/______   ____   ____ \_   ___ \____________ _/ ____\/  |_
//    |    __) \_  __ \_/ __ \_/ __ \/    \  \/\_  __ \__  \\   __\\   __\ 
//    |     \   |  | \/\  ___/\  ___/\     \____|  | \// __ \|  |   |  |
//    \___  /   |__|    \___  >\___  >\______  /|__|  (____  /__|   |__|
//	  \/		    \/	   \/	     \/		   \/
//  ______________________                           ______________________
//			  T H E   W A R   B E G I N S
//	   FreeCraft - A free fantasy real time strategy game engine
//
/**@name video.c	-	The universal video functions. */
/*
**	(c) Copyright 1999,2000 by Lutz Sammer
**
**	$Id$
*/

//@{

/*----------------------------------------------------------------------------
--	Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "freecraft.h"
#include "video.h"

#include "map.h"
#include "ui.h"
#include "cursor.h"

#ifdef USE_SDL
#include <SDL/SDL.h>
#endif

/*----------------------------------------------------------------------------
--	Declarations
----------------------------------------------------------------------------*/

// JOHNS: This is needed, because later I want to support it all with the same
//	  executable, choosable at runtime.
#ifdef USE_X11
#define UseX11		1
#define UseSdl		0
#define UseSVGALib	0
#define UseWin32	0
#endif

#ifdef USE_SDL
#define UseX11		0
#define UseSdl		1
#define UseSVGALib	0
#define UseWin32	0
#endif

#ifdef USE_SVGALIB
#define UseX11		0
#define UseSdl		0
#define UseSVGALib	1
#define UseWin32	0
#endif

#ifdef noUSE_WIN32
#define UseX11		0
#define UseSdl		0
#define UseSVGALib	0
#define UseWin32	1
#endif

/*----------------------------------------------------------------------------
--	Externals
----------------------------------------------------------------------------*/

extern void InitVideoSdl(void);
extern void InitVideoX11(void);
extern void InitVideoSVGA(void);
extern void InitVideoWin32(void);

/*----------------------------------------------------------------------------
--	Variables
----------------------------------------------------------------------------*/

global char VideoFullScreen;		/// true fullscreen wanted

#ifdef NEW_VIDEO

global int ClipX1;			/// current clipping top left
global int ClipY1;			/// current clipping top left
global int ClipX2;			/// current clipping bottom right
global int ClipY2;			/// current clipping bottom right

#ifdef DEBUG
global unsigned AllocatedGraphicMemory;	/// Allocated memory for objects
global unsigned CompressedGraphicMemory;/// memory for compressed objects
#endif

    /**
    **	Architecture-dependant video depth. Set by InitVideoXXX, if 0.
    **	(8,15,16,24,32)
    **	@see InitVideo @see InitVideoX11 @see InitVideoSVGA @see InitVideoSdl
    **	@see InitVideoWin32 @see main
    */
global int VideoDepth;

    /**
    **	Architecture-dependant videomemory. Set by InitVideoXXX.
    **	FIXME: need a new function to set it, see #ifdef SDL code
    **	@see InitVideo @see InitVideoX11 @see InitVideoSVGA @see InitVideoSdl
    **	@see InitVideoWin32 @see VMemType
    */
global VMemType* VideoMemory;

    /**
    **	Architecture-dependant system palette. Applies as conversion between
    **	GlobalPalette colors and their representation in videomemory.
    **	Set by VideoCreatePalette or VideoSetPalette.
    **	@see VideoCreatePalette @VideoSetPalette
    */
global VMemType* Pixels;

#endif

    ///	Loaded system palette. 256-entries long, active system palette.
global Palette GlobalPalette[256];

#ifdef NEW_VIDEO
    /// Does ColorCycling..
global void (*ColorCycle)(void);
#endif

/*----------------------------------------------------------------------------
--	Functions
----------------------------------------------------------------------------*/

#ifdef NEW_VIDEO
/**
**	Set clipping for graphic routines.
**
**	@param left	Left X screen coordinate.
**	@param top	Top Y screen coordinate.
**	@param right	Right X screen coordinate.
**	@param bottom	Bottom Y screen coordinate.
*/
global void SetClipping(int left,int top,int right,int bottom)
{
    if( left>right ) { left^=right; right^=left; left^=right; }
    if( top>bottom ) { top^=bottom; bottom^=top; top^=bottom; }
    
    if( left<0 )    left=0;
    if( top<0 )	    top=0;
    if( right<0 )   right=0;
    if( bottom<0 )  bottom=0;

    if( left>=VideoWidth )	left=VideoWidth-1;
    if( right>=VideoWidth )	right=VideoWidth-1;
    if( bottom>=VideoHeight ) bottom=VideoHeight-1;
    if( top>=VideoHeight )	top=VideoHeight-1;
    
    ClipX1=left;
    ClipY1=top;
    ClipX2=right;
    ClipY2=bottom;
}
#endif

/**
**	Load a picture and display it on the screen (full screen),
**	changing the colormap and so on..
**
**	@param name	Name of the picture (file) to display.
*/
global void DisplayPicture(const char *name)
{
    Graphic* title;

    title=LoadGraphic(name);
#ifdef NEW_VIDEO
    VideoSetPalette((VMemType*)title->Pixels);
#else
    VideoSetPalette(title->Pixels);
#endif

#ifdef USE_SDL
    // FIXME: should be moved to system/hardware dependend part
    { extern SDL_Surface *Screen;		/// internal screen
    SDL_LockSurface(Screen);

    VideoMemory=Screen->pixels;
#endif

    // FIXME: bigger window ?
    VideoDrawSubClip(title,0,0
	,title->Width,title->Height
	,(VideoWidth-title->Width)/2,(VideoHeight-title->Height)/2);

#ifdef USE_SDL
    // FIXME: should be moved to system/hardware dependend part
    SDL_UnlockSurface(Screen); }
#endif
    VideoFree(title);
    // FIXME: (ARI:) New Palette got stuck in memory?
}

#ifdef NEW_VIDEO

/**
**	Load palette from resource. Just loads palette, to set it use
**	VideoCreatePalette, which sets system palette.
**
**	@param pal buffer to store palette (256-entries long)
**	@param name resource file name
**
**	@see VideoCreatePalette
*/
global void LoadRGB(Palette *pal, const char *name)
{
    FILE *fp;
    int i;
    
    if((fp=fopen(name,"rb")) == NULL) {
	fprintf(stderr,"Can't load palette %s\n",name);
	exit(-1);
    }

    for(i=0;i<256;i++){
	pal[i].r=fgetc(fp)<<2;
	pal[i].g=fgetc(fp)<<2;
	pal[i].b=fgetc(fp)<<2;
    }
    
    fclose(fp);
}

// FIXME: this isn't 100% correct
// Color cycling info - forest:
// 3	flash red/green	(attacked building on minimap)
// 38-47	cycle		(water)
// 48-56	cycle		(water-coast boundary)
// 202	pulsates red	(Circle of Power)
// 240-244	cycle		(water around ships, Runestone, Dark Portal)
// Color cycling info - swamp:
// 3	flash red/green	(attacked building on minimap)
// 4	pulsates red	(Circle of Power)
// 5-9	cycle		(Runestone, Dark Portal)
// 38-47	cycle		(water)
// 88-95	cycle		(waterholes in coast and ground)
// 240-244	cycle		(water around ships)
// Color cycling info - wasteland:
// 3	flash red/green	(attacked building on minimap)
// 38-47	cycle		(water)
// 64-70	cycle		(coast)
// 202	pulsates red	(Circle of Power)
// 240-244	cycle		(water around ships, Runestone, Dark Portal)
// Color cycling info - winter:
// 3	flash red/green	(attacked building on minimap)
// 40-47	cycle		(water)
// 48-54	cycle		(half-sunken ice-floe)
// 202	pulsates red	(Circle of Power)
// 205-207	cycle		(lights on christmas tree)
// 240-244	cycle		(water around ships, Runestone, Dark Portal)

/**
**	Color cycle for 8 bpp video mode.
**
**	FIXME: not correct cycles only palette of tileset.
**	FIXME: Also icons and some units use color cycling.
**	FIXME: must be configured by the tileset or global.
*/
global void ColorCycle8(void)
{
    int i;
    int x;
    VMemType8* pixels;

    //
    //	Color cycle tileset palette
    //
    pixels=TheMap.TileData->Pixels;
    x = pixels[38];
    for(i = 38; i < 47; ++i){
	pixels[i] = pixels[i+1];
    }
    pixels[47] = x;

    x=Pixels8[38];
    for( i=38; i<47; ++i ) {	// tileset color cycle
	Pixels8[i]=Pixels8[i+1];
    }
    Pixels8[47]=x;

    x=Pixels8[240];
    for( i=240; i<244; ++i ) {	// units/icons color cycle
	Pixels8[i]=Pixels8[i+1];
    }
    Pixels8[244]=x;

    MapColorCycle();		// FIXME: could be little more informativer
    MustRedraw|=RedrawMap|RedrawInfoPanel;
}

/**
**	Color cycle for 16 bpp video mode.
**
**	FIXME: not correct cycles only palette of tileset.
**	FIXME: Also icons and some units use color cycling.
**	FIXME: must be configured by the tileset or global.
*/
global void ColorCycle16(void)
{
    int i;
    int x;
    VMemType16* pixels;

    //
    //	Color cycle tileset palette
    //
    pixels=TheMap.TileData->Pixels;
    x = pixels[38];
    for(i = 38; i < 47; ++i){
	pixels[i] = pixels[i+1];
    }
    pixels[47] = x;

    x=Pixels16[38];
    for( i=38; i<47; ++i ) {	// tileset color cycle
	Pixels16[i]=Pixels16[i+1];
    }
    Pixels16[47]=x;

    x=Pixels16[240];
    for( i=240; i<244; ++i ) {	// units/icons color cycle
	Pixels16[i]=Pixels16[i+1];
    }
    Pixels16[244]=x;

    MapColorCycle();		// FIXME: could be little more informativer
    MustRedraw|=RedrawMap|RedrawInfoPanel;
}

/**
**	Color cycle for 24 bpp video mode.
**
**	FIXME: not correct cycles only palette of tileset.
**	FIXME: Also icons and some units use color cycling.
**	FIXME: must be configured by the tileset or global.
*/
global void ColorCycle24(void)
{
    int i;
    VMemType24 x;
    VMemType24* pixels;

    //
    //	Color cycle tileset palette
    //
    pixels=TheMap.TileData->Pixels;
    x = pixels[38];
    for(i = 38; i < 47; ++i){
	pixels[i] = pixels[i+1];
    }
    pixels[47] = x;

    x=Pixels24[38];
    for( i=38; i<47; ++i ) {	// tileset color cycle
	Pixels24[i]=Pixels24[i+1];
    }
    Pixels24[47]=x;

    x=Pixels24[240];
    for( i=240; i<244; ++i ) {	// units/icons color cycle
	Pixels24[i]=Pixels24[i+1];
    }
    Pixels24[244]=x;

    MapColorCycle();		// FIXME: could be little more informativer
    MustRedraw|=RedrawMap|RedrawInfoPanel;
}

/**
**	Color cycle for 32 bpp video mode.
**
**	FIXME: not correct cycles only palette of tileset.
**	FIXME: Also icons and some units use color cycling.
**	FIXME: must be configured by the tileset or global.
*/
global void ColorCycle32(void)
{
    int i;
    int x;
    VMemType32* pixels;

    //
    //	Color cycle tileset palette
    //
    pixels=TheMap.TileData->Pixels;
    x = pixels[38];
    for(i = 38; i < 47; ++i){
	pixels[i] = pixels[i+1];
    }
    pixels[47] = x;

    x=Pixels32[38];
    for( i=38; i<47; ++i ) {	// tileset color cycle
	Pixels32[i]=Pixels32[i+1];
    }
    Pixels32[47]=x;

    x=Pixels32[240];
    for( i=240; i<244; ++i ) {	// units/icons color cycle
	Pixels32[i]=Pixels32[i+1];
    }
    Pixels32[244]=x;

    MapColorCycle();		// FIXME: could be little more informativer
    MustRedraw|=RedrawMap|RedrawInfoPanel;
}

/**
**	Initializes system palette. Also calls SetPlayersPalette to set
**	palette for all players.
**
**	@param palette VMemType structure, as created by VideoCreateNewPalette
**	@see SetPlayersPalette
*/
global void VideoSetPalette(const VMemType* palette)
{
    if( Pixels ) {
	free(Pixels);
    }
    Pixels=(VMemType*)palette;
    SetPlayersPalette();
}

/**
**	Set the system hardware palette from an independend Palette struct.
**
**	@param palette	System independ palette structure.
*/
global void VideoCreatePalette(const Palette* palette)
{
    VMemType* temp;

    temp = VideoCreateNewPalette(palette);

    VideoSetPalette(temp);
}

#endif

/**
**	Video initialize.
*/
global void InitVideo(void)
{
    if( UseSdl ) {
	InitVideoSdl();
    } else if( UseX11 ) {
	InitVideoX11();
    } else if( UseSVGALib ) {
	InitVideoSVGA();
    } else if( UseWin32 ) {
	InitVideoWin32();
    } else {
	IfDebug( abort(); );
    }

    //
    //	Init video sub modules
    //
    InitGraphic();
    InitLineDraw();
#ifdef NEW_VIDEO
    InitSprite();
    InitCursor();
    switch( VideoDepth ) {
	case  8: ColorCycle=ColorCycle8 ; break;
	case 15:
	case 16: ColorCycle=ColorCycle16; break;
	case 24: ColorCycle=ColorCycle24; break;
	case 32: ColorCycle=ColorCycle32; break;
    }
#endif

    DebugLevel3(__FUNCTION__": %d %d\n",MapWidth,MapHeight);
}

//@}
