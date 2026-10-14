/*
	BASS 2.4 C/C++ header file
	Copyright(c)1999-2009 Un4seen Developments Ltd.

	See the BASS.CHM file for more detailed documentation
*/

$ifndef __bass_inc__
$define __bass_inc__

$ifndef BASS_NO_LIB
$use "bass.lib" ' dll imports
$endif

$use "custom\\bass24.lib" ' presets
$use "custom\\sdkincludes.lib" ' BASS_ChannelBytes2Seconds wrapper

'$ ifdef _WIN32
$ifndef __windowssdk_inc__
$include "windowssdk.inc"
$endif
typedef QWORD uint64
/*$else
$include "stdint.inc"
$define WINAPI
$define CALLBACK
typedef BYTE uint8_t
typedef WORD uint16_t
typedef DWORD uint32_t
typedef QWORD uint64_t
$ ifndef __OBJC__
typedef BOOL int
$ endif

$define LOBYTE(a)(BYTE)(a)
$define HIBYTE(a)(BYTE)((a)>>8)
$define LOWORD(a)(WORD)(a)
$define HIWORD(a)(WORD)((a)>>16)
$define MAKEWORD(a,b)(WORD)(((a)&0xff)|((b)<<8))
$define MAKELONG(a,b)(DWORD)(((a)&0xffff)|((b)<<16))
$ endif*/

$define BASSVERSION			0x204	' API version
$define BASSVERSIONTEXT		"2.4"

/*$ ifndef BASSDEF
$define BASSDEF(f)WINAPI f
$ endif*/

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
$define BASS_ERROR_POSITION	7	' invalid position
$define BASS_ERROR_INIT		8	' BASS_Init has not been successfully called
$define BASS_ERROR_START	9	' BASS_Start has not been successfully called
$define BASS_ERROR_ALREADY	14	' already initialized/paused/whatever
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
$define BASS_ERROR_NOTAVAIL	37	' requested data is not available
$define BASS_ERROR_DECODE	38	' the channel is a "decoding channel"
$define BASS_ERROR_DX		39	' a sufficient DirectX version is not installed
$define BASS_ERROR_TIMEOUT	40	' connection timedout
$define BASS_ERROR_FILEFORM	41	' unsupported file format
$define BASS_ERROR_SPEAKER	42	' unavailable speaker
$define BASS_ERROR_VERSION	43	' invalid BASS version(used by add-ons)
$define BASS_ERROR_CODEC	44	' codec is not available/supported
$define BASS_ERROR_ENDED	45	' the channel/file has ended
$define BASS_ERROR_UNKNOWN	-1	' some other mystery problem

' BASS_SetConfig options
$define BASS_CONFIG_BUFFER			0
$define BASS_CONFIG_UPDATEPERIOD	1
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
$define BASS_CONFIG_NET_PREBUF		15
$define BASS_CONFIG_NET_PASSIVE		18
$define BASS_CONFIG_REC_BUFFER		19
$define BASS_CONFIG_NET_PLAYLIST	21
$define BASS_CONFIG_MUSIC_VIRTUAL	22
$define BASS_CONFIG_VERIFY			23
$define BASS_CONFIG_UPDATETHREADS	24

' BASS_SetConfigPtr options
$define BASS_CONFIG_NET_AGENT		16
$define BASS_CONFIG_NET_PROXY		17

' Initialization flags
$define BASS_DEVICE_8BITS		1	' use 8 bit resolution, else 16 bit
$define BASS_DEVICE_MONO		2	' use mono, else stereo
$define BASS_DEVICE_3D			4	' enable 3D functionality
$define BASS_DEVICE_LATENCY		256	' calculate device latency(BASS_INFO struct)
$define BASS_DEVICE_CPSPEAKERS	1024 ' detect speakers via Windows control panel
$define BASS_DEVICE_SPEAKERS	2048 ' force enabling of speaker assignment
$define BASS_DEVICE_NOSPEAKER	4096 ' ignore speaker arrangement

' DirectSound interfaces(for use with BASS_GetDSoundObject)
$define BASS_OBJECT_DS		1	' IDirectSound
$define BASS_OBJECT_DS3DL	2	' IDirectSound3DListener

' Device info structure
type BASS_DEVICEINFO
	pointer name	' description
	pointer driver	' driver
	DWORD flags
endtype

' BASS_DEVICEINFO flags
$define BASS_DEVICE_ENABLED		1
$define BASS_DEVICE_DEFAULT		2
$define BASS_DEVICE_INIT		4

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
	DWORD initflags' BASS_Init "flags" parameter
	DWORD speakers ' number of speakers available
	DWORD freq		' current output rate(Vista/OSX only)
endtype

' BASS_INFO flags(from DSOUND.H)
$define DSCAPS_CONTINUOUSRATE	0x00000010	' supports all sample rates between min/maxrate
$define DSCAPS_EMULDRIVER		0x00000020	' device does NOT have hardware DirectSound support
$define DSCAPS_CERTIFIED		0x00000040	' device driver has been certified by Microsoft
$define DSCAPS_SECONDARYMONO	0x00000100	' mono
$define DSCAPS_SECONDARYSTEREO	0x00000200	' stereo
$define DSCAPS_SECONDARY8BIT	0x00000400	' 8 bit
$define DSCAPS_SECONDARY16BIT	0x00000800	' 16 bit

' Recording device info structure
type BASS_RECORDINFO
	DWORD flags	' device capabilities(DSCCAPS_xxx flags)
	DWORD formats	' supported standard formats(WAVE_FORMAT_xxx flags)
	DWORD inputs	' number of inputs
	BOOL singlein	' TRUE = only 1 input can be set at a time
	DWORD freq		' current input rate(Vista/OSX only)
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

' Sample info structure
type BASS_SAMPLE
	DWORD freq		' default playback rate
	float volume	' default volume(0-1)
	float pan		' default pan(-1=left, 0=middle, 1=right)
	DWORD flags	' BASS_SAMPLE_xxx flags
	DWORD length	' length(in bytes)
	DWORD max		' maximum simultaneous playbacks
	DWORD origres	' original resolution bits
	DWORD chans	' number of channels
	DWORD mingap	' minimum gap(ms)between creating channels
	DWORD mode3d	' BASS_3DMODE_xxx mode
	float mindist	' minimum distance
	float maxdist	' maximum distance
	DWORD iangle	' angle of inside projection cone
	DWORD oangle	' angle of outside projection cone
	float outvol	' delta-volume outside the projection cone
	DWORD vam		' voice allocation/management flags(BASS_VAM_xxx)
	DWORD priority	' priority(0=lowest, 0xffffffff=highest)
endtype

$define BASS_SAMPLE_8BITS		1	' 8 bit
$define BASS_SAMPLE_FLOAT		256	' 32-bit floating-point
$define BASS_SAMPLE_MONO		2	' mono
$define BASS_SAMPLE_LOOP		4	' looped
$define BASS_SAMPLE_3D			8	' 3D functionality
$define BASS_SAMPLE_SOFTWARE	16	' not using hardware mixing
$define BASS_SAMPLE_MUTEMAX		32	' mute at max distance(3D only)
$define BASS_SAMPLE_VAM			64	' DX7 voice allocation & management
$define BASS_SAMPLE_FX			128	' old implementation of DX8 effects
$define BASS_SAMPLE_OVER_VOL	0x10000	' override lowest volume
$define BASS_SAMPLE_OVER_POS	0x20000	' override longest playing
$define BASS_SAMPLE_OVER_DIST	0x30000 ' override furthest from listener(3D only)

$define BASS_STREAM_PRESCAN		0x20000 ' enable pin-point seeking/length(MP3/MP2/MP1)
$define BASS_MP3_SETPOS			BASS_STREAM_PRESCAN
$define BASS_STREAM_AUTOFREE	0x40000	' automatically free the stream when it stop/ends
$define BASS_STREAM_RESTRATE	0x80000	' restrict the download rate of internet file streams
$define BASS_STREAM_BLOCK		0x100000 ' download/play internet file stream in small blocks
$define BASS_STREAM_DECODE		0x200000 ' don't play the stream, only decode(BASS_ChannelGetData)
$define BASS_STREAM_STATUS		0x800000 ' give server status info(HTTP/ICY tags)in DOWNLOADPROC

$define BASS_MUSIC_FLOAT		BASS_SAMPLE_FLOAT
$define BASS_MUSIC_MONO			BASS_SAMPLE_MONO
$define BASS_MUSIC_LOOP			BASS_SAMPLE_LOOP
$define BASS_MUSIC_3D			BASS_SAMPLE_3D
$define BASS_MUSIC_FX			BASS_SAMPLE_FX
$define BASS_MUSIC_AUTOFREE		BASS_STREAM_AUTOFREE
$define BASS_MUSIC_DECODE		BASS_STREAM_DECODE
$define BASS_MUSIC_PRESCAN		BASS_STREAM_PRESCAN	' calculate playback length
$define BASS_MUSIC_CALCLEN		BASS_MUSIC_PRESCAN
$define BASS_MUSIC_RAMP			0x200	' normal ramping
$define BASS_MUSIC_RAMPS		0x400	' sensitive ramping
$define BASS_MUSIC_SURROUND		0x800	' surround sound
$define BASS_MUSIC_SURROUND2	0x1000	' surround sound(mode 2)
$define BASS_MUSIC_FT2MOD		0x2000	' play .MOD as FastTracker 2 does
$define BASS_MUSIC_PT1MOD		0x4000	' play .MOD as ProTracker 1 does
$define BASS_MUSIC_NONINTER		0x10000	' non-interpolated sample mixing
$define BASS_MUSIC_SINCINTER	0x800000 ' sinc interpolated sample mixing
$define BASS_MUSIC_POSRESET		0x8000	' stop all notes when moving position
$define BASS_MUSIC_POSRESETEX	0x400000 ' stop all notes and reset bmp/etc when moving position
$define BASS_MUSIC_STOPBACK		0x80000	' stop the music on a backwards jump effect
$define BASS_MUSIC_NOSAMPLE		0x100000 ' don't load the samples

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

' DX7 voice allocation & management flags
$define BASS_VAM_HARDWARE		1
$define BASS_VAM_SOFTWARE		2
$define BASS_VAM_TERM_TIME		4
$define BASS_VAM_TERM_DIST		8
$define BASS_VAM_TERM_PRIO		16

' Channel info structure
type BASS_CHANNELINFO
	DWORD freq		' default playback rate
	DWORD chans	' channels
	DWORD flags	' BASS_SAMPLE/STREAM/MUSIC/SPEAKER flags
	DWORD ctype	' type of channel
	DWORD origres	' original resolution
	HPLUGIN plugin	' plugin
	HSAMPLE sample ' sample
	pointer filename ' filename
endtype

' BASS_CHANNELINFO types
$define BASS_CTYPE_SAMPLE		1
$define BASS_CTYPE_RECORD		2
$define BASS_CTYPE_STREAM		0x10000
$define BASS_CTYPE_STREAM_OGG	0x10002
$define BASS_CTYPE_STREAM_MP1	0x10003
$define BASS_CTYPE_STREAM_MP2	0x10004
$define BASS_CTYPE_STREAM_MP3	0x10005
$define BASS_CTYPE_STREAM_AIFF	0x10006
$define BASS_CTYPE_STREAM_CA	0x10007
$define BASS_CTYPE_STREAM_WAV	0x40000 ' WAVE flag, LOWORD=codec
$define BASS_CTYPE_STREAM_WAV_PCM	0x50001
$define BASS_CTYPE_STREAM_WAV_FLOAT	0x50003
$define BASS_CTYPE_MUSIC_MOD	0x20000
$define BASS_CTYPE_MUSIC_MTM	0x20001
$define BASS_CTYPE_MUSIC_S3M	0x20002
$define BASS_CTYPE_MUSIC_XM		0x20003
$define BASS_CTYPE_MUSIC_IT		0x20004
$define BASS_CTYPE_MUSIC_MO3	0x00100 ' MO3 flag

type BASS_PLUGINFORM
	DWORD ctype		' channel type
	pointer name	' format description
	pointer exts	' file extension filter(*.ext1*.ext2etc...)
endtype

type BASS_PLUGININFO
	DWORD version					' version(same form as BASS_GetVersion)
	DWORD formatc					' number of formats
	pointer formats	' the array of formats
endtype

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
$define BASS_3DMODE_NORMAL		0	' normal 3D processing
$define BASS_3DMODE_RELATIVE	1	' position is relative to the listener
$define BASS_3DMODE_OFF			2	' no 3D processing

' software 3D mixing algorithms(used with BASS_CONFIG_3DALGORITHM)
$define BASS_3DALG_DEFAULT	0
$define BASS_3DALG_OFF		1
$define BASS_3DALG_FULL		2
$define BASS_3DALG_LIGHT	3

' EAX environments, use with BASS_SetEAXParameters
enum EAX_ENVIRONMENT
	EAX_ENVIRONMENT_GENERIC
	EAX_ENVIRONMENT_PADDEDCELL
	EAX_ENVIRONMENT_ROOM
	EAX_ENVIRONMENT_BATHROOM
	EAX_ENVIRONMENT_LIVINGROOM
	EAX_ENVIRONMENT_STONEROOM
	EAX_ENVIRONMENT_AUDITORIUM
	EAX_ENVIRONMENT_CONCERTHALL
	EAX_ENVIRONMENT_CAVE
	EAX_ENVIRONMENT_ARENA
	EAX_ENVIRONMENT_HANGAR
	EAX_ENVIRONMENT_CARPETEDHALLWAY
	EAX_ENVIRONMENT_HALLWAY
	EAX_ENVIRONMENT_STONECORRIDOR
	EAX_ENVIRONMENT_ALLEY
	EAX_ENVIRONMENT_FOREST
	EAX_ENVIRONMENT_CITY
	EAX_ENVIRONMENT_MOUNTAINS
	EAX_ENVIRONMENT_QUARRY
	EAX_ENVIRONMENT_PLAIN
	EAX_ENVIRONMENT_PARKINGLOT
	EAX_ENVIRONMENT_SEWERPIPE
	EAX_ENVIRONMENT_UNDERWATER
	EAX_ENVIRONMENT_DRUGGED
	EAX_ENVIRONMENT_DIZZY
	EAX_ENVIRONMENT_PSYCHOTIC

	EAX_ENVIRONMENT_COUNT			' total number of environments
endenum

declare import, BASS_SetEAXPreset alias BASS_SetEAXParameters(GUID g byval),BOOL
/* EAX presets, usage: BASS_SetEAXParameters(EAX_PRESET_xxx)
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

typedef STREAMPROC int'DWORD(CALLBACK STREAMPROC)(HSTREAM handle, pointer buffer, DWORD length, pointer user)
/* User stream callback function. NOTE: A stream function should obviously be as quick
as possible, other streams(and MOD musics)can't be mixed until it's finished.
handle : The stream that needs writing
buffer : Buffer to write the samples in
length : Number of bytes to write
user	: The 'user' parameter value given when calling BASS_StreamCreate
RETURN : Number of bytes written. Set the BASS_STREAMPROC_END flag to end
		the stream. */

$define BASS_STREAMPROC_END		0x80000000	' end of user stream flag

' special STREAMPROCs
$define STREAMPROC_DUMMY		0		' "dummy" stream
$define STREAMPROC_PUSH			-1		' push stream

' BASS_StreamCreateFileUser file systems
$define STREAMFILE_NOBUFFER		0
$define STREAMFILE_BUFFER		1
$define STREAMFILE_BUFFERPUSH	2

' User file stream callback functions
typedef FILECLOSEPROC int'(CALLBACK FILECLOSEPROC)(pointer user)
typedef FILELENPROC int'(CALLBACK FILELENPROC)(pointer user),QWORD
typedef FILEREADPROC int'(CALLBACK FILEREADPROC)(pointer buffer, DWORD length, pointer user),DWORD
typedef FILESEEKPROC int'(CALLBACK FILESEEKPROC)(QWORD offset, pointer user),BOOL

type BASS_FILEPROCS
	FILECLOSEPROC close
	FILELENPROC length
	FILEREADPROC _read
	FILESEEKPROC _seek
endtype

' BASS_StreamPutFileData options
$define BASS_FILEDATA_END		0	' end & close the file

' BASS_StreamGetFilePosition modes
$define BASS_FILEPOS_CURRENT	0
$define BASS_FILEPOS_DECODE		BASS_FILEPOS_CURRENT
$define BASS_FILEPOS_DOWNLOAD	1
$define BASS_FILEPOS_END		2
$define BASS_FILEPOS_START		3
$define BASS_FILEPOS_CONNECTED	4
$define BASS_FILEPOS_BUFFER		5
$define BASS_FILEPOS_SOCKET		6

typedef DOWNLOADPROC int'void(CALLBACK DOWNLOADPROC(pointer buffer, DWORD length, pointer user)
/* Internet stream download callback function.
buffer : Buffer containing the downloaded data... NULL=end of download
length : Number of bytes in the buffer
user	: The 'user' parameter value given when calling BASS_StreamCreateURL */

' BASS_ChannelSetSync types
$define BASS_SYNC_POS			0
$define BASS_SYNC_END			2
$define BASS_SYNC_META			4
$define BASS_SYNC_SLIDE			5
$define BASS_SYNC_STALL			6
$define BASS_SYNC_DOWNLOAD		7
$define BASS_SYNC_FREE			8
$define BASS_SYNC_SETPOS		11
$define BASS_SYNC_MUSICPOS		10
$define BASS_SYNC_MUSICINST		1
$define BASS_SYNC_MUSICFX		3
$define BASS_SYNC_OGG_CHANGE	12
$define BASS_SYNC_MIXTIME		0x40000000	' FLAG: sync at mixtime, else at playtime
$define BASS_SYNC_ONETIME		0x80000000	' FLAG: sync only once, else continuously

typedef SYNCPROC int'void(CALLBACK SYNCPROC(HSYNC handle, DWORD channel, DWORD _data, pointer user)
/* Sync callback function. NOTE: a sync callback function should be very
quick as other syncs can't be processed until it has finished. If the sync
is a "mixtime" sync, then other streams and MOD musics can't be mixed until
it's finished either.
handle : The sync that has occured
channel: Channel that the sync occured in
data	: Additional data associated with the sync's occurance
user	: The 'user' parameter given when calling BASS_ChannelSetSync */

typedef DSPPROC int'void(CALLBACK DSPPROC(HDSP handle, DWORD channel, pointer buffer, DWORD length, pointer user)
/* DSP callback function. NOTE: A DSP function should obviously be as quick as
possible... other DSP functions, streams and MOD musics can not be processed
until it's finished.
handle : The DSP handle
channel: Channel that the DSP is being applied to
buffer : Buffer to apply the DSP to
length : Number of bytes in the buffer
user	: The 'user' parameter given when calling BASS_ChannelSetDSP */

typedef RECORDPROC int'BOOL(CALLBACK RECORDPROC(HRECORD handle, pointer buffer, DWORD length, pointer user)
/* Recording callback function.
handle : The recording handle
buffer : Buffer containing the recorded sample data
length : Number of bytes
user	: The 'user' parameter value given when calling BASS_RecordStart
RETURN : TRUE = continue recording, FALSE = stop */

' BASS_ChannelIsActive return values
$define BASS_ACTIVE_STOPPED	0
$define BASS_ACTIVE_PLAYING	1
$define BASS_ACTIVE_STALLED	2
$define BASS_ACTIVE_PAUSED	3

' Channel attributes
$define BASS_ATTRIB_FREQ			1
$define BASS_ATTRIB_VOL				2
$define BASS_ATTRIB_PAN				3
$define BASS_ATTRIB_EAXMIX			4
$define BASS_ATTRIB_MUSIC_AMPLIFY	0x100
$define BASS_ATTRIB_MUSIC_PANSEP	0x101
$define BASS_ATTRIB_MUSIC_PSCALER	0x102
$define BASS_ATTRIB_MUSIC_BPM		0x103
$define BASS_ATTRIB_MUSIC_SPEED		0x104
$define BASS_ATTRIB_MUSIC_VOL_GLOBAL 0x105
$define BASS_ATTRIB_MUSIC_VOL_CHAN	0x200 ' + channel $
$define BASS_ATTRIB_MUSIC_VOL_INST	0x300 ' + instrument $

' BASS_ChannelGetData flags
$define BASS_DATA_AVAILABLE	0			' query how much data is buffered
$define BASS_DATA_FLOAT		0x40000000	' flag: return floating-point sample data
$define BASS_DATA_FFT256	0x80000000	' 256 sample FFT
$define BASS_DATA_FFT512	0x80000001	' 512 FFT
$define BASS_DATA_FFT1024	0x80000002	' 1024 FFT
$define BASS_DATA_FFT2048	0x80000003	' 2048 FFT
$define BASS_DATA_FFT4096	0x80000004	' 4096 FFT
$define BASS_DATA_FFT8192	0x80000005	' 8192 FFT
$define BASS_DATA_FFT_INDIVIDUAL 0x10	' FFT flag: FFT for each channel, else all combined
$define BASS_DATA_FFT_NOWINDOW	0x20	' FFT flag: no Hanning window

' BASS_ChannelGetTags types : what's returned
$define BASS_TAG_ID3		0	' ID3v1 tags : TAG_ID3 structure
$define BASS_TAG_ID3V2		1	' ID3v2 tags : variable length block
$define BASS_TAG_OGG		2	' OGG comments : series of null-terminated UTF-8 strings
$define BASS_TAG_HTTP		3	' HTTP headers : series of null-terminated ANSI strings
$define BASS_TAG_ICY		4	' ICY headers : series of null-terminated ANSI strings
$define BASS_TAG_META		5	' ICY metadata : ANSI string
$define BASS_TAG_VENDOR		9	' OGG encoder : UTF-8 string
$define BASS_TAG_LYRICS3	10	' Lyric3v2 tag : ASCII string
$define BASS_TAG_CA_CODEC	11	' CoreAudio codec info : TAG_CA_CODEC structure
$define BASS_TAG_RIFF_INFO	0x100 ' RIFF "INFO" tags : series of null-terminated ANSI strings
$define BASS_TAG_RIFF_BEXT	0x101 ' RIFF/BWF Broadcast Audio Extension tags : TAG_BEXT structure
$define BASS_TAG_MUSIC_NAME		0x10000	' MOD music name : ANSI string
$define BASS_TAG_MUSIC_MESSAGE	0x10001	' MOD message : ANSI string
$define BASS_TAG_MUSIC_ORDERS	0x10002	' MOD order list : BYTE array of pattern numbers
$define BASS_TAG_MUSIC_INST		0x10100	' + instrument $, MOD instrument name : ANSI string
$define BASS_TAG_MUSIC_SAMPLE	0x10300	' + sample $, MOD sample name : ANSI string

' ID3v1 tag structure
type TAG_ID3
	istring id[3]
	istring title[30]
	istring artist[30]
	istring album[30]
	istring year[4]
	istring comment[30]
	BYTE genre
endtype

' BWF Broadcast Audio Extension tag structure
'$ifdef _MSC_VER
'$pragma warning(push)
'$pragma warning(disable:4200)
'$endif
'$pragma pack(push,1)
type TAG_BEXT,1
	istring Description[256]			' description
	istring Originator[32]			' name of the originator
	istring OriginatorReference[32]	' reference of the originator
	istring OriginationDate[10]		' date of creation(yyyy-mm-dd)
	istring OriginationTime[8]		' time of creation(hh-mm-ss)
	QWORD TimeReference			' first sample count since midnight(little-endian)
	WORD Version					' BWF version(little-endian)
	BYTE UMID[64]					' SMPTE UMID
	BYTE Reserved[190]
'$if defined(__GNUC__)&& __GNUC__<3
'	char CodingHistory[0]			' history
'$elif 1 ' change to 0 if compiler fails the following line
'	char CodingHistory[]			' history
'$else
'	char CodingHistory[1]			' history
'$endif
endtype
'$pragma pack(pop)
'$ifdef _MSC_VER
'$pragma warning(pop)
'$endif

' CoreAudio codec info structure
type TAG_CA_CODEC
	DWORD ftype					' file format
	DWORD atype					' audio format
	pointer name				' description
endtype

' BASS_ChannelGetLength/GetPosition/SetPosition modes
$define BASS_POS_BYTE			0		' byte position
$define BASS_POS_MUSIC_ORDER	1		' order.row position, MAKELONG(order,row)
$define BASS_POS_DECODE			0x10000000 ' flag: get the decoding(not playing)position

' BASS_RecordSetInput flags
$define BASS_INPUT_OFF		0x10000
$define BASS_INPUT_ON		0x20000

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

' DX8 effect types, use with BASS_ChannelSetFX
enum BASS_FX_DX8
	BASS_FX_DX8_CHORUS=0
	BASS_FX_DX8_COMPRESSOR
	BASS_FX_DX8_DISTORTION
	BASS_FX_DX8_ECHO
	BASS_FX_DX8_FLANGER
	BASS_FX_DX8_GARGLE
	BASS_FX_DX8_I3DL2REVERB
	BASS_FX_DX8_PARAMEQ
	BASS_FX_DX8_REVERB
endenum

type BASS_DX8_CHORUS
	float	fWetDryMix
	float	fDepth
	float	fFeedback
	float	fFrequency
	DWORD	lWaveform	' 0=triangle, 1=sine
	float	fDelay
	DWORD	lPhase		' BASS_DX8_PHASE_xxx
endtype

type BASS_DX8_COMPRESSOR
	float	fGain
	float	fAttack
	float	fRelease
	float	fThreshold
	float	fRatio
	float	fPredelay
endtype

type BASS_DX8_DISTORTION
	float	fGain
	float	fEdge
	float	fPostEQCenterFrequency
	float	fPostEQBandwidth
	float	fPreLowpassCutoff
endtype

type BASS_DX8_ECHO
	float	fWetDryMix
	float	fFeedback
	float	fLeftDelay
	float	fRightDelay
	BOOL	lPanDelay
endtype

type BASS_DX8_FLANGER
	float	fWetDryMix
	float	fDepth
	float	fFeedback
	float	fFrequency
	DWORD	lWaveform	' 0=triangle, 1=sine
	float	fDelay
	DWORD	lPhase		' BASS_DX8_PHASE_xxx
endtype

type BASS_DX8_GARGLE
	DWORD	dwRateHz	' Rate of modulation in hz
	DWORD	dwWaveShape	' 0=triangle, 1=square
endtype

type BASS_DX8_I3DL2REVERB
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
endtype

type BASS_DX8_PARAMEQ
	float	fCenter
	float	fBandwidth
	float	fGain
endtype

type BASS_DX8_REVERB
	float	fInGain	' [-96.0,0.0]	default: 0.0 dB
	float	fReverbMix	' [-96.0,0.0]	default: 0.0 db
	float	fReverbTime	' [0.001,3000.0]	default: 1000.0 ms
	float	fHighFreqRTRatio	' [0.001,0.999]	default: 0.001
endtype

$define BASS_DX8_PHASE_NEG_180	0
$define BASS_DX8_PHASE_NEG_90	1
$define BASS_DX8_PHASE_ZERO	2
$define BASS_DX8_PHASE_90	3
$define BASS_DX8_PHASE_180	4

declare import, BASS_SetConfig(DWORD option, DWORD value),BOOL
declare import, BASS_GetConfig(DWORD option),DWORD
declare import, BASS_SetConfigPtr(DWORD option, pointer value),BOOL
declare import, BASS_GetConfigPtr(DWORD option),pointer
declare import, BASS_GetVersion(),DWORD
declare import, BASS_ErrorGetCode(),int
declare import, BASS_GetDeviceInfo(DWORD device, pointer info),BOOL
'$if defined(_WIN32)
declare import, BASS_Init(int device, DWORD freq, DWORD flags, HWND win, pointer dsguid),BOOL
'$else
'declare import, BASS_Init(int device, DWORD freq, DWORD flags, pointer win, pointer dsguid),BOOL
'$endif
declare import, BASS_SetDevice(DWORD device),BOOL
declare import, BASS_GetDevice(),DWORD
declare import, BASS_Free(),BOOL
'$ifdef _WIN32
declare import, BASS_GetDSoundObject(DWORD object),comref
'$endif
declare import, BASS_GetInfo(pointer info),BOOL
declare import, BASS_Update(DWORD length),BOOL
declare extern BASS_GetCPU alias _BASS_GetCPU(),float
declare import, BASS_Start(),BOOL
declare import, BASS_Stop(),BOOL
declare import, BASS_Pause(),BOOL
declare import, BASS_SetVolume(float volume),BOOL
declare extern BASS_GetVolume alias _BASS_GetVolume(),float

declare import, BASS_PluginLoad(pointer _file, DWORD flags),HPLUGIN
declare import, BASS_PluginFree(HPLUGIN handle),BOOL
declare import, BASS_PluginGetInfo(HPLUGIN handle),pointer

declare import, BASS_Set3DFactors(float distf, float rollf, float doppf),BOOL
declare import, BASS_Get3DFactors(pointer distf, pointer rollf, pointer doppf),BOOL
declare import, BASS_Set3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare import, BASS_Get3DPosition(pointer pos, pointer vel, pointer front, pointer top),BOOL
declare import, BASS_Apply3D()
'$ifdef _WIN32
declare import, BASS_SetEAXParameters(int env, float vol, float decay, float damp),BOOL
declare import, BASS_GetEAXParameters(pointer env, pointer vol, pointer decay, pointer damp),BOOL
'$endif

declare import, BASS_MusicLoad(BOOL mem, pointer _file, QWORD offset, DWORD length, DWORD flags, DWORD freq),HMUSIC
declare import, BASS_MusicFree(HMUSIC handle),BOOL

declare import, BASS_SampleLoad(BOOL mem, pointer _file, QWORD offset, DWORD length, DWORD max, DWORD flags),HSAMPLE
declare import, BASS_SampleCreate(DWORD length, DWORD freq, DWORD chans, DWORD max, DWORD flags),HSAMPLE
declare import, BASS_SampleFree(HSAMPLE handle),BOOL
declare import, BASS_SampleSetData(HSAMPLE handle, pointer buffer),BOOL
declare import, BASS_SampleGetData(HSAMPLE handle, pointer buffer),BOOL
declare import, BASS_SampleGetInfo(HSAMPLE handle, pointer info),BOOL
declare import, BASS_SampleSetInfo(HSAMPLE handle, pointer info),BOOL
declare import, BASS_SampleGetChannel(HSAMPLE handle, BOOL onlynew),HCHANNEL
declare import, BASS_SampleGetChannels(HSAMPLE handle, pointer channels),DWORD
declare import, BASS_SampleStop(HSAMPLE handle),BOOL

declare import, BASS_StreamCreate(DWORD freq, DWORD chans, DWORD flags, pointer proc, pointer user),HSTREAM
declare import, BASS_StreamCreateFile(BOOL mem, pointer _file, QWORD offset, QWORD length, DWORD flags),HSTREAM
declare import, BASS_StreamCreateURL(pointer url, DWORD offset, DWORD flags, DOWNLOADPROC proc, pointer user),HSTREAM
declare import, BASS_StreamCreateFileUser(DWORD _system, DWORD flags, BASS_FILEPROCS proc, pointer user),HSTREAM
declare import, BASS_StreamFree(HSTREAM handle),BOOL
declare import, BASS_StreamGetFilePosition(HSTREAM handle, DWORD mode),QWORD
declare import, BASS_StreamPutData(HSTREAM handle, pointer buffer, DWORD length),DWORD
declare import, BASS_StreamPutFileData(HSTREAM handle, pointer buffer, DWORD length),DWORD

declare import, BASS_RecordGetDeviceInfo(DWORD device, pointer info),BOOL
declare import, BASS_RecordInit(int device),BOOL
declare import, BASS_RecordSetDevice(DWORD device),BOOL
declare import, BASS_RecordGetDevice(),DWORD
declare import, BASS_RecordFree(),BOOL
declare import, BASS_RecordGetInfo(pointer info),BOOL
declare import, BASS_RecordGetInputName(int _input),string
declare import, BASS_RecordSetInput(int _input, DWORD flags, float volume),BOOL
declare import, BASS_RecordGetInput(int _input, pointer volume),DWORD
declare import, BASS_RecordStart(DWORD freq, DWORD chans, DWORD flags, RECORDPROC proc, pointer user),HRECORD

' this wrapper handles the double returned in FPU register
declare extern BASS_ChannelBytes2Seconds alias _BASS_ChannelBytes2Seconds(DWORD handle, QWORD pos),double
declare import, BASS_ChannelSeconds2Bytes(DWORD handle, double pos),QWORD
declare import, BASS_ChannelGetDevice(DWORD handle),DWORD
declare import, BASS_ChannelSetDevice(DWORD handle, DWORD device),BOOL
declare import, BASS_ChannelIsActive(DWORD handle),DWORD
declare import, BASS_ChannelGetInfo(DWORD handle, pointer info),BOOL
declare import, BASS_ChannelGetTags(DWORD handle, DWORD tags),string
declare import, BASS_ChannelFlags(DWORD handle, DWORD flags, DWORD mask),DWORD
declare import, BASS_ChannelUpdate(DWORD handle, DWORD length),BOOL
declare import, BASS_ChannelLock(DWORD handle, BOOL lock),BOOL
declare import, BASS_ChannelPlay(DWORD handle, BOOL restart),BOOL
declare import, BASS_ChannelStop(DWORD handle),BOOL
declare import, BASS_ChannelPause(DWORD handle),BOOL
declare import, BASS_ChannelSetAttribute(DWORD handle, DWORD attrib, float value),BOOL
declare import, BASS_ChannelGetAttribute(DWORD handle, DWORD attrib, pointer value),BOOL
declare import, BASS_ChannelSlideAttribute(DWORD handle, DWORD attrib, float value, DWORD time),BOOL
declare import, BASS_ChannelIsSliding(DWORD handle, DWORD attrib),BOOL
declare import, BASS_ChannelSet3DAttributes(DWORD handle, int mode, float min, float max, int iangle, int oangle, float outvol),BOOL
declare import, BASS_ChannelGet3DAttributes(DWORD handle, pointer mode, pointer min, pointer max, pointer iangle, pointer oangle, pointer outvol),BOOL
declare import, BASS_ChannelSet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare import, BASS_ChannelGet3DPosition(DWORD handle, pointer pos, pointer orient, pointer vel),BOOL
declare import, BASS_ChannelGetLength(DWORD handle, DWORD mode),QWORD
declare import, BASS_ChannelSetPosition(DWORD handle, QWORD pos, DWORD mode),BOOL
declare import, BASS_ChannelGetPosition(DWORD handle, DWORD mode),QWORD
declare import, BASS_ChannelGetLevel(DWORD handle),DWORD
declare import, BASS_ChannelGetData(DWORD handle, pointer buffer, DWORD length),DWORD
declare import, BASS_ChannelSetSync(DWORD handle, DWORD _type, QWORD param, SYNCPROC proc, pointer user),HSYNC
declare import, BASS_ChannelRemoveSync(DWORD handle, HSYNC sync),BOOL
declare import, BASS_ChannelSetDSP(DWORD handle, DSPPROC proc, pointer user, int priority),HDSP
declare import, BASS_ChannelRemoveDSP(DWORD handle, HDSP dsp),BOOL
declare import, BASS_ChannelSetLink(DWORD handle, DWORD chan),BOOL
declare import, BASS_ChannelRemoveLink(DWORD handle, DWORD chan),BOOL
declare import, BASS_ChannelSetFX(DWORD handle, DWORD _type, int priority),HFX
declare import, BASS_ChannelRemoveFX(DWORD handle, HFX fx),BOOL

declare import, BASS_FXSetParameters(HFX handle, pointer params),BOOL
declare import, BASS_FXGetParameters(HFX handle, pointer params),BOOL
declare import, BASS_FXReset(HFX handle),BOOL

$endif
