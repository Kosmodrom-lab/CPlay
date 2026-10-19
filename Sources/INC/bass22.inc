/* BASS 2.2 C/C++ header file, copyright(c)1999-2005 Ian Luck.
	Please report bugs/suggestions/etc... to bass@un4seen.com

	See the BASS.CHM file for more complete documentation */

' $define BASS_LOAD_DYNAMIC - link dynamic

$ifndef __bass_inc__
$define __bass_inc__

$ifndef BASS_NO_LIB
$use "bass.lib"
$endif

$use "custom\\bass24.lib" ' presets

'# ifdef _WIN32 // Windows
'$include "wtypes.inc"
typedef QWORD uint64
/*# else // OSX
$define WINAPI
$define CALLBACK
typedef unsigned char BYTE
typedef unsigned short WORD
typedef unsigned long DWORD
typedef unsigned long long QWORD
typedef int BOOL
$define TRUE 1
$define FALSE 0
$define LOWORD(a)(WORD)(a)
$define HIWORD(a)(WORD)((a)>>16)
$define MAKELONG(a,b)(DWORD)(((a)&0xffff)|((b)<<16))
# endif*/

$ifndef BASSDEF
'$define BASSDEF(f)WINAPI f
$endif

typedef HMUSIC DWORD		' MOD music handle
typedef HSAMPLE DWORD		' sample handle
typedef HCHANNEL DWORD		' playing sample's channel handle
typedef HSTREAM DWORD		' sample stream handle
typedef HRECORD DWORD		' recording handle
typedef HSYNC DWORD		' synchronizer handle
typedef HDSP DWORD			' DSP handle
typedef HFX DWORD			' DX8 effect handle
typedef HPLUGIN DWORD		' Plugin handle

' Error codes returned by BASS_ErrorGetCode
$define BASS_OK				0	' all is OK
$define BASS_ERROR_MEM		1	' memory error
$define BASS_ERROR_FILEOPEN	2	' can't open the file
$define BASS_ERROR_DRIVER	3	' can't find a free/valid driver
$define BASS_ERROR_BUFLOST	4	' the sample buffer was lost
$define BASS_ERROR_HANDLE	5	' invalid handle
$define BASS_ERROR_FORMAT	6	' unsupported sample format
$define BASS_ERROR_POSITION	7	' invalid playback position
$define BASS_ERROR_INIT		8	' BASS_Init has not been successfully called
$define BASS_ERROR_START	9	' BASS_Start has not been successfully called
$define BASS_ERROR_ALREADY	14	' already initialized/paused/whatever
$define BASS_ERROR_NOPAUSE	16	' not paused
$define BASS_ERROR_NOCHAN	18	' can't get a free channel
$define BASS_ERROR_ILLTYPE	19	' an illegal type was specified
$define BASS_ERROR_ILLPARAM	20	' an illegal parameter was specified
$define BASS_ERROR_NO3D		21	' no 3D support
$define BASS_ERROR_NOEAX	22	' no EAX support
$define BASS_ERROR_DEVICE	23	' illegal device number
$define BASS_ERROR_NOPLAY	24	' not playing
$define BASS_ERROR_FREQ		25	' illegal sample rate
$define BASS_ERROR_NOTFILE	27	' the stream is not a file stream
$define BASS_ERROR_NOHW		29	' no hardware voices available
$define BASS_ERROR_EMPTY	31	' the MOD music has no sequence data
$define BASS_ERROR_NONET	32	' no internet connection could be opened
$define BASS_ERROR_CREATE	33	' couldn't create the file
$define BASS_ERROR_NOFX		34	' effects are not available
$define BASS_ERROR_PLAYING	35	' the channel is playing
$define BASS_ERROR_NOTAVAIL	37	' requested data is not available
$define BASS_ERROR_DECODE	38	' the channel is a "decoding channel"
$define BASS_ERROR_DX		39	' a sufficient DirectX version is not installed
$define BASS_ERROR_TIMEOUT	40	' connection timedout
$define BASS_ERROR_FILEFORM	41	' unsupported file format
$define BASS_ERROR_SPEAKER	42	' unavailable speaker
$define BASS_ERROR_UNKNOWN	-1	' some other mystery error

' Initialization flags
$define BASS_DEVICE_8BITS	1	' use 8 bit resolution, else 16 bit
$define BASS_DEVICE_MONO	2	' use mono, else stereo
$define BASS_DEVICE_3D		4	' enable 3D functionality
/* If the BASS_DEVICE_3D flag is not specified when initilizing BASS,
then the 3D flags(BASS_SAMPLE_3D and BASS_MUSIC_3D)are ignored when
loading/creating a sample/stream/music. */
$define BASS_DEVICE_LATENCY	256	' calculate device latency(BASS_INFO struct)
$define BASS_DEVICE_SPEAKERS 2048	' force enabling of speaker assignment
$define BASS_DEVICE_NOSPEAKER 4096	' ignore speaker arrangement

' DirectSound interfaces(for use with BASS_GetDSoundObject)
$define BASS_OBJECT_DS		1	' IDirectSound
$define BASS_OBJECT_DS3DL	2	' IDirectSound3DListener

type BASS_INFO
	DWORD flags	' device capabilities(DSCAPS_xxx flags)
	DWORD hwsize	' size of total device hardware memory
	DWORD hwfree	' size of free device hardware memory
	DWORD freesam	' number of free sample slots in the hardware
	DWORD free3d	' number of free 3D sample slots in the hardware
	DWORD minrate	' min sample rate supported by the hardware
	DWORD maxrate	' max sample rate supported by the hardware
	BOOL eax		' device supports EAX?(always FALSE if BASS_DEVICE_3D was not used)
	DWORD minbuf	' recommended minimum buffer length in ms(requires BASS_DEVICE_LATENCY)
	DWORD dsver	' DirectSound version
	DWORD latency	' delay(in ms)before start of playback(requires BASS_DEVICE_LATENCY)
	DWORD initflags' "flags" parameter of BASS_Init call
	DWORD speakers ' number of speakers available
	pointer	driver	' driver
endtype

' BASS_INFO flags(from DSOUND.H)
$define DSCAPS_CONTINUOUSRATE	0x00000010
/* supports all sample rates between min/maxrate */
$define DSCAPS_EMULDRIVER		0x00000020
/* device does NOT have hardware DirectSound support */
$define DSCAPS_CERTIFIED		0x00000040
/* device driver has been certified by Microsoft */
/* The following flags tell what type of samples are supported by HARDWARE
mixing*/
$define DSCAPS_SECONDARYMONO	0x00000100	' mono
$define DSCAPS_SECONDARYSTEREO	0x00000200	' stereo
$define DSCAPS_SECONDARY8BIT	0x00000400	' 8 bit
$define DSCAPS_SECONDARY16BIT	0x00000800	' 16 bit

type BASS_RECORDINFO
	DWORD flags	' device capabilities(DSCCAPS_xxx flags)
	DWORD formats	' supported standard formats(WAVE_FORMAT_xxx flags)
	DWORD inputs	' number of inputs
	BOOL singlein	' TRUE = only 1 input can be set at a time
	pointer	driver	' driver
endtype

' BASS_RECORDINFO flags(from DSOUND.H)
$define DSCCAPS_EMULDRIVER	DSCAPS_EMULDRIVER	' device does NOT have hardware DirectSound recording support
$define DSCCAPS_CERTIFIED	DSCAPS_CERTIFIED	' device driver has been certified by Microsoft

' defines for formats field of BASS_RECORDINFO(from MMSYSTEM.H)
$ifndef WAVE_FORMAT_1M08
$define WAVE_FORMAT_1M08	0x00000001	/* 11.025 kHz, Mono,	8-bit	*/
$define WAVE_FORMAT_1S08	0x00000002	/* 11.025 kHz, Stereo, 8-bit	*/
$define WAVE_FORMAT_1M16	0x00000004	/* 11.025 kHz, Mono,	16-bit */
$define WAVE_FORMAT_1S16	0x00000008	/* 11.025 kHz, Stereo, 16-bit */
$define WAVE_FORMAT_2M08	0x00000010	/* 22.05	kHz, Mono,	8-bit	*/
$define WAVE_FORMAT_2S08	0x00000020	/* 22.05	kHz, Stereo, 8-bit	*/
$define WAVE_FORMAT_2M16	0x00000040	/* 22.05	kHz, Mono,	16-bit */
$define WAVE_FORMAT_2S16	0x00000080	/* 22.05	kHz, Stereo, 16-bit */
$define WAVE_FORMAT_4M08	0x00000100	/* 44.1	kHz, Mono,	8-bit	*/
$define WAVE_FORMAT_4S08	0x00000200	/* 44.1	kHz, Stereo, 8-bit	*/
$define WAVE_FORMAT_4M16	0x00000400	/* 44.1	kHz, Mono,	16-bit */
$define WAVE_FORMAT_4S16	0x00000800	/* 44.1	kHz, Stereo, 16-bit */
$endif

' Sample info structure & flags
type BASS_SAMPLE
	DWORD freq		' default playback rate
	DWORD volume	' default volume(0-100)
	int pan		' default pan(-100=left, 0=middle, 100=right)
	DWORD flags	' BASS_SAMPLE_xxx flags
	DWORD length	' length(in bytes)
	DWORD max		' maximum simultaneous playbacks
	DWORD origres	' original resolution bits
	DWORD chans	' number of channels
/* The following are the sample's default 3D attributes(if the sample
is 3D, BASS_SAMPLE_3D is in flags)see BASS_ChannelSet3DAttributes */
	DWORD mode3d	' BASS_3DMODE_xxx mode
	float mindist	' minimum distance
	float maxdist	' maximum distance
	DWORD iangle	' angle of inside projection cone
	DWORD oangle	' angle of outside projection cone
	DWORD outvol	' delta-volume outside the projection cone
/* The following are the defaults used if the sample uses the DirectX 7
voice allocation/management features. */
	DWORD vam		' voice allocation/management flags(BASS_VAM_xxx)
	DWORD priority	' priority(0=lowest, 0xffffffff=highest)
endtype

$define BASS_SAMPLE_8BITS		1	' 8 bit
$define BASS_SAMPLE_FLOAT		256	' 32-bit floating-point
$define BASS_SAMPLE_MONO		2	' mono
$define BASS_SAMPLE_LOOP		4	' looped
$define BASS_SAMPLE_3D			8	' 3D functionality enabled
$define BASS_SAMPLE_SOFTWARE	16	' it's NOT using hardware mixing
$define BASS_SAMPLE_MUTEMAX		32	' muted at max distance(3D only)
$define BASS_SAMPLE_VAM			64	' uses the DX7 voice allocation & management
$define BASS_SAMPLE_FX			128	' old implementation of DX8 effects are enabled
$define BASS_SAMPLE_OVER_VOL	0x10000	' override lowest volume
$define BASS_SAMPLE_OVER_POS	0x20000	' override longest playing
$define BASS_SAMPLE_OVER_DIST	0x30000 ' override furthest from listener(3D only)

$define BASS_STREAM_PRESCAN		0x20000 ' enable pin-point seeking(MP3/MP2/MP1)
$define BASS_MP3_SETPOS			BASS_STREAM_PRESCAN
$define BASS_STREAM_AUTOFREE	0x40000	' automatically free the stream when it stop/ends
$define BASS_STREAM_RESTRATE	0x80000	' restrict the download rate of internet file streams
$define BASS_STREAM_BLOCK		0x100000' download/play internet file stream in small blocks
$define BASS_STREAM_DECODE		0x200000' don't play the stream, only decode(BASS_ChannelGetData)
$define BASS_STREAM_STATUS		0x800000' give server status info(HTTP/ICY tags)in DOWNLOADPROC

$define BASS_MUSIC_FLOAT		BASS_SAMPLE_FLOAT ' 32-bit floating-point
$define BASS_MUSIC_MONO			BASS_SAMPLE_MONO ' force mono mixing(less CPU usage)
$define BASS_MUSIC_LOOP			BASS_SAMPLE_LOOP ' loop music
$define BASS_MUSIC_3D			BASS_SAMPLE_3D ' enable 3D functionality
$define BASS_MUSIC_FX			BASS_SAMPLE_FX ' enable old implementation of DX8 effects
$define BASS_MUSIC_AUTOFREE		BASS_STREAM_AUTOFREE ' automatically free the music when it stop/ends
$define BASS_MUSIC_DECODE		BASS_STREAM_DECODE ' don't play the music, only decode(BASS_ChannelGetData)
$define BASS_MUSIC_PRESCAN		BASS_STREAM_PRESCAN	' calculate playback length
$define BASS_MUSIC_CALCLEN		BASS_MUSIC_PRESCAN
$define BASS_MUSIC_RAMP			0x200	' normal ramping
$define BASS_MUSIC_RAMPS		0x400	' sensitive ramping
$define BASS_MUSIC_SURROUND		0x800	' surround sound
$define BASS_MUSIC_SURROUND2	0x1000	' surround sound(mode 2)
$define BASS_MUSIC_FT2MOD		0x2000	' play .MOD as FastTracker 2 does
$define BASS_MUSIC_PT1MOD		0x4000	' play .MOD as ProTracker 1 does
$define BASS_MUSIC_NONINTER		0x10000	' non-interpolated mixing
$define BASS_MUSIC_POSRESET		0x8000	' stop all notes when moving position
$define BASS_MUSIC_POSRESETEX	0x400000' stop all notes and reset bmp/etc when moving position
$define BASS_MUSIC_STOPBACK		0x80000	' stop the music on a backwards jump effect
$define BASS_MUSIC_NOSAMPLE		0x100000' don't load the samples

' Speaker assignment flags
$define BASS_SPEAKER_FRONT	0x1000000	' front speakers
$define BASS_SPEAKER_REAR	0x2000000	' rear/side speakers
$define BASS_SPEAKER_CENLFE	0x3000000	' center & LFE speakers(5.1)
$define BASS_SPEAKER_REAR2	0x4000000	' rear center speakers(7.1)
'$define BASS_SPEAKER_N(n)	((n)<<24)	' n'th pair of speakers(max 15)
$define BASS_SPEAKER_LEFT	0x10000000	' modifier: left
$define BASS_SPEAKER_RIGHT	0x20000000	' modifier: right
$define BASS_SPEAKER_FRONTLEFT	BASS_SPEAKER_FRONT|BASS_SPEAKER_LEFT
$define BASS_SPEAKER_FRONTRIGHT	BASS_SPEAKER_FRONT|BASS_SPEAKER_RIGHT
$define BASS_SPEAKER_REARLEFT	BASS_SPEAKER_REAR|BASS_SPEAKER_LEFT
$define BASS_SPEAKER_REARRIGHT	BASS_SPEAKER_REAR|BASS_SPEAKER_RIGHT
$define BASS_SPEAKER_CENTER		BASS_SPEAKER_CENLFE|BASS_SPEAKER_LEFT
$define BASS_SPEAKER_LFE		BASS_SPEAKER_CENLFE|BASS_SPEAKER_RIGHT
$define BASS_SPEAKER_REAR2LEFT	BASS_SPEAKER_REAR2|BASS_SPEAKER_LEFT
$define BASS_SPEAKER_REAR2RIGHT	BASS_SPEAKER_REAR2|BASS_SPEAKER_RIGHT

$define BASS_UNICODE			0x80000000

$define BASS_RECORD_PAUSE		0x8000	' start recording paused

'$define MAKEMUSICPOS(order,row)(0x80000000|MAKELONG(order,row))

' DX7 voice allocation flags
$define BASS_VAM_HARDWARE		1
/* Play the sample in hardware. If no hardware voices are available then
the "play" call will fail */
$define BASS_VAM_SOFTWARE		2
/* Play the sample in software(ie. non-accelerated). No other VAM flags
may be used together with this flag. */

' DX7 voice management flags
/* These flags enable hardware resource stealing... if the hardware has no
available voices, a currently playing buffer will be stopped to make room for
the new buffer. NOTE: only samples loaded/created with the BASS_SAMPLE_VAM
flag are considered for termination by the DX7 voice management. */
$define BASS_VAM_TERM_TIME		4
/* If there are no free hardware voices, the buffer to be terminated will be
the one with the least time left to play. */
$define BASS_VAM_TERM_DIST		8
/* If there are no free hardware voices, the buffer to be terminated will be
one that was loaded/created with the BASS_SAMPLE_MUTEMAX flag and is beyond
it's max distance. If there are no buffers that match this criteria, then the
"play" call will fail. */
$define BASS_VAM_TERM_PRIO		16
/* If there are no free hardware voices, the buffer to be terminated will be
the one with the lowest priority. */

type BASS_CHANNELINFO
	DWORD freq		' default playback rate
	DWORD chans	' channels
	DWORD flags	' BASS_SAMPLE/STREAM/MUSIC/SPEAKER flags
	DWORD ctype	' type of channel
	DWORD origres	' original resolution
endtype

' BASS_CHANNELINFO types
$define BASS_CTYPE_SAMPLE		1
$define BASS_CTYPE_RECORD		2
$define BASS_CTYPE_STREAM		0x10000
$define BASS_CTYPE_STREAM_WAV	0x10001
$define BASS_CTYPE_STREAM_OGG	0x10002
$define BASS_CTYPE_STREAM_MP1	0x10003
$define BASS_CTYPE_STREAM_MP2	0x10004
$define BASS_CTYPE_STREAM_MP3	0x10005
$define BASS_CTYPE_STREAM_AIFF	0x10006
$define BASS_CTYPE_MUSIC_MOD	0x20000
$define BASS_CTYPE_MUSIC_MTM	0x20001
$define BASS_CTYPE_MUSIC_S3M	0x20002
$define BASS_CTYPE_MUSIC_XM		0x20003
$define BASS_CTYPE_MUSIC_IT		0x20004
$define BASS_CTYPE_MUSIC_MO3	0x00100 ' mo3 flag

' 3D vector(for 3D positions/velocities/orientations)
type BASS_3DVECTOR
'$ifdef __cplusplus
'	BASS_3DVECTOR(){}
'	BASS_3DVECTOR(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
'$endif
	float x	' +=right, -=left
	float y	' +=up, -=down
	float z	' +=front, -=behind
endtype

' 3D channel modes
$define BASS_3DMODE_NORMAL		0
/* normal 3D processing */
$define BASS_3DMODE_RELATIVE	1
/* The channel's 3D position(position/velocity/orientation)are relative to
the listener. When the listener's position/velocity/orientation is changed
with BASS_Set3DPosition, the channel's position relative to the listener does
not change. */
$define BASS_3DMODE_OFF			2
/* Turn off 3D processing on the channel, the sound will be played
in the center. */

'$ifdef _WIN32
' EAX environments, use with BASS_SetEAXParameters

$define EAX_ENVIRONMENT_GENERIC 0
$define EAX_ENVIRONMENT_PADDEDCELL 1
$define EAX_ENVIRONMENT_ROOM 2
$define EAX_ENVIRONMENT_BATHROOM 3
$define EAX_ENVIRONMENT_LIVINGROOM 4
$define EAX_ENVIRONMENT_STONEROOM 5
$define EAX_ENVIRONMENT_AUDITORIUM 6
$define EAX_ENVIRONMENT_CONCERTHALL 7
$define EAX_ENVIRONMENT_CAVE 8
$define EAX_ENVIRONMENT_ARENA 9
$define EAX_ENVIRONMENT_HANGAR 10
$define EAX_ENVIRONMENT_CARPETEDHALLWAY 11
$define EAX_ENVIRONMENT_HALLWAY 12
$define EAX_ENVIRONMENT_STONECORRIDOR 13
$define EAX_ENVIRONMENT_ALLEY 14
$define EAX_ENVIRONMENT_FOREST 15
$define EAX_ENVIRONMENT_CITY 16
$define EAX_ENVIRONMENT_MOUNTAINS 17
$define EAX_ENVIRONMENT_QUARRY 18
$define EAX_ENVIRONMENT_PLAIN 19
$define EAX_ENVIRONMENT_PARKINGLOT 20
$define EAX_ENVIRONMENT_SEWERPIPE 21
$define EAX_ENVIRONMENT_UNDERWATER 22
$define EAX_ENVIRONMENT_DRUGGED 23
$define EAX_ENVIRONMENT_DIZZY 24
$define EAX_ENVIRONMENT_PSYCHOTIC 25
$define EAX_ENVIRONMENT_COUNT 26			' total number of environments

declare import, BASS_SetEAXPreset alias BASS_SetEAXParameters(GUID g byval),BOOL
' EAX presets, usage: BASS_SetEAXParameters(EAX_PRESET_xxx)
/*
$define EAX_PRESET_GENERIC	EAX_ENVIRONMENT_GENERIC,0.5F,1.493F,0.5F
$define EAX_PRESET_PADDEDCELL	EAX_ENVIRONMENT_PADDEDCELL,0.25F,0.1F,0.0F
$define EAX_PRESET_ROOM	EAX_ENVIRONMENT_ROOM,0.417F,0.4F,0.666F
$define EAX_PRESET_BATHROOM	EAX_ENVIRONMENT_BATHROOM,0.653F,1.499F,0.166F
$define EAX_PRESET_LIVINGROOM	EAX_ENVIRONMENT_LIVINGROOM,0.208F,0.478F,0.0F
$define EAX_PRESET_STONEROOM	EAX_ENVIRONMENT_STONEROOM,0.5F,2.309F,0.888F
$define EAX_PRESET_AUDITORIUM	EAX_ENVIRONMENT_AUDITORIUM,0.403F,4.279F,0.5F
$define EAX_PRESET_CONCERTHALL	EAX_ENVIRONMENT_CONCERTHALL,0.5F,3.961F,0.5F
$define EAX_PRESET_CAVE	EAX_ENVIRONMENT_CAVE,0.5F,2.886F,1.304F
$define EAX_PRESET_ARENA	EAX_ENVIRONMENT_ARENA,0.361F,7.284F,0.332F
$define EAX_PRESET_HANGAR	EAX_ENVIRONMENT_HANGAR,0.5F,10.0F,0.3F
$define EAX_PRESET_CARPETEDHALLWAY EAX_ENVIRONMENT_CARPETEDHALLWAY,0.153F,0.259F,2.0F
$define EAX_PRESET_HALLWAY	EAX_ENVIRONMENT_HALLWAY,0.361F,1.493F,0.0F
$define EAX_PRESET_STONECORRIDOR	EAX_ENVIRONMENT_STONECORRIDOR,0.444F,2.697F,0.638F
$define EAX_PRESET_ALLEY	EAX_ENVIRONMENT_ALLEY,0.25F,1.752F,0.776F
$define EAX_PRESET_FOREST	EAX_ENVIRONMENT_FOREST,0.111F,3.145F,0.472F
$define EAX_PRESET_CITY	EAX_ENVIRONMENT_CITY,0.111F,2.767F,0.224F
$define EAX_PRESET_MOUNTAINS	EAX_ENVIRONMENT_MOUNTAINS,0.194F,7.841F,0.472F
$define EAX_PRESET_QUARRY	EAX_ENVIRONMENT_QUARRY,1.0F,1.499F,0.5F
$define EAX_PRESET_PLAIN	EAX_ENVIRONMENT_PLAIN,0.097F,2.767F,0.224F
$define EAX_PRESET_PARKINGLOT	EAX_ENVIRONMENT_PARKINGLOT,0.208F,1.652F,1.5F
$define EAX_PRESET_SEWERPIPE	EAX_ENVIRONMENT_SEWERPIPE,0.652F,2.886F,0.25F
$define EAX_PRESET_UNDERWATER	EAX_ENVIRONMENT_UNDERWATER,1.0F,1.499F,0.0F
$define EAX_PRESET_DRUGGED	EAX_ENVIRONMENT_DRUGGED,0.875F,8.392F,1.388F
$define EAX_PRESET_DIZZY	EAX_ENVIRONMENT_DIZZY,0.139F,17.234F,0.666F
$define EAX_PRESET_PSYCHOTIC	EAX_ENVIRONMENT_PSYCHOTIC,0.486F,7.563F,0.806F
*/
extern EAX_PRESET_GENERIC as GUID
extern EAX_PRESET_PADDEDCELL as GUID
extern EAX_PRESET_ROOM as GUID
extern EAX_PRESET_BATHROOM as GUID
extern EAX_PRESET_LIVINGROOM as GUID
extern EAX_PRESET_STONEROOM as GUID
extern EAX_PRESET_AUDITORIUM as GUID
extern EAX_PRESET_CONCERTHALL as GUID
extern EAX_PRESET_CAVE as GUID
extern EAX_PRESET_ARENA as GUID
extern EAX_PRESET_HANGAR as GUID
extern EAX_PRESET_CARPETEDHALLWAY as GUID
extern EAX_PRESET_HALLWAY as GUID
extern EAX_PRESET_STONECORRIDOR as GUID
extern EAX_PRESET_ALLEY as GUID
extern EAX_PRESET_FOREST as GUID
extern EAX_PRESET_CITY as GUID
extern EAX_PRESET_MOUNTAINS as GUID
extern EAX_PRESET_QUARRY as GUID
extern EAX_PRESET_PLAIN as GUID
extern EAX_PRESET_PARKINGLOT as GUID
extern EAX_PRESET_SEWERPIPE as GUID
extern EAX_PRESET_UNDERWATER as GUID
extern EAX_PRESET_DRUGGED as GUID
extern EAX_PRESET_DIZZY as GUID
extern EAX_PRESET_PSYCHOTIC as GUID

' software 3D mixing algorithm modes(used with BASS_Set3DAlgorithm)
$define BASS_3DALG_DEFAULT	0
/* default algorithm(currently translates to BASS_3DALG_OFF)*/
$define BASS_3DALG_OFF		1
/* Uses normal left and right panning. The vertical axis is ignored except for
scaling of volume due to distance. Doppler shift and volume scaling are still
applied, but the 3D filtering is not performed. This is the most CPU efficient
software implementation, but provides no virtual 3D audio effect. Head Related
Transfer Function processing will not be done. Since only normal stereo panning
is used, a channel using this algorithm may be accelerated by a 2D hardware
voice if no free 3D hardware voices are available. */
$define BASS_3DALG_FULL		2
/* This algorithm gives the highest quality 3D audio effect, but uses more CPU.
Requires Windows 98 2nd Edition or Windows 2000 that uses WDM drivers, if this
mode is not available then BASS_3DALG_OFF will be used instead. */
$define BASS_3DALG_LIGHT	3
/* This algorithm gives a good 3D audio effect, and uses less CPU than the FULL
mode. Requires Windows 98 2nd Edition or Windows 2000 that uses WDM drivers, if
this mode is not available then BASS_3DALG_OFF will be used instead. */

typedef STREAMPROC int
'typedef DWORD(CALLBACK STREAMPROC)(HSTREAM handle,pointer buffer, DWORD length, DWORD user)
/* User stream callback function. NOTE: A stream function should obviously be as quick
as possible, other streams(and MOD musics)can't be mixed until it's finished.
handle : The stream that needs writing
buffer : Buffer to write the samples in
length : Number of bytes to write
user	: The 'user' parameter value given when calling BASS_StreamCreate
RETURN : Number of bytes written. Set the BASS_STREAMPROC_END flag to end
		the stream. */

$define BASS_STREAMPROC_END		0x80000000	' end of user stream flag

' BASS_StreamGetFilePosition modes
$define BASS_FILEPOS_CURRENT	0
$define BASS_FILEPOS_DECODE		BASS_FILEPOS_CURRENT
$define BASS_FILEPOS_DOWNLOAD	1
$define BASS_FILEPOS_END		2
$define BASS_FILEPOS_START		3

' STREAMFILEPROC actions
$define BASS_FILE_CLOSE		0
$define BASS_FILE_READ		1
$define BASS_FILE_LEN		3
$define BASS_FILE_SEEK		4

typedef STREAMFILEPROC int
'typedef DWORD(CALLBACK STREAMFILEPROC)(DWORD action, DWORD param1, DWORD param2, DWORD user)
/* User file stream callback function.
action : The action to perform, one of BASS_FILE_xxx values.
param1 : Depends on "action"
param2 : Depends on "action"
user	: The 'user' parameter value given when calling BASS_StreamCreate
RETURN : Depends on "action" */

typedef DOWNLOADPROC int
'typedef void(CALLBACK DOWNLOADPROC)(pointer buffer, DWORD length, DWORD user)
/* Internet stream download callback function.
buffer : Buffer containing the downloaded data... NULL=end of download
length : Number of bytes in the buffer
user	: The 'user' parameter value given when calling BASS_StreamCreateURL */

/* Sync types(with BASS_ChannelSetSync "param" and SYNCPROC "data"
definitions)& flags. */
$define BASS_SYNC_POS	0
/* Sync when a channel reaches a position.
param: position in bytes
data : not used */
$define BASS_SYNC_END		2
/* Sync when a channel reaches the end.
param: not used
data : 1 = the sync is triggered by a backward jump in a MOD music*/
$define BASS_SYNC_META		4
/* Sync when metadata is received in a stream.
param: not used
data : pointer to the metadata */
$define BASS_SYNC_SLIDE		5
/* Sync when an attribute slide is completed.
param: not used
data : the type of slide completed(one of the BASS_SLIDE_xxx values)*/
$define BASS_SYNC_STALL		6
/* Sync when playback has stalled.
param: not used
data : 0=stalled, 1=resumed */
$define BASS_SYNC_DOWNLOAD	7
/* Sync when downloading of an internet(or "buffered" user file)stream has ended.
param: not used
data : not used */
$define BASS_SYNC_FREE	8
/* Sync when a channel is freed.
param: not used
data : not used */
$define BASS_SYNC_MUSICPOS		10
/* Sync when a MOD music reaches an order:row position.
param: LOWORD=order(0=first, -1=all)HIWORD=row(0=first, -1=all)
data : LOWORD=order HIWORD=row */
$define BASS_SYNC_MUSICINST	1
/* Sync when an instrument(sample for the non-instrument based formats)
is played in a MOD music(not including retrigs).
param: LOWORD=instrument(1=first)HIWORD=note(0=c0...119=b9, -1=all)
data : LOWORD=note HIWORD=volume(0-64)*/
$define BASS_SYNC_MUSICFX	3
/* Sync when the "sync" effect(XM/MTM/MOD: E8x/Wxx, IT/S3M: S2x)is used.
param: 0:data=pos, 1:data="x" value
data : param=0: LOWORD=order HIWORD=row, param=1: "x" value */
$define BASS_SYNC_MESSAGE	0x20000000	' FLAG: post a Windows message(instead of callback)
/* When using a window message "callback", the message to post is given in the "proc"
parameter of BASS_ChannelSetSync, and is posted to the window specified in the BASS_Init
call. The message parameters are: WPARAM = data, LPARAM = user. */
$define BASS_SYNC_MIXTIME	0x40000000	' FLAG: sync at mixtime, else at playtime
$define BASS_SYNC_ONETIME	0x80000000	' FLAG: sync only once, else continuously

typedef SYNCPROC int
'typedef void(CALLBACK SYNCPROC)(HSYNC handle, DWORD channel, DWORD data, DWORD user)
/* Sync callback function. NOTE: a sync callback function should be very
quick as other syncs can't be processed until it has finished. If the sync
is a "mixtime" sync, then other streams and MOD musics can't be mixed until
it's finished either.
handle : The sync that has occured
channel: Channel that the sync occured in
data	: Additional data associated with the sync's occurance
user	: The 'user' parameter given when calling BASS_ChannelSetSync */

typedef DSPPROC int
'typedef void(CALLBACK DSPPROC)(HDSP handle, DWORD channel,pointer buffer, DWORD length, DWORD user)
/* DSP callback function. NOTE: A DSP function should obviously be as quick as
possible... other DSP functions, streams and MOD musics can not be processed
until it's finished.
handle : The DSP handle
channel: Channel that the DSP is being applied to
buffer : Buffer to apply the DSP to
length : Number of bytes in the buffer
user	: The 'user' parameter given when calling BASS_ChannelSetDSP */

typedef RECORDPROC int
'typedef BOOL(CALLBACK RECORDPROC)(HRECORD handle,pointer buffer, DWORD length, DWORD user)
/* Recording callback function.
handle : The recording handle
buffer : Buffer containing the recorded sample data
length : Number of bytes
user	: The 'user' parameter value given when calling BASS_RecordStart
RETURN : TRUE = continue recording, FALSE = stop */

' BASS_ChannelGetData flags
$define BASS_DATA_AVAILABLE	0			' query how much data is buffered
$define BASS_DATA_FLOAT		0x40000000	' flag: return floating-point sample data
$define BASS_DATA_FFT512	0x80000000	' 512 sample FFT
$define BASS_DATA_FFT1024	0x80000001	' 1024 FFT
$define BASS_DATA_FFT2048	0x80000002	' 2048 FFT
$define BASS_DATA_FFT4096	0x80000003	' 4096 FFT
$define BASS_DATA_FFT_INDIVIDUAL 0x10	' FFT flag: FFT for each channel, else all combined
$define BASS_DATA_FFT_NOWINDOW	0x20	' FFT flag: no Hanning window

' BASS_StreamGetTags types : what's returned
$define BASS_TAG_ID3		0	' ID3v1 tags : 128 byte block
$define BASS_TAG_ID3V2		1	' ID3v2 tags : variable length block
$define BASS_TAG_OGG		2	' OGG comments : array of null-terminated strings
$define BASS_TAG_HTTP		3	' HTTP headers : array of null-terminated strings
$define BASS_TAG_ICY		4	' ICY headers : array of null-terminated strings
$define BASS_TAG_META		5	' ICY metadata : null-terminated string
$define BASS_TAG_VENDOR		9	' OGG encoder : null-terminated string

' BASS_MusicSet/GetAttribute options
$define BASS_MUSIC_ATTRIB_AMPLIFY	0
$define BASS_MUSIC_ATTRIB_PANSEP	1
$define BASS_MUSIC_ATTRIB_PSCALER	2
$define BASS_MUSIC_ATTRIB_BPM		3
$define BASS_MUSIC_ATTRIB_SPEED		4
$define BASS_MUSIC_ATTRIB_VOL_GLOBAL 5
$define BASS_MUSIC_ATTRIB_VOL_CHAN	0x100 ' + channel #
$define BASS_MUSIC_ATTRIB_VOL_INST	0x200 ' + instrument #

'$ifdef _WIN32
' DX8 effect types, use with BASS_ChannelSetFX
$define BASS_FX_CHORUS 0	' GUID_DSFX_STANDARD_CHORUS
$define BASS_FX_COMPRESSOR 1	' GUID_DSFX_STANDARD_COMPRESSOR
$define BASS_FX_DISTORTION 2	' GUID_DSFX_STANDARD_DISTORTION
$define BASS_FX_ECHO 3	' GUID_DSFX_STANDARD_ECHO
$define BASS_FX_FLANGER 4	' GUID_DSFX_STANDARD_FLANGER
$define BASS_FX_GARGLE 5	' GUID_DSFX_STANDARD_GARGLE
$define BASS_FX_I3DL2REVERB 6 ' GUID_DSFX_STANDARD_I3DL2REVERB
$define BASS_FX_PARAMEQ 7	' GUID_DSFX_STANDARD_PARAMEQ
$define BASS_FX_REVERB 8	' GUID_DSFX_WAVES_REVERB

type BASS_FXCHORUS
	float	fWetDryMix
	float	fDepth
	float	fFeedback
	float	fFrequency
	DWORD	lWaveform	' 0=triangle, 1=sine
	float	fDelay
	DWORD	lPhase		' BASS_FX_PHASE_xxx
endtype 		' DSFXChorus

type BASS_FXCOMPRESSOR
	float	fGain
	float	fAttack
	float	fRelease
	float	fThreshold
	float	fRatio
	float	fPredelay
endtype 	' DSFXCompressor

type BASS_FXDISTORTION
	float	fGain
	float	fEdge
	float	fPostEQCenterFrequency
	float	fPostEQBandwidth
	float	fPreLowpassCutoff
endtype 	' DSFXDistortion

type BASS_FXECHO
	float	fWetDryMix
	float	fFeedback
	float	fLeftDelay
	float	fRightDelay
	BOOL	lPanDelay
endtype 			' DSFXEcho

type BASS_FXFLANGER
	float	fWetDryMix
	float	fDepth
	float	fFeedback
	float	fFrequency
	DWORD	lWaveform	' 0=triangle, 1=sine
	float	fDelay
	DWORD	lPhase		' BASS_FX_PHASE_xxx
endtype 		' DSFXFlanger

type BASS_FXGARGLE
	DWORD	dwRateHz	' Rate of modulation in hz
	DWORD	dwWaveShape	' 0=triangle, 1=square
endtype 		' DSFXGargle

type BASS_FXI3DL2REVERB
	int	lRoom	' [-10000, 0]	default: -1000 mB
	int	lRoomHF	' [-10000, 0]	default: 0 mB
	float	flRoomRolloffFactor	' [0.0, 10.0]	default: 0.0
	float	flDecayTime	' [0.1, 20.0]	default: 1.49s
	float	flDecayHFRatio	' [0.1, 2.0]	default: 0.83
	int	lReflections	' [-10000, 1000]	default: -2602 mB
	float	flReflectionsDelay	' [0.0, 0.3]	default: 0.007 s
	int	lReverb	' [-10000, 2000]	default: 200 mB
	float	flReverbDelay	' [0.0, 0.1]	default: 0.011 s
	float	flDiffusion	' [0.0, 100.0]	default: 100.0 %
	float	flDensity	' [0.0, 100.0]	default: 100.0 %
	float	flHFReference	' [20.0, 20000.0]	default: 5000.0 Hz
endtype 	' DSFXI3DL2Reverb

type BASS_FXPARAMEQ
	float	fCenter
	float	fBandwidth
	float	fGain
endtype 		' DSFXParamEq

type BASS_FXREVERB
	float	fInGain	' [-96.0,0.0]	default: 0.0 dB
	float	fReverbMix	' [-96.0,0.0]	default: 0.0 db
	float	fReverbTime	' [0.001,3000.0]	default: 1000.0 ms
	float	fHighFreqRTRatio	' [0.001,0.999]	default: 0.001
endtype 		' DSFXWavesReverb

$define BASS_FX_PHASE_NEG_180	0
$define BASS_FX_PHASE_NEG_90	1
$define BASS_FX_PHASE_ZERO	2
$define BASS_FX_PHASE_90	3
$define BASS_FX_PHASE_180	4
'$endif

' BASS_ChannelIsActive return values
$define BASS_ACTIVE_STOPPED	0
$define BASS_ACTIVE_PLAYING	1
$define BASS_ACTIVE_STALLED	2
$define BASS_ACTIVE_PAUSED	3

' BASS_ChannelIsSliding return flags
$define BASS_SLIDE_FREQ	1
$define BASS_SLIDE_VOL	2
$define BASS_SLIDE_PAN	4

' BASS_RecordSetInput flags
$define BASS_INPUT_OFF		0x10000
$define BASS_INPUT_ON		0x20000
$define BASS_INPUT_LEVEL	0x40000

$define BASS_INPUT_TYPE_MASK		0xff000000
$define BASS_INPUT_TYPE_UNDEF		0x00000000
$define BASS_INPUT_TYPE_DIGITAL		0x01000000
$define BASS_INPUT_TYPE_LINE		0x02000000
$define BASS_INPUT_TYPE_MIC			0x03000000
$define BASS_INPUT_TYPE_SYNTH		0x04000000
$define BASS_INPUT_TYPE_CD			0x05000000
$define BASS_INPUT_TYPE_PHONE		0x06000000
$define BASS_INPUT_TYPE_SPEAKER		0x07000000
$define BASS_INPUT_TYPE_WAVE		0x08000000
$define BASS_INPUT_TYPE_AUX			0x09000000
$define BASS_INPUT_TYPE_ANALOG		0x0a000000

' BASS_Set/GetConfig options
$define BASS_CONFIG_BUFFER			0
$define BASS_CONFIG_UPDATEPERIOD	1
$define BASS_CONFIG_MAXVOL			3
$define BASS_CONFIG_GVOL_SAMPLE		4
$define BASS_CONFIG_GVOL_STREAM		5
$define BASS_CONFIG_GVOL_MUSIC		6
$define BASS_CONFIG_CURVE_VOL		7
$define BASS_CONFIG_CURVE_PAN		8
$define BASS_CONFIG_FLOATDSP		9
$define BASS_CONFIG_3DALGORITHM		10
$define BASS_CONFIG_NET_TIMEOUT		11
$define BASS_CONFIG_NET_BUFFER		12
$define BASS_CONFIG_PAUSE_NOPLAY	13
$define BASS_CONFIG_NET_NOPROXY		14
$define BASS_CONFIG_NET_PREBUF		15
$define BASS_CONFIG_NET_AGENT		16

$ifndef BASS_LOAD_DYNAMIC
declare import, BASS_SetConfig(DWORD option, DWORD value),DWORD
declare import, BASS_GetConfig(DWORD option),DWORD
declare import, BASS_GetVersion(),DWORD
declare import, BASS_GetDeviceDescription(DWORD device),pointer
declare import, BASS_ErrorGetCode(),int
'# ifdef _WIN32
declare import, BASS_Init(int device, DWORD freq, DWORD flags, HWND win,pointer dsguid),BOOL
'# else
'BOOL BASSDEF(BASS_Init)(int device, DWORD freq, DWORD flags,pointer win,pointer dsguid)
'# endif
declare import, BASS_SetDevice(DWORD device),BOOL
declare import, BASS_GetDevice(),DWORD
declare import, BASS_Free(),BOOL
'# ifdef _WIN32
declare import, BASS_GetDSoundObject(DWORD object),pointer
'# endif
declare import, BASS_GetInfo(pointer info),BOOL
declare import, BASS_Update(),BOOL
declare import, BASS_GetCPU(),float
declare import, BASS_Start(),BOOL
declare import, BASS_Stop(),BOOL
declare import, BASS_Pause(),BOOL
declare import, BASS_SetVolume(DWORD volume),BOOL
declare import, BASS_GetVolume(),DWORD

declare import, BASS_PluginLoad(pointer _file),HPLUGIN
declare import, BASS_PluginFree(HPLUGIN handle),BOOL

declare import, BASS_Set3DFactors(float distf, float rollf, float doppf),BOOL
declare import, BASS_Get3DFactors(pointer distf,pointer rollf,pointer doppf),BOOL
declare import, BASS_Set3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare import, BASS_Get3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare import, BASS_Apply3D()
'# ifdef _WIN32
declare import, BASS_SetEAXParameters(int env, float vol, float decay, float damp),BOOL
declare import, BASS_GetEAXParameters(pointer env,pointer vol,pointer decay,pointer damp),BOOL
'# endif

declare import, BASS_MusicLoad(BOOL mem,pointer _file, DWORD offset, DWORD length, DWORD flags, DWORD freq),HMUSIC
declare import, BASS_MusicFree(HMUSIC handle),BOOL
declare import, BASS_MusicSetAttribute(HMUSIC handle, DWORD attrib, DWORD value),DWORD
declare import, BASS_MusicGetAttribute(HMUSIC handle, DWORD attrib),DWORD
declare import, BASS_MusicGetName(HMUSIC handle),pointer
declare import, BASS_MusicGetOrders(HMUSIC handle),DWORD
declare import, BASS_MusicGetOrderPosition(HMUSIC handle),DWORD

declare import, BASS_SampleLoad(BOOL mem,pointer _file, DWORD offset, DWORD length, DWORD max, DWORD flags),HSAMPLE
declare import, BASS_SampleCreate(DWORD length, DWORD freq, DWORD chans, DWORD max, DWORD flags),pointer
declare import, BASS_SampleCreateDone(),HSAMPLE
declare import, BASS_SampleFree(HSAMPLE handle),BOOL
declare import, BASS_SampleGetInfo(HSAMPLE handle, pointer info),BOOL
declare import, BASS_SampleSetInfo(HSAMPLE handle, pointer info),BOOL
declare import, BASS_SampleGetChannel(HSAMPLE handle, BOOL onlynew),HCHANNEL
declare import, BASS_SampleStop(HSAMPLE handle),BOOL

declare import, BASS_StreamCreate(DWORD freq, DWORD chans, DWORD flags,pointer proc, DWORD user),HSTREAM
declare import, BASS_StreamCreateFile(BOOL mem,pointer _file, DWORD offset, DWORD length, DWORD flags),HSTREAM
declare import, BASS_StreamCreateURL(pointer url, DWORD offset, DWORD flags,pointer proc, DWORD user),HSTREAM
declare import, BASS_StreamCreateFileUser(BOOL buffered, DWORD flags,pointer proc, DWORD user),HSTREAM
declare import, BASS_StreamFree(HSTREAM handle),BOOL
declare import, BASS_StreamGetTags(HSTREAM handle, DWORD tags),pointer
declare import, BASS_StreamGetFilePosition(HSTREAM handle, DWORD mode),DWORD

declare import, BASS_RecordGetDeviceDescription(DWORD device),pointer
declare import, BASS_RecordInit(int device),BOOL
declare import, BASS_RecordSetDevice(DWORD device),BOOL
declare import, BASS_RecordGetDevice(),DWORD
declare import, BASS_RecordFree(),BOOL
declare import, BASS_RecordGetInfo(pointer info),BOOL
declare import, BASS_RecordGetInputName(int _input),pointer
declare import, BASS_RecordSetInput(int _input, DWORD setting),BOOL
declare import, BASS_RecordGetInput(int _input),DWORD
declare import, BASS_RecordStart(DWORD freq, DWORD chans, DWORD flags,pointer proc, DWORD user),HRECORD

declare import, BASS_ChannelBytes2Seconds(DWORD handle, QWORD pos),float
declare import, BASS_ChannelSeconds2Bytes(DWORD handle, float pos),QWORD
declare import, BASS_ChannelGetDevice(DWORD handle),DWORD
declare import, BASS_ChannelIsActive(DWORD handle),DWORD
declare import, BASS_ChannelGetInfo(DWORD handle, pointer info),BOOL
declare import, BASS_ChannelSetFlags(DWORD handle, DWORD flags),BOOL
declare import, BASS_ChannelPreBuf(DWORD handle, DWORD length),BOOL
declare import, BASS_ChannelPlay(DWORD handle, BOOL restart),BOOL
declare import, BASS_ChannelStop(DWORD handle),BOOL
declare import, BASS_ChannelPause(DWORD handle),BOOL
declare import, BASS_ChannelSetAttributes(DWORD handle, int freq, int volume, int pan),BOOL
declare import, BASS_ChannelGetAttributes(DWORD handle,pointer freq,pointer volume,pointer pan),BOOL
declare import, BASS_ChannelSlideAttributes(DWORD handle, int freq, int volume, int pan, DWORD time),BOOL
declare import, BASS_ChannelIsSliding(DWORD handle),DWORD
declare import, BASS_ChannelSet3DAttributes(DWORD handle, int mode, float min, float max, int iangle, int oangle, int outvol),BOOL
declare import, BASS_ChannelGet3DAttributes(DWORD handle,pointer mode,pointer min,pointer max,pointer iangle,pointer oangle,pointer outvol),BOOL
declare import, BASS_ChannelSet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare import, BASS_ChannelGet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare import, BASS_ChannelGetLength(DWORD handle),QWORD
declare import, BASS_ChannelSetPosition(DWORD handle, QWORD pos),BOOL
declare import, BASS_ChannelGetPosition(DWORD handle),QWORD
declare import, BASS_ChannelGetLevel(DWORD handle),DWORD
declare import, BASS_ChannelGetData(DWORD handle,pointer buffer, DWORD length),DWORD
declare import, BASS_ChannelSetSync(DWORD handle, DWORD _type, QWORD param,pointer proc, DWORD user),HSYNC
declare import, BASS_ChannelRemoveSync(DWORD handle, HSYNC sync),BOOL
declare import, BASS_ChannelSetDSP(DWORD handle,pointer proc, DWORD user, int priority),HDSP
declare import, BASS_ChannelRemoveDSP(DWORD handle, HDSP dsp),BOOL
declare import, BASS_ChannelSetLink(DWORD handle, DWORD chan),BOOL
declare import, BASS_ChannelRemoveLink(DWORD handle, DWORD chan),BOOL
'# ifdef _WIN32
declare import, BASS_ChannelSetEAXMix(DWORD handle, float mix),BOOL
declare import, BASS_ChannelGetEAXMix(DWORD handle,pointer mix),BOOL
declare import, BASS_ChannelSetFX(DWORD handle, DWORD _type, DWORD priority),HFX
declare import, BASS_ChannelRemoveFX(DWORD handle, HFX fx),BOOL

declare import, BASS_FXSetParameters(HFX handle,pointer par),BOOL
declare import, BASS_FXGetParameters(HFX handle,pointer par),BOOL
'# endif

$else
declare* BASS_SetConfig(DWORD option, DWORD value),DWORD
declare* BASS_GetConfig(DWORD option),DWORD
declare* BASS_GetVersion(),DWORD
declare* BASS_GetDeviceDescription(DWORD device),pointer
declare* BASS_ErrorGetCode(),int
declare* BASS_Init(int device, DWORD freq, DWORD flags, HWND win,pointer dsguid),BOOL
declare* BASS_SetDevice(DWORD device),BOOL
declare* BASS_GetDevice(),DWORD
declare* BASS_Free(),BOOL
declare* BASS_GetDSoundObject(DWORD object),pointer
declare* BASS_GetInfo(pointer info),BOOL
declare* BASS_Update(),BOOL
declare* BASS_GetCPU(),float
declare* BASS_Start(),BOOL
declare* BASS_Stop(),BOOL
declare* BASS_Pause(),BOOL
declare* BASS_SetVolume(DWORD volume),BOOL
declare* BASS_GetVolume(),DWORD
declare* BASS_PluginLoad(pointer file),HPLUGIN
declare* BASS_PluginFree(HPLUGIN handle),BOOL
declare* BASS_Set3DFactors(float distf, float rollf, float doppf),BOOL
declare* BASS_Get3DFactors(pointer distf,pointer rollf,pointer doppf),BOOL
declare* BASS_Set3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare* BASS_Get3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare* BASS_Apply3D()
declare* BASS_SetEAXParameters(int env, float vol, float decay, float damp),BOOL
declare* BASS_GetEAXParameters(pointer env,pointer vol,pointer decay,pointer damp),BOOL
declare* BASS_MusicLoad(BOOL mem,pointer file, DWORD offset, DWORD length, DWORD flags, DWORD freq),HMUSIC
declare* BASS_MusicFree(HMUSIC handle),BOOL
declare* BASS_MusicSetAttribute(HMUSIC handle, DWORD attrib, DWORD value),DWORD
declare* BASS_MusicGetAttribute(HMUSIC handle, DWORD attrib),DWORD
declare* BASS_MusicGetName(HMUSIC handle),pointer
declare* BASS_MusicGetOrders(HMUSIC handle),DWORD
declare* BASS_MusicGetOrderPosition(HMUSIC handle),DWORD
declare* BASS_SampleLoad(BOOL mem,pointer file, DWORD offset, DWORD length, DWORD max, DWORD flags),HSAMPLE
declare* BASS_SampleCreate(DWORD length, DWORD freq, DWORD chans, DWORD max, DWORD flags),pointer
declare* BASS_SampleCreateDone(),HSAMPLE
declare* BASS_SampleFree(HSAMPLE handle),BOOL
declare* BASS_SampleGetInfo(HSAMPLE handle, pointer info),BOOL
declare* BASS_SampleSetInfo(HSAMPLE handle, pointer info),BOOL
declare* BASS_SampleGetChannel(HSAMPLE handle, BOOL onlynew),HCHANNEL
declare* BASS_SampleStop(HSAMPLE handle),BOOL
declare* BASS_StreamCreate(DWORD freq, DWORD chans, DWORD flags,pointer proc, DWORD user),HSTREAM
declare* BASS_StreamCreateFile(BOOL mem,pointer file, DWORD offset, DWORD length, DWORD flags),HSTREAM
declare* BASS_StreamCreateURL(pointer url, DWORD offset, DWORD flags,pointer proc, DWORD user),HSTREAM
declare* BASS_StreamCreateFileUser(BOOL buffered, DWORD flags,pointer proc, DWORD user),HSTREAM
declare* BASS_StreamFree(HSTREAM handle),BOOL
declare* BASS_StreamGetTags(HSTREAM handle, DWORD tags),pointer
declare* BASS_StreamGetFilePosition(HSTREAM handle, DWORD mode),DWORD
declare* BASS_RecordGetDeviceDescription(DWORD device),pointer
declare* BASS_RecordInit(int device),BOOL
declare* BASS_RecordSetDevice(DWORD device),BOOL
declare* BASS_RecordGetDevice(),DWORD
declare* BASS_RecordFree(),BOOL
declare* BASS_RecordGetInfo(BASS_RECORDINFO* info),BOOL
declare* BASS_RecordGetInputName(int _input),pointer
declare* BASS_RecordSetInput(int _input, DWORD setting),BOOL
declare* BASS_RecordGetInput(int _input),DWORD
declare* BASS_RecordStart(DWORD freq, DWORD chans, DWORD flags,pointer proc, DWORD user),HRECORD
declare* BASS_ChannelBytes2Seconds(DWORD handle, QWORD pos),float
declare* BASS_ChannelSeconds2Bytes(DWORD handle, float pos),QWORD
declare* BASS_ChannelGetDevice(DWORD handle),DWORD
declare* BASS_ChannelIsActive(DWORD handle),DWORD
declare* BASS_ChannelGetInfo(DWORD handle, pointer info),BOOL
declare* BASS_ChannelSetFlags(DWORD handle, DWORD flags),BOOL
declare* BASS_ChannelPreBuf(DWORD handle, DWORD length),BOOL
declare* BASS_ChannelPlay(DWORD handle, BOOL restart),BOOL
declare* BASS_ChannelStop(DWORD handle),BOOL
declare* BASS_ChannelPause(DWORD handle),BOOL
declare* BASS_ChannelSetAttributes(DWORD handle, int freq, int volume, int pan),BOOL
declare* BASS_ChannelGetAttributes(DWORD handle,pointer freq,pointer volume,pointer pan),BOOL
declare* BASS_ChannelSlideAttributes(DWORD handle, int freq, int volume, int pan, DWORD time),BOOL
declare* BASS_ChannelIsSliding(DWORD handle),DWORD
declare* BASS_ChannelSet3DAttributes(DWORD handle, int mode, float min, float max, int iangle, int oangle, int outvol),BOOL
declare* BASS_ChannelGet3DAttributes(DWORD handle,pointer mode,pointer min,pointer max,pointer iangle,pointer oangle,pointer outvol),BOOL
declare* BASS_ChannelSet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare* BASS_ChannelGet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare* BASS_ChannelGetLength(DWORD handle),QWORD
declare* BASS_ChannelSetPosition(DWORD handle, QWORD pos),BOOL
declare* BASS_ChannelGetPosition(DWORD handle),QWORD
declare* BASS_ChannelGetLevel(DWORD handle),DWORD
declare* BASS_ChannelGetData(DWORD handle,pointer buffer, DWORD length),DWORD
declare* BASS_ChannelSetSync(DWORD handle, DWORD _type, QWORD param,pointer proc, DWORD user),HSYNC
declare* BASS_ChannelRemoveSync(DWORD handle, HSYNC sync),BOOL
declare* BASS_ChannelSetDSP(DWORD handle,pointer proc, DWORD user, int priority),HDSP
declare* BASS_ChannelRemoveDSP(DWORD handle, HDSP dsp),BOOL
declare* BASS_ChannelSetLink(DWORD handle, DWORD chan),BOOL
declare* BASS_ChannelRemoveLink(DWORD handle, DWORD chan),BOOL
declare* BASS_ChannelSetEAXMix(DWORD handle, float mix),BOOL
declare* BASS_ChannelGetEAXMix(DWORD handle,pointer mix),BOOL
declare* BASS_ChannelSetFX(DWORD handle, DWORD _type, DWORD priority),HFX
declare* BASS_ChannelRemoveFX(DWORD handle, HFX fx),BOOL
declare* BASS_FXSetParameters(HFX handle,pointer par),BOOL
declare* BASS_FXGetParameters(HFX handle,pointer par),BOOL
$endif

$endif
