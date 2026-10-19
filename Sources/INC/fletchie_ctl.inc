'Auto Generated on the (ISO Date UTC): 2004-07-26 21:39:20

$use "ctl.lib"

'----------------------------------------------------------------------------------------------------

'---- c:\FletchieIBPro\Subs\@BigStrType.iba -------------------------------------------------------------------------
type BigStr
	def First:pointer
	def Last:pointer
	def StrLen:int
endtype

'---- c:\FletchieIBPro\Subs\@DynaType.iba ---------------------------------------------------------------------------
type DynaStore
	def heaphnd:int
	def ind:pointer
	def LastItem:int
	def inc:int
	def CurSize:int
endtype

'---- c:\FletchieIBPro\Subs\@xfiletype.iba --------------------------------------------------------------------------
type xfile
	def fh:int
	def buffer:int
	def buffersize:int
	def textactual:int
	def cp:int
	def term[4]:istring
endtype


'---- c:\FletchieIBPro\Subs\ActivatedWindow.iba ---------------------------------------------------------------------
declare extern ActivatedWindow(wt:string),int

'---- c:\FletchieIBPro\Subs\AlreadyRunning.iba ----------------------------------------------------------------------
declare extern AlreadyRunning(uniqueid:string),int

'---- c:\FletchieIBPro\Subs\AppendTextFile.iba ----------------------------------------------------------------------
declare extern AppendTextFile(fv:file,fn:string),int

'---- c:\FletchieIBPro\Subs\BigStr.iba ------------------------------------------------------------------------------
declare extern BigStrMake(bs:BigStr),pointer
declare extern BigStrReset(bs:BigStr)
declare extern BigStrAdd(bs:BigStr,str:string)

'---- c:\FletchieIBPro\Subs\BrowseFolder.iba ------------------------------------------------------------------------
declare extern BrowseFolder(win:int,wintitle:string,text:string,buf:string,startfolder:string,openfolder:string,showfiles:int),int

'---- c:\FletchieIBPro\Subs\ChangeFileReadOnly.iba ------------------------------------------------------------------
declare extern ChangeFileReadOnly(fn:string,fl:int)

'---- c:\FletchieIBPro\Subs\conCBLoadFonts.iba ----------------------------------------------------------------------
declare extern conCBLoadFonts(win:window,cid:int,justtruetype:int)

'---- c:\FletchieIBPro\Subs\conClientEdge.iba -----------------------------------------------------------------------
declare extern conClientEdge(par:window,cid:int,fl:int)

'---- c:\FletchieIBPro\Subs\conDraw.iba -----------------------------------------------------------------------------
declare extern conDrawOn(par:window,cid:int)
declare extern conDrawOff(par:window,cid:int)
declare extern conLBInitStorage(par:window,cid:int,strcount:int,opt avglen=20:int)
declare extern conCBInitStorage(par:window,cid:int,strcount:int,opt avglen=20:int)

'---- c:\FletchieIBPro\Subs\conLBAddStrList.iba ---------------------------------------------------------------------
declare extern conLBAddStrList(win:window,cid:int,strlist:pointer,remove:int),int

'---- c:\FletchieIBPro\Subs\conLBRightClick.iba ---------------------------------------------------------------------
declare extern conLBRightClick(win:window,cid:int,func:uint)

'---- c:\FletchieIBPro\Subs\conLoadImages.iba -----------------------------------------------------------------------
declare extern conLoadImages(fn:string,cx:int,fileflag:int),int

'---- c:\FletchieIBPro\Subs\conLV.iba -------------------------------------------------------------------------------
declare extern conLVGetText(win:window,cid:int,row:int,col:int,str:string),int
declare extern conLVSetExtendedStyle(win:window,cid:int,style:string)
declare extern conLVSetExtendedStyleRaw(win:window,cid:int,style:int)
declare extern conLVAutoSize(win:window,cid:int,col:int)
declare extern conLVHeaderAutoSize(win:window,cid:int,col:int)
declare extern conLVGetCheckState(win:window,cid:int,index:int),int
declare extern conLVSetCheckState(win:window,cid:int,index:int,ticked:int)
declare extern conLVHitTest(win:window,cid:int,row:int byref,col:int byref),int

'---- c:\FletchieIBPro\Subs\conLVColumnSet.iba ----------------------------------------------------------------------
declare extern conLVColumnListSet(win:window,cid:int,list:pointer,colwidth:int,deletelist:int)
declare extern conLVColumnSet(win:window,cid:int,cols:string)

'---- c:\FletchieIBPro\Subs\conNewControl.iba -----------------------------------------------------------------------
declare extern conNewControl(par:window,cid:int,cclass:string,x:int,y:int,w:int,h:int,st:int,ex:int),int

'---- c:\FletchieIBPro\Subs\conPC.iba -------------------------------------------------------------------------------
declare extern conProgressControl(par:window,cid:uint,x:int,y:int,w:int,h:int,style:string)
declare extern conPCSetRange(par:window,cid:int,min:int,max:int)
declare extern conPCSetPos(par:window,cid:int,pos:int)
declare extern conPCSetBarColor(par:window,cid:int,col:int)
declare extern conPCSetBkgColor(par:window,cid:int,col:int)

'---- c:\FletchieIBPro\Subs\conReset.iba ----------------------------------------------------------------------------
declare extern conReset(win:window,cid:int)

'---- c:\FletchieIBPro\Subs\conSlider.iba ---------------------------------------------------------------------------
declare extern conSliderControl(par:window,cid:int,x:int,y:int,w:int,h:int,style:string),int
declare extern conSliderSetThumbSize(par:window,cid:int,size:int)
declare extern conSliderSetBuddy(par:window,cid:int,fl:int,bid:int),int
declare extern conSliderGetPos(par:window,cid:int),int
declare extern conSliderSetPos(par:window,cid:int,pos:int)
declare extern conSliderSetRange(par:window,cid:int,min:int,max:int)

'---- c:\FletchieIBPro\Subs\conTab.iba ------------------------------------------------------------------------------
declare extern conTabControl(par:window,cid:int,x:int,y:int,w:int,h:int,style:string)
declare extern conTabInsert(par:window,cid:int,str:string,ind:int)

'---- c:\FletchieIBPro\Subs\conTV.iba -------------------------------------------------------------------------------
declare extern conTVControl(par:window,cid:int,x:int,y:int,w:int,h:int,style:string),int
declare extern conTVFullInsert(par:window,cid:int,text:string,lp:int,insertafter:int,imunsel:int,imsel:int,noimunsel:int,noimsel:int),int
declare extern conTVInsert(par:window,cid:int,text:string,lp:int,parent:int,insertafter:int,imunsel:int,imsel:int),int
declare extern conTVSetColor(par:window,cid:int,fg:int,bg:int)
declare extern conTVUseImages(par:window,cid:int,hnd:int),int
declare extern conTVHitTest(par:window,cid:int,a:point,hitem:int byref,fl:int byref),int
declare extern conTVDelete(par:window,cid:int,hitem:int),int
declare extern conTVExpand(par:window,cid:int,hitem:int),int
declare extern conTVGetItemText(par:window,cid:int,hitem:int),string
declare extern conTVGetSelItem(),int
declare extern conTVGetParent(par:window,cid:int,hitem:int),int
declare extern conTVGetItemFullText(par:window,cid:int,hitem:int),string
declare extern conTVGetCurItemFullText(par:window,cid:int),string

'---- c:\FletchieIBPro\Subs\CreateShortCut.iba ----------------------------------------------------------------------
declare extern CreateShortCut(fn:string,towhat:string,desc:string,startdir:string,args:string,hotkey:int,iconfile:string,iconid:int),int

'---- c:\FletchieIBPro\Subs\DaysFromStartOfYear.iba -----------------------------------------------------------------
declare extern DaysFromStartOfYear(year:int,month:int,day:int),int

'---- c:\FletchieIBPro\Subs\DaysInMonth.iba -------------------------------------------------------------------------
declare extern DaysInMonth(year:int,month:int),int

'---- c:\FletchieIBPro\Subs\Debug.iba -------------------------------------------------------------------------------
declare extern DebugOut(str:string)
declare extern DebugStart(fn:string),int

'---- c:\FletchieIBPro\Subs\DeleteWildFile.iba ----------------------------------------------------------------------
declare extern DeleteWildFile(dir:string,fn:string),int

'---- c:\FletchieIBPro\Subs\DirExists.iba ---------------------------------------------------------------------------
declare extern DirExists(fn:string),int

'---- c:\FletchieIBPro\Subs\DottedFour.iba --------------------------------------------------------------------------
declare extern DottedFour(a:uint,b:uint,c:uint,d:uint),string
declare extern ip2uint(a:int,b:int,c:int,d:int),string
declare extern uint2ip(ip:uint,a:int byref,b:int byref,c:int byref,d:int byref)

'---- c:\FletchieIBPro\Subs\DragWindow.iba --------------------------------------------------------------------------
declare extern DragWindow(win:window,opt cid=0:int)

'---- c:\FletchieIBPro\Subs\DynaAddStr.iba --------------------------------------------------------------------------
declare extern DynaAddStr(what:DynaStore,str:string)

'---- c:\FletchieIBPro\Subs\DynaAddStrList.iba ----------------------------------------------------------------------
declare extern DynaAddStrZZ(what:DynaStore,from:pointer),int

'---- c:\FletchieIBPro\Subs\DynaDelete.iba --------------------------------------------------------------------------
declare extern DynaDelete(what:DynaStore),int

'---- c:\FletchieIBPro\Subs\DynaGetStr.iba --------------------------------------------------------------------------
declare extern DynaGetStr(what:DynaStore,index:int,str:string),int

'---- c:\FletchieIBPro\Subs\DynaGetStrPtr.iba -----------------------------------------------------------------------
declare extern DynaGetStrPtr(what:DynaStore,index:int),pointer

'---- c:\FletchieIBPro\Subs\DynaInsertStr.iba -----------------------------------------------------------------------
declare extern DynaInsertStr(what:DynaStore,index:uint,str:string),int

'---- c:\FletchieIBPro\Subs\DynaLoadFile.iba ------------------------------------------------------------------------
declare extern DynaLoadFile(what:DynaStore,fn:string),int

'---- c:\FletchieIBPro\Subs\DynaNew.iba -----------------------------------------------------------------------------
declare extern DynaNew(what:DynaStore,inititems:int,stp:int),int

'---- c:\FletchieIBPro\Subs\DynaRemoveStr.iba -----------------------------------------------------------------------
declare extern DynaRemoveStr(what:DynaStore,index:uint)

'---- c:\FletchieIBPro\Subs\DynaRenew.iba ---------------------------------------------------------------------------
declare extern DynaRenew(what:DynaStore,inititems:int,stp:int),int

'---- c:\FletchieIBPro\Subs\DynaSaveFile.iba ------------------------------------------------------------------------
declare extern DynaSaveFile(what:DynaStore,fn:string,opt term="\xD\xA":string),int

'---- c:\FletchieIBPro\Subs\DynaSortStr.iba -------------------------------------------------------------------------
declare extern DynaSortStr(what:DynaStore,opt reverse=0:int)

'---- c:\FletchieIBPro\Subs\DynaSwapStr.iba -------------------------------------------------------------------------
declare extern DynaSwapStr(what:DynaStore,index1:uint,index2:uint)

'---- c:\FletchieIBPro\Subs\Encode64.iba ----------------------------------------------------------------------------
declare extern Encode64(what:pointer,size:int,outfile:file)

'---- c:\FletchieIBPro\Subs\EncodeFile64.iba ------------------------------------------------------------------------
declare extern EncodeFile64(fn:string,outfile:file),int

'---- c:\FletchieIBPro\Subs\FileExists.iba --------------------------------------------------------------------------
declare extern FileExists(fn:string),int

'---- c:\FletchieIBPro\Subs\GetAttribStr.iba ------------------------------------------------------------------------
declare extern GetAttribStr(fn:string),string

'---- c:\FletchieIBPro\Subs\GetClrButtonFace.iba --------------------------------------------------------------------
declare extern GetClrButtonFace(),int

'---- c:\FletchieIBPro\Subs\GetClrStaticText.iba --------------------------------------------------------------------
declare extern GetClrStaticText(),int

'---- c:\FletchieIBPro\Subs\GetCMClientCoords.iba -------------------------------------------------------------------
declare extern GetCMClientCoords(win:window,pnt:point,usequal:int)

'---- c:\FletchieIBPro\Subs\GetCommandText.iba ----------------------------------------------------------------------
declare extern GetCommandText(),string
declare extern ArgV(n:uint),string
declare extern ArgC(),int

'---- c:\FletchieIBPro\Subs\GetDLLVersion.iba -----------------------------------------------------------------------
declare extern GetDLLVersion(name:string),int

'---- c:\FletchieIBPro\Subs\GetDriveLetters.iba ---------------------------------------------------------------------
declare extern GetDriveLetters(fl:int),string

'---- c:\FletchieIBPro\Subs\GetDriveTypeStrFL.iba -------------------------------------------------------------------
declare extern GetDriveTypeStr(dir:string),string

'---- c:\FletchieIBPro\Subs\GetDroppedFiles.iba ---------------------------------------------------------------------
setid "iddropfiles",563
declare "shell32",AllowFileDrop alias DragAcceptFiles(hWnd:int,fAccept:int),int
declare extern GetDroppedFiles(here:DynaStore,empty:int)

'---- c:\FletchieIBPro\Subs\GetFileBinaryVersion.iba ----------------------------------------------------------------
declare extern GetFileBinaryVersion(fn:string,a:int byref,b:int byref,c:int byref,d:int byref),int

'---- c:\FletchieIBPro\Subs\GetFileExt.iba --------------------------------------------------------------------------
declare extern GetFileExt(fn:string,filename:pointer,ext:pointer)

'---- c:\FletchieIBPro\Subs\GetFileModifiedISO.iba ------------------------------------------------------------------
declare extern GetFileModifiedISO(fn:string,retstring:string,locflag:int),int

'---- c:\FletchieIBPro\Subs\GetFiles.iba ----------------------------------------------------------------------------
setid "GF_FILE",1
setid "GF_DIRUNI",2
setid "GF_DIR",3
declare extern GetFilesFL(dir:string,ex:string,cb:uint,reflag:int,OPT ignore=0 as INT)
declare extern GetDynaDirList(what:DynaStore,dir:string,reflag:int),int
declare extern GetDynaFileList(what:DynaStore,dir:string,ex:string,reflag:int),int

'---- c:\FletchieIBPro\Subs\GetFileTimeAsISO.iba --------------------------------------------------------------------
declare extern GetFileTimeAsISO(ft:FILETIME,isostr:string,loc:int)

'---- c:\FletchieIBPro\Subs\GetFileTimeFromISO.iba ------------------------------------------------------------------
declare extern GetFileTimeFromISO(ft:FILETIME byref,iso:string)

'---- c:\FletchieIBPro\Subs\GetIBKeyWords.iba -----------------------------------------------------------------------
declare extern GetIBKeyWords(dsReserved:DynaStore,dsSetId:DynaStore,dsConst:DynaStore,dsTypes:DynaStore)

'---- c:\FletchieIBPro\Subs\GetIBProDir.iba -------------------------------------------------------------------------
declare extern GetIBProDir(root:string,bin:string),int

'---- c:\FletchieIBPro\Subs\GetISONowUTC.iba ------------------------------------------------------------------------
declare extern GetISONowUTC(needmillies:int),string

'---- c:\FletchieIBPro\Subs\GetPathFile.iba -------------------------------------------------------------------------
declare extern GetPathFile(fn:string,path:pointer,filename:pointer)

'---- c:\FletchieIBPro\Subs\GetSpecialDirs.iba ----------------------------------------------------------------------
declare extern GetMyDesktopDir(str:string,buflen:int),int
declare extern GetMyAppDataDir(str:string,buflen:int),int
declare extern GetMyQuickLaunch(str:string,buflen:int),int
declare extern GetMyDocsDir(str:string,buflen:int),int
declare extern GetMyStartMenu(str:string,buflen:int),int
declare extern sGetDir(str:string,buflen:int,what:int),int
declare extern GetDirectoryWindows(wdir:string),int
declare extern GetDirectorySystem(sdir:string),int

'---- c:\FletchieIBPro\Subs\GetSysInfo.iba --------------------------------------------------------------------------
declare extern GetSysInfo(numofprocessors:pointer,processormask:pointer,allocgranularity:pointer)

'---- c:\FletchieIBPro\Subs\GetSysTrayMenuXY.iba --------------------------------------------------------------------
declare extern GetSysTrayMenuXY(w:window,x:int byref,y:int byref)

'---- c:\FletchieIBPro\Subs\GetTextFromClipBoard.iba ----------------------------------------------------------------
declare extern GetTextFromClipBoard(win:window,where:int byref),int

'---- c:\FletchieIBPro\Subs\GetWorkArea.iba -------------------------------------------------------------------------
declare extern GetWorkArea(x:int byref,y:int byref,w:int byref,h:int byref)

'---- c:\FletchieIBPro\Subs\intMin.iba ------------------------------------------------------------------------------
declare extern intMin(a:int,b:int),int

'---- c:\FletchieIBPro\Subs\intMinNZ.iba ----------------------------------------------------------------------------
declare extern intMinNZ(a:int,b:int),int

'---- c:\FletchieIBPro\Subs\IsFileReadOnly.iba ----------------------------------------------------------------------
declare extern IsFileReadOnly(fn:string,fl:int byref),int

'---- c:\FletchieIBPro\Subs\IsLeapYear.iba --------------------------------------------------------------------------
declare extern IsLeapYear(year:int),int

'---- c:\FletchieIBPro\Subs\KeyJustDown.iba -------------------------------------------------------------------------
declare extern KeyJustDown(n:int),int

'---- c:\FletchieIBPro\Subs\lens.iba --------------------------------------------------------------------------------
declare extern lens(str:string),int

'---- c:\FletchieIBPro\Subs\MakeFull2DScreen.iba --------------------------------------------------------------------
declare extern MakeFull2DScreen(x:int,y:int,bpp:int)

'---- c:\FletchieIBPro\Subs\MakeTempFile.iba ------------------------------------------------------------------------
declare extern MakeTempFile(prefix:string,fn:string),int

'---- c:\FletchieIBPro\Subs\MatchStart.iba --------------------------------------------------------------------------
declare extern MatchStart(start:String,from:String,Opt remainder=Null:Pointer),Int

'---- c:\FletchieIBPro\Subs\mciWave.iba -----------------------------------------------------------------------------
declare extern mciOpenWave(fn:string,moniker:string)
declare extern mciCloseWave(moniker:string)
declare extern mciPlayWave(moniker:string)
declare extern mciStopWave(moniker:string)
declare extern mciSounds(fl:int)

'---- c:\FletchieIBPro\Subs\MemAvailable.iba ------------------------------------------------------------------------
declare extern MemAvailable(),int

'---- c:\FletchieIBPro\Subs\MemLoadFile.iba -------------------------------------------------------------------------
declare extern MemLoadFile(fn:string,bufsize:uint byref,isstr:int),pointer

'---- c:\FletchieIBPro\Subs\Mess.iba --------------------------------------------------------------------------------
declare extern ConfirmExit(win:window,pn:string),int
declare extern ConfirmSaveChanges(win:window,pn:string,fn:string),int

'---- c:\FletchieIBPro\Subs\MessageWait.iba -------------------------------------------------------------------------
declare extern MessageWait(Message:string,opt yn=0:int),int

'---- c:\FletchieIBPro\Subs\MinimumWorkingSet.iba -------------------------------------------------------------------
declare extern MinimumWorkingSet()

'---- c:\FletchieIBPro\Subs\ModifyWindowStyle.iba -------------------------------------------------------------------
declare extern ModifyWindowStyle(win:int,st:int,fl:int,opt invalidate=0:int)
declare extern ModifyWindowExStyle(win:int,exst:int,flag:int,opt invalidate=0:int)

'---- c:\FletchieIBPro\Subs\MousePointerArrow.iba -------------------------------------------------------------------
declare extern MousePointerArrow(opt win=FrontBuffer:window)

'---- c:\FletchieIBPro\Subs\MousePointerOff.iba ---------------------------------------------------------------------
declare extern MousePointerOff(opt win=FrontBuffer:window)

'---- c:\FletchieIBPro\Subs\MousePointerWait.iba --------------------------------------------------------------------
declare extern MousePointerWait(opt win=FrontBuffer:window)

'---- c:\FletchieIBPro\Subs\RandomString.iba ------------------------------------------------------------------------
declare extern RandomNumStr(min:int,max:int,str:string)
declare extern RandomString(minlen:uint,maxlen:uint,str:string)

'---- c:\FletchieIBPro\Subs\ReadableFileSize.iba --------------------------------------------------------------------
declare extern ReadableFileSize(size:uint64),string

'---- c:\FletchieIBPro\Subs\RegKeyIDs.iba ---------------------------------------------------------------------------
setid "HKEY_CLASSES_ROOT",0x80000000
setid "HKEY_CURRENT_USER",0x80000001
setid "HKEY_LOCAL_MACHINE",0x80000002
setid "HKEY_USERS",0x80000003
setid "HKEY_PERFORMANCE_DATA",0x80000004
setid "HKEY_CURRENT_CONFIG",0x80000005
setid "HKEY_DYN_DATA",0x80000006
setid "HKEY_PERFORMANCE_TEXT",0x80000050
setid "HKEY_PERFORMANCE_NLSTEXT",0x80000060

'---- c:\FletchieIBPro\Subs\RegReadStr.iba --------------------------------------------------------------------------
declare extern RegReadStr(root:int,key:string,ele:string,value:string,opt MaxLength=255:int),int

'---- c:\FletchieIBPro\Subs\RegWriteStr.iba -------------------------------------------------------------------------
declare extern RegWriteStr(root:int,key:string,ele:string,value:string),int

'---- c:\FletchieIBPro\Subs\RelativePath.iba ------------------------------------------------------------------------
declare extern RelativePath(relto:string,rel:string),string

'---- c:\FletchieIBPro\Subs\ReNew.iba -------------------------------------------------------------------------------
declare extern ReNew(pnt:int byref,elements:int,opt elesize=4:int),int

'---- c:\FletchieIBPro\Subs\RunDosCmd.iba ---------------------------------------------------------------------------
declare extern RunDosCmd(str:string),int

'---- c:\FletchieIBPro\Subs\RunnWait.iba ----------------------------------------------------------------------------
declare extern RunnWait(fn:string,params:string),int

'---- c:\FletchieIBPro\Subs\RunProg.iba -----------------------------------------------------------------------------
declare extern RunConsoleApp(fn:string,exepath:string,cline:string,StartDir:string,OutputFN:string,cbaddr:uint),int

'---- c:\FletchieIBPro\Subs\SaveBitMap.iba --------------------------------------------------------------------------
declare extern SaveBitMap(filename:string,win:anytype,bitsneeded:int,opt x=-1:int,opt y=0:int,opt w=0:int,opt h=0:int),int

'---- c:\FletchieIBPro\Subs\SaveResource.iba ------------------------------------------------------------------------
declare extern SaveResource(id:int,ty:int,fn:string),string

'---- c:\FletchieIBPro\Subs\SendToClipBoard.iba ---------------------------------------------------------------------
declare extern SendToClipBoard(win:window,str:string),int

'---- c:\FletchieIBPro\Subs\SetMinTrackedWindowSize.iba -------------------------------------------------------------
setid "idgetminmaxinfo",0x24
declare extern SetMinTrackedWindowSize(w:int,h:int)
declare extern SetTrackedWindowSize(clientsize:int,minw:int,minh:int,opt maxw=-1:int,opt maxh=-1:int)

'---- c:\FletchieIBPro\Subs\SetProcessSpeed.iba ---------------------------------------------------------------------
declare extern SetProcessSpeed(speed:int)

'---- c:\FletchieIBPro\Subs\SplitterFunctions.iba -------------------------------------------------------------------
Const WM_SPLITTERSIZED = 0x8000 + 0x1000 
Const WM_SPLITTERSIZING = WM_SPLITTERSIZED+1
Const WM_SPLITTERLBUTTONDN = WM_SPLITTERSIZED+2 
Const WM_SPLITTERRBUTTONDN = WM_SPLITTERSIZED+3
Const WM_SPLITTERLBUTTONDBLCLK = WM_SPLITTERSIZED+4
Const WM_SPLITTERRBUTTONUP = WM_SPLITTERSIZED+5
Const WM_SPLITTERCONTROL = WM_SPLITTERSIZED+20
declare extern CreateSplitter(par:Window,splW:Window,style:Int,l:Int,t:Int,w:Int,h:Int,cid:Int),Int
declare extern SetSplitterMin(splitter:Window,min:Int),Int
declare extern SetSplitterMax(splitter:Window,max:Int),Int
declare extern GetSplitterMin(splitter:Window),Int
declare extern GetSplitterMax(splitter:Window),Int
declare extern SetSplitterShadow(splitter:Window,onoff:Int),Int
declare extern SetSplitterState(splitter:Window,state:Int),Int
declare extern GetSplitterState(splitter:Window),Int
declare extern SetSplitterColors(splitter:Window,face:Int,high:Int),Int
declare extern GetSplitterColors(splitter:Window,c1:Int BYREF,c2:Int BYREF),Int
declare extern SetSplitterPos(splitter:Window,l:Int,t:Int,w:Int,h:Int),Int
declare extern GetSplitterPos(splitter:Window,l:Int BYREF,t:Int BYREF,w:Int BYREF,h:Int BYREF),Int
declare extern SetSplitterStyle(splitter:Window,style:Int),Int
declare extern GetSplitterStyle(splitter:Window),Int
declare extern GetSplitterPercentage(splitter:Window),Int
declare extern CloseSplitter(splitter:Window),Int

'---- c:\FletchieIBPro\Subs\SplitTwo.iba ----------------------------------------------------------------------------
declare extern SplitTwo(from:string,sep:string,left:string,right:string,tidy:int,opt rtl=0:int),int

'---- c:\FletchieIBPro\Subs\strscan.iba -----------------------------------------------------------------------------
declare extern strscan(mainstr:string,substring:string,opt spos=1:int),int

'---- c:\FletchieIBPro\Subs\SubClassWindow.iba ----------------------------------------------------------------------
declare extern SubClassWindow(win:anytype,subhandler:uint,opt cid=0:int),uint

'---- c:\FletchieIBPro\Subs\SysTray.iba -----------------------------------------------------------------------------
setid "idsystray",1024
declare extern SysTrayIcon(win:window,id:int,flag:int,tiptext:string,fn:string),int
declare extern DeleteSysTrayIcon(win:window,id:int),int

'---- c:\FletchieIBPro\Subs\unRgb.iba -------------------------------------------------------------------------------
declare extern unRgb(col:int,r:int byref,g:int byref,b:int byref),int

'---- c:\FletchieIBPro\Subs\va_count.iba ----------------------------------------------------------------------------
declare extern va_count(),int

'---- c:\FletchieIBPro\Subs\WaitFade.iba ----------------------------------------------------------------------------
declare extern WaitFade(),int

'---- c:\FletchieIBPro\Subs\WarmUp.iba ------------------------------------------------------------------------------
declare extern WarmUp(col:int)

'---- c:\FletchieIBPro\Subs\WinAlpha.iba ----------------------------------------------------------------------------
declare extern WinAlphaAvailable(),int
declare extern WinAlpha(win:int,alpha:int,opt transpixel=-1:int),int
declare extern WinAlphaOff(win:int)

'---- c:\FletchieIBPro\Subs\winapp.iba ------------------------------------------------------------------------------
declare extern GetWinEffectiveRect(w1:window,rc:winrect,cid1:int,opt cid2=0:int,opt cid3=0:int,opt cid4=0:int,opt cid5=0:int,opt cid6=0:int)
declare extern MenuControlFlip(w1:window,mid:int,cid:int)
declare extern conStatusSliderCon(statuswin:window,statuscid:int,pane:int,wf:window,slidercid:int)
declare extern conStatusSliderUpdate(statuswin:window,statuscid:int,pane:int,slidercid:int)

'---- c:\FletchieIBPro\Subs\WindowOnTop.iba -------------------------------------------------------------------------
declare extern WindowOnTop(win:int,topflag:int)

'---- c:\FletchieIBPro\Subs\xCloseFile.iba --------------------------------------------------------------------------
declare extern xCloseFile(fv:xfile),int

'---- c:\FletchieIBPro\Subs\xinstr.iba ------------------------------------------------------------------------------
declare extern xinstr(str:pointer,find:pointer,opt startpos=1:int),int

'---- c:\FletchieIBPro\Subs\xOpenFile.iba ---------------------------------------------------------------------------
declare extern xOpenFile(fv:xfile,fn:string,how:string),int

'---- c:\FletchieIBPro\Subs\xRead.iba -------------------------------------------------------------------------------
declare extern xRead(fv:xfile,str:string),int

'---- c:\FletchieIBPro\Subs\xSeek.iba -------------------------------------------------------------------------------
declare extern xSeek(fv:xfile,pos:int)

'---- c:\FletchieIBPro\Subs\xWrite.iba ------------------------------------------------------------------------------
declare extern xWrite(fv:xfile,str:string),int

'---- c:\FletchieIBPro\Subs\YesNoBox.iba ----------------------------------------------------------------------------
declare extern YesNoBox(win:window,text:string,title:string),int
