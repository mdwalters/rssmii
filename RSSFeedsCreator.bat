:startup_begin
@echo off
:: ===========================================================================
:: RSMii feed.xml creator for Windows
set version=1.0.1
:: AUTHORS: KcrPL
:: ***************************************************************************
:: Copyright (c) 2017 RiiConnect24, and it's (Lead) Developers
:: ===========================================================================
if exist temp.bat del /q temp.bat
set mode=130,30
mode %mode%

:: Reseting variables goes here
set /a patherror=0
set /a copyingsdcard=0

:: Window Title
title RSSMii Feeds Creator v.%version%  Created by KcrPL.
set last_build=2017/10/28
set at=18:31

set /a Update_Activate=1
set /a offlinestorage=0
set FilesHostedOn=https://raw.githubusercontent.com/KcrPL/KcrPL.github.io/master/Patchers_Auto_Update/RSSMiiCreator
set MainFolder=%appdata%\RSSMiiCreator
set TempStorage=%appdata%\RSSMiiCreator\internet\temp

:: Trying to prevent running from OS that is not Windows.
if %os%=="" goto not_windows_nt
if not %os%==Windows_NT goto not_windows_nt

:: If program is opened as an admin the path will messed up
set /a patherror=0
if "%cd%"=="%windir%\system32" set /a patherror=1

goto begin_main
:begin_main
mode %mode%
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
if %patherror%==1 echo :----------------------------------------------------------------:                
if %patherror%==1 echo : Warning: Please run this application without admin privilages. :               
if %patherror%==1 echo :----------------------------------------------------------------:
echo.
echo Welcome to RSS Feeds Creator! In this program you can create file feed.xml that contains info about
echo your RSS Feeds!
echo.
echo         ````````````````````````````````````````````````````````````````````````````````````        
echo     `.-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-.`    
echo    .:::::    ```.--:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.   
echo   -::::::           `.-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-  
echo  .///////`              `.:://///////////////::::::::::///////////::::::///////////:::::://///////. 
echo  .///////:::::--.``        `-://////////////-`````````...://///:-.``````.-://///:-.``````.-://////. 
echo  .///////::///////::-`       `-:////////////.   ```````   .///:`  `....`   -///:`  `....`  `-/////. 
echo  .///////````..-::////:-`      `-///////////-   ://////.   ://-   ://///.```///-   :////:.```/////. 
echo  -///////        `.-:////-`      .//////////-   :::::::`  `://:`   `.--:://////:`  ``.--::////////- 
echo  -///////`           .:////-`     `:////////-   ``````  `.://///-``      `.://///-``      `.://///- 
echo  -////////:::-.`       `:///:.     `:///////-   ---.   .://////////::--.`   :///////::--.`   :////- 
echo  -//////////////:-`      -////.     `///////-   :///:`  `-////```.//////:   .//```.//////:   -////- 
echo  -/////////////////-`     .////.     .//////-   //////.   .///-   `-:::-`   ://-   .-:::-`  `:////- 
echo  -+++++++/-````./+++/`     .+++/`     :+++++-   /+++++/-`  `/+/:.`       `./+++/:.`       `-/+++++- 
echo  -+++++++.      `/+++/`     :+++-     .+++++/:::/++++++/::::/++++//:::::://+++++++//:::::///++++++- 
echo  .+++++++`       /++++:     .+++/     `+++++////++++++/////++++/////////////++++/////////////+++++. 
echo   :++++++/.    `:++++++     `++++      /+++++///+++++////++++++///+++++++////+++///+++++++////+++:  
echo    -++++++/:--:/+++++++:----:++++::::::+++++++++++++++++++++++++++++++++++++++++++++++++++++++++-   
echo     `-/++////////++++++//////++++/////+++++++++++++++++++++++++++++++++++++++++++++++++++++++/-`    
echo         `..................................................................................`        
echo.
echo Press any button to continue. (Do you have any problems with it? Contact us at support@riiconnect24.net)
pause>NUL
if %patherror%==1 goto begin_main
goto startup_script
:startup_script
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo.
echo.
echo Checking for updates...
echo         ````````````````````````````````````````````````````````````````````````````````````        
echo     `.-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-.`    
echo    .:::::    ```.--:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.   
echo   -::::::           `.-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-  
echo  .///////`              `.:://///////////////::::::::::///////////::::::///////////:::::://///////. 
echo  .///////:::::--.``        `-://////////////-`````````...://///:-.``````.-://///:-.``````.-://////. 
echo  .///////::///////::-`       `-:////////////.   ```````   .///:`  `....`   -///:`  `....`  `-/////. 
echo  .///////````..-::////:-`      `-///////////-   ://////.   ://-   ://///.```///-   :////:.```/////. 
echo  -///////        `.-:////-`      .//////////-   :::::::`  `://:`   `.--:://////:`  ``.--::////////- 
echo  -///////`           .:////-`     `:////////-   ``````  `.://///-``      `.://///-``      `.://///- 
echo  -////////:::-.`       `:///:.     `:///////-   ---.   .://////////::--.`   :///////::--.`   :////- 
echo  -//////////////:-`      -////.     `///////-   :///:`  `-////```.//////:   .//```.//////:   -////- 
echo  -/////////////////-`     .////.     .//////-   //////.   .///-   `-:::-`   ://-   .-:::-`  `:////- 
echo  -+++++++/-````./+++/`     .+++/`     :+++++-   /+++++/-`  `/+/:.`       `./+++/:.`       `-/+++++- 
echo  -+++++++.      `/+++/`     :+++-     .+++++/:::/++++++/::::/++++//:::::://+++++++//:::::///++++++- 
echo  .+++++++`       /++++:     .+++/     `+++++////++++++/////++++/////////////++++/////////////+++++. 
echo   :++++++/.    `:++++++     `++++      /+++++///+++++////++++++///+++++++////+++///+++++++////+++:  
echo    -++++++/:--:/+++++++:----:++++::::::+++++++++++++++++++++++++++++++++++++++++++++++++++++++++-   
echo     `-/++////////++++++//////++++/////+++++++++++++++++++++++++++++++++++++++++++++++++++++++/-`    
echo         `..................................................................................`        
echo.
:: Update script.
set updateversion=0.0.0
:: Delete version.txt and whatsnew.txt
if %offlinestorage%==0 if exist %TempStorage%\version.txt del %TempStorage%\version.txt /q
if %offlinestorage%==0 if exist %TempStorage%\version.txt` del %TempStorage%\version.txt` /q
if %offlinestorage%==0 if exist %TempStorage%\whatsnew.txt del %TempStorage%\whatsnew.txt /q
if %offlinestorage%==0 if exist %TempStorage%\whatsnew.txt` del %TempStorage%\whatsnew.txt` /q

if not exist %TempStorage% md %TempStorage%
:: Commands to download files from server.
if %Update_Activate%==1 if %offlinestorage%==0 powershell -command "(new-object System.Net.WebClient).DownloadFile('%FilesHostedOn%/whatsnew.txt', '%TempStorage%/whatsnew.txt')"
if %Update_Activate%==1 if %offlinestorage%==0 powershell -command "(new-object System.Net.WebClient).DownloadFile('%FilesHostedOn%/version.txt', '%TempStorage%/version.txt')"
	set /a temperrorlev=%errorlevel%
	
set /a updateserver=1
	::Bind error codes to errors here
	if not %errorlevel%==0 set /a updateserver=0
	
if exist "%TempStorage%\version.txt`" ren "%TempStorage%\version.txt`" "version.txt"
if exist "%TempStorage%\whatsnew.txt`" ren "%TempStorage%\whatsnew.txt`" "whatsnew.txt"
:: Copy the content of version.txt to variable.
if exist %TempStorage%\version.txt set /p updateversion=<%TempStorage%\version.txt
if not exist %TempStorage%\version.txt set /a updateavailable=0
if %Update_Activate%==1 if exist %TempStorage%\version.txt set /a updateavailable=1
:: If version.txt doesn't match the version variable stored in this batch file, it means that update is available.
if %updateversion%==%version% set /a updateavailable=0

if %Update_Activate%==1 if %updateavailable%==1 set /a updateserver=2
if %Update_Activate%==1 if %updateavailable%==1 goto update_notice

goto 1
:update_notice
set /a update=1
cls
echo.                                                                       
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo    /---\   An Update is available.              
echo   /     \  An Update for this program is available. We suggest updating this program to the latest version.
echo  /   !   \ 
echo  ---------  Current version: %version%
echo             New version: %updateversion%
echo                       1. Update                      2. Dismiss               3. What's new in this update?
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
set /p s=
if %s%==1 goto update_files
if %s%==2 goto 1
if %s%==3 goto whatsnew
goto update_notice
:update_files
cls
echo.                                                                       
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo    /---\   Updating.
echo   /     \  Please wait...
echo  /   !   \ 
echo  ---------  This program will restart shortly...
echo             Current version: %version%
echo             New version: %updateversion%
echo -------------------------------------------------------------------------------------------------------------------------------  
echo.
powershell -command "(new-object System.Net.WebClient).DownloadFile('%FilesHostedOn%/RSSFeedsCreator.bat', 'RSSFeedsCreator.bat`')"
if not exist RSSFeedsCreator.bat` goto update_fail

:: TEMP 
echo off >>temp.bat
echo ping localhost -n 2 >>temp.bat
echo del RSSFeedsCreator.bat /q >>temp.bat
echo ren RSSFeedsCreator.bat` RSSFeedsCreator.bat >>temp.bat
echo start RSSFeedsCreator.bat >>temp.bat
echo exit >>temp.bat

start temp.bat
exit	
exit
exit
:whatsnew
cls
if not exist %TempStorage%\whatsnew.txt goto whatsnew_notexist
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------           
echo.
echo What's new in update %updateversion%?
echo.
type %TempStorage%\whatsnew.txt
pause>NUL
goto update_notice
:whatsnew_notexist
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Error. What's new file is not available.
echo.
echo Press any button to go back.
pause>NUL
goto update_notice
:update_fail
cls
echo.                                                                       
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo.
echo --------------------------------------------------------------------------------------------------------------------------------              
echo    /---\   Updating failed.
echo   /     \  
echo  /   !   \ 
echo  ---------  This program will restart shortly...
echo             Current version: %version%
echo.
echo --------------------------------------------------------------------------------------------------------------------------------
echo.
timeout 5 /nobreak >NUL
goto startup_begin

:: :: :: ::
:1
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo :========================================================:
echo : RSSMii Feeds Creator Update System.                    :
if %updateserver%==1 echo : The latest version is installed. Press C to read more. :
if %updateserver%==2 echo : An Update is available. Press C to read more.          :
if %updateserver%==0 echo : A Update Server is not available. Press C to read more :
echo :========================================================:
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo  [*] Configuring
echo.
echo Do you want to start adding RSS Feeds?
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo                          1. Yes                                                 2. Exit
set /p s=
if %s%==1 goto 2
if %s%==2 goto end
if %s%==c goto more_info_update
if %s%==C goto more_info_update
goto 1
:more_info_update
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
if %updateserver%==1 echo The latest version of RSSMii Feeds Creator is now installed. (v%version%)
if %updateserver%==2 goto update_notice

if %updateserver%==0 echo Update server is not available.
if %updateserver%==0 echo We could not connect to the update server. Please check your internet connection. 
if %updateserver%==0 echo It can also mean that the server is under maintance now.
pause>NUL
goto 1
:2
cls
set /a feed_right_now=1
set /a error_nothing=0

set /a feedturnon_1=0
set /a feedturnon_2=0
set /a feedturnon_3=0
set /a feedturnon_4=0
set /a feedturnon_5=0
set /a feedturnon_6=0
set /a feedturnon_7=0
set /a feedturnon_8=0
set /a feedturnon_9=0
set /a feedturnon_10=0
set /a feedturnon_11=0
set /a feedturnon_12=0
set /a feedturnon_13=0
set /a feedturnon_14=0
set /a feedturnon_15=0
set /a feedturnon_16=0
set /a feedturnon_17=0
set /a feedturnon_18=0
set /a feedturnon_19=0
set /a feedturnon_20=0
set /a feedturnon_21=0
set /a feedturnon_22=0
set /a feedturnon_23=0
set /a feedturnon_24=0
set /a feedturnon_25=0

goto 3_feed_name

:3_feed_name
if %feed_right_now%==26 goto enough_feeds
set /a feed%feed_right_now%name=NUL
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Currently making feed number %feed_right_now%
echo.
if %error_nothing%==1 echo ERROR: Please type in something!
if %error_nothing%==1 set /a error_nothing=0
echo What should be the name of your RSS Feed?
echo.
set /p feed_temp_name=Feed name :^> 

if feed%feed_right_now%name==feedNULname set /a error_nothing=1
if feed%feed_right_now%name==feedNULname goto 3_feed_name

goto 3_feed_url

:3_feed_url
set /a feed%feed_right_now%url=NUL
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Currently making feed number %feed_right_now%
echo.
if %error_nothing%==1 echo ERROR: Please type in something!
if %error_nothing%==1 set /a error_nothing=0
echo What is the URL (link) of your RSS Feed? (example: https://status.rc24.xyz/rss)
echo.
echo How to copy and paste?
echo Windows 10: CTRL+V
echo Anything older than Windows 10: Right click -^> Paste
echo.

set /p feed_temp_url=Feed URL :^> 

if feed%feed_right_now%url==feedNULurl set /a error_nothing=1
if feed%feed_right_now%url==feedNULurl goto 3_feed_url

goto 4
:4
set feed%feed_right_now%url=%feed_temp_url%
set feed%feed_right_now%name=%feed_temp_name%

cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Currently making feed number %feed_right_now%
echo.
echo Feed name: %feed_temp_name%
echo Feed URL: %feed_temp_url%
echo.
echo Is it ok? Or maybe do you want to correct something?
echo -------------------------------------------------------------------------------------------------------------------------------
echo 1. Ok, let's add another feed  2. Fix something in this feed 3. Ok, enough of feeds
echo.
set /p s=


if %s%==1 set /a feedturnon_%feed_right_now%=1
if %s%==1 set /a feed_right_now=%feed_right_now%+1
if %s%==1 goto 3_feed_name

if %s%==2 goto 3_feed_name

if %s%==3 set /a feedturnon_%feed_right_now%=1
if %s%==3 goto create_scripts
goto 4
:enough_feeds
mode 150,28
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo We've set the limit of feeds to 25 because it might get dangerous later on.
echo.
echo       .::::-   -:::::::   `::`     .::::.             .:::::.     `:::-   .::   `::`   ::::::`.::::::::`.:::::::    ::::::  `::`  `::.  :::::         
echo       ./NMs-   -/:MMy/:   `+m-    +dm//hh+            sMm:/hds` `:ym/ydy` sMNy-`-MM-`:ymo////`oMM+/////`oMM+//+My..hM+//+My/:MM.  .MMo-yM+/oms.       
echo        `NM+       MMo     .s`     +dm///+:            sMm  `oMN-oNm` `/MN-sMMMNyoMM-sNN` .///`oMM+////  oMM+//oMh.:MM.  .MMo:MM.  .MMo-hMo//++.       
echo        `NM+       MMo             `:+:::yNh`          sMm  `oMm-sMNssshMM-sMN:dNMMM-oNN.`.+MM-oMM/::::  oMM/yNm+` :MM.  .MMo:MM.  .MMo`.+::::Nd/      
echo       ./mNs:      NN+             :yd+++hms`          sMN++ddo` sMm```/MM-sMN `/yMM-`-sNs+sMM-oMMo+++++.oMM.`:yNo..sMs++oMs:.sMo++oMh:.oNs+++Nh:      
echo       ``````     -//::::-  -:::::. `-----.      `::::::--/++/::..-.   `--`.-. `::+/`   :++---``--:+++++:.-/:- `-:::`/+++++:::`----/+:   ------`       
echo                  :/+NNo/: smy///hdo           `/hm////: odd///hms            -yN+hd+   /NN.     /hN///yNs.oNNs` /NN:oNN+/////.    hNm                 
echo                    .MM:  `NM+   yMd          `dNh. -::- dMh   yMN`          yNm. `oNd` /MM.     sMN   +MM-oMMMmooMM:oMN:::::      dMm                 
echo                    .MM:  `NM+   yMd           mNh. :hMd dMh   yMN`          dMNooohMN` /MM.     sMN   +MM-oMN/dNMMM:oMN/////`     hmd                 
echo                    .MM:   sNy///dmo           .+hm//dMd omd///dms           dMm...oMN` /MMo////`/hN///yMy.oMN .+hMM:oMN//////`    +o+                 
echo                     --`    ------.              `------  .-----.            ---   `--  `-------` `------  .--   `--`.--------`    ---                 
echo.                                                                                                                                                       
echo.                                                                                                                                                       
echo                             .......`   `...    ..`   ..` ........`            `......` ..`   `.`   `....`   `....`                                    
echo                            `osymmoo:  :yhsm/` `mm: `/dy/`mmysssss/            +oymmys/ mm/   ymh   :smmy:  :hhoodo-                                   
echo                               +MM   .yNs-`/Nh/`MM+/hm/` `MM+....`               /MM:   MMo...hMd    .MM/  `mMh..++:                                   
echo                               +MM   :MMs///MMo`MMyhmo`  `MMyoooo:               /MM:   MMhooomMd    .MM/   .ssooohy:                                  
echo                               +MM   :MMo:::NMo`MM/./dh/.`MMo......              /MM:   MM+   hMd   `:MMo`  sho...hNy   :hh`                           
echo                               -++   .++.   ++-`++.   ++:`++++++++:              .++.   ++-   /+/   :++++:   /+++++:    .++`                           
pause>NUL
goto create_scripts

:warning_already_exist_feeds
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo ERROR: feeds.xml file already exists. Do you want to delete it?
echo.
echo 1. Delete it
echo 2. No, exit.
set /p s=
if %s%==1 del feeds.xml /q
if %s%==1 goto create_scripts

if %s%==2 goto end
goto warning_already_exist_feeds
:create_scripts
if exist feeds.xml goto warning_already_exist_feeds
mode %mode%
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Please wait, while we are saving the feeds...
timeout 1 /nobreak >NUL

echo  ^<^?xml version="1.0" encoding="utf-8"^?^>>>feeds.xml
echo  ^<rss^>>>feeds.xml
if %feedturnon_1%==1 echo    ^<feed name="%feed1name%"^>^<![CDATA[%feed1url%]]^>^</feed^> >>feeds.xml
if %feedturnon_2%==1 echo    ^<feed name="%feed2name%"^>^<![CDATA[%feed2url%]]^>^</feed^> >>feeds.xml
if %feedturnon_3%==1 echo    ^<feed name="%feed3name%"^>^<![CDATA[%feed3url%]]^>^</feed^> >>feeds.xml
if %feedturnon_4%==1 echo    ^<feed name="%feed4name%"^>^<![CDATA[%feed4url%]]^>^</feed^> >>feeds.xml
if %feedturnon_5%==1 echo    ^<feed name="%feed5name%"^>^<![CDATA[%feed5url%]]^>^</feed^> >>feeds.xml
if %feedturnon_6%==1 echo    ^<feed name="%feed6name%"^>^<![CDATA[%feed6url%]]^>^</feed^> >>feeds.xml
if %feedturnon_7%==1 echo    ^<feed name="%feed7name%"^>^<![CDATA[%feed7url%]]^>^</feed^> >>feeds.xml
if %feedturnon_8%==1 echo    ^<feed name="%feed8name%"^>^<![CDATA[%feed8url%]]^>^</feed^> >>feeds.xml
if %feedturnon_9%==1 echo    ^<feed name="%feed9name%"^>^<![CDATA[%feed9url%]]^>^</feed^> >>feeds.xml
if %feedturnon_10%==1 echo    ^<feed name="%feed10name%"^>^<![CDATA[%feed10url%]]^>^</feed^> >>feeds.xml
if %feedturnon_11%==1 echo    ^<feed name="%feed11name%"^>^<![CDATA[%feed11url%]]^>^</feed^> >>feeds.xml
if %feedturnon_12%==1 echo    ^<feed name="%feed12name%"^>^<![CDATA[%feed12url%]]^>^</feed^> >>feeds.xml
if %feedturnon_13%==1 echo    ^<feed name="%feed13name%"^>^<![CDATA[%feed13url%]]^>^</feed^> >>feeds.xml
if %feedturnon_14%==1 echo    ^<feed name="%feed14name%"^>^<![CDATA[%feed14url%]]^>^</feed^> >>feeds.xml
if %feedturnon_15%==1 echo    ^<feed name="%feed15name%"^>^<![CDATA[%feed15url%]]^>^</feed^> >>feeds.xml
if %feedturnon_16%==1 echo    ^<feed name="%feed16name%"^>^<![CDATA[%feed16url%]]^>^</feed^> >>feeds.xml
if %feedturnon_17%==1 echo    ^<feed name="%feed17name%"^>^<![CDATA[%feed17url%]]^>^</feed^> >>feeds.xml
if %feedturnon_18%==1 echo    ^<feed name="%feed18name%"^>^<![CDATA[%feed18url%]]^>^</feed^> >>feeds.xml
if %feedturnon_19%==1 echo    ^<feed name="%feed19name%"^>^<![CDATA[%feed19url%]]^>^</feed^> >>feeds.xml
if %feedturnon_20%==1 echo    ^<feed name="%feed20name%"^>^<![CDATA[%feed20url%]]^>^</feed^> >>feeds.xml
if %feedturnon_21%==1 echo    ^<feed name="%feed21name%"^>^<![CDATA[%feed21url%]]^>^</feed^> >>feeds.xml
if %feedturnon_22%==1 echo    ^<feed name="%feed22name%"^>^<![CDATA[%feed22url%]]^>^</feed^> >>feeds.xml
if %feedturnon_23%==1 echo    ^<feed name="%feed23name%"^>^<![CDATA[%feed23url%]]^>^</feed^> >>feeds.xml
if %feedturnon_24%==1 echo    ^<feed name="%feed24name%"^>^<![CDATA[%feed24url%]]^>^</feed^> >>feeds.xml
if %feedturnon_25%==1 echo    ^<feed name="%feed25name%"^>^<![CDATA[%feed25url%]]^>^</feed^> >>feeds.xml
echo  ^</rss^>>>feeds.xml

goto 5
:5
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Creating feeds.xml done! Do you want to copy that file to an SD Card?
echo (If yes, connect your SD Card to your computer now)
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo 1. Yes  2. No, exit
set /p s=
if %s%==1 goto 5_sd_card_choose
if %s%==2 goto end
goto 5
:5_sd_card_choose
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Do you want to automatically detect SD Card or manually add it?
echo.
echo -------------------------------------------------------------------------------------------------------------------------------
echo 1. Automatically  2. Manually
set /p s=
if %s%==1 goto 5_sd_card_detect
if %s%==2 goto change_sd_card_letter
goto 5_sd_card_choose


:5_sd_card_detect
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Please wait...
goto sd_a
:sd_a
set /a check=0
if exist A:\apps set /a check=%check%+1
if %check%==1 set sdcard=A
goto sd_b
:sd_b
set /a check=0
if exist B:\apps set /a check=%check%+1
if %check%==1 set sdcard=B
goto sd_c
:sd_c
set /a check=0
if exist C:\apps set /a check=%check%+1
if %check%==1 set sdcard=C
goto sd_d
:sd_d
set /a check=0
if exist D:\apps set /a check=%check%+1
if %check%==1 set sdcard=D
goto sd_e
:sd_e
set /a check=0
if exist E:\apps set /a check=%check%+1
if %check%==1 set sdcard=E
goto sd_f
:sd_f
set /a check=0
if exist F:\apps set /a check=%check%+1
if %check%==1 set sdcard=F
goto sd_g
:sd_g
set /a check=0
if exist G:\apps set /a check=%check%+1
if %check%==1 set sdcard=G
goto sd_h
:sd_h
set /a check=0
if exist H:\apps set /a check=%check%+1
if %check%==1 set sdcard=H
goto sd_i
:sd_i
set /a check=0
if exist I:\apps set /a check=%check%+1
if %check%==1 set sdcard=J
goto sd_j
:sd_j
set /a check=0
if exist J:\apps set /a check=%check%+1
if %check%==1 set sdcard=J
goto sd_k
:sd_k
set /a check=0
if exist K:\apps set /a check=%check%+1
if %check%==1 set sdcard=K
goto sd_l
:sd_l
set /a check=0
if exist L:\apps set /a check=%check%+1
if %check%==1 set sdcard=L
goto sd_m
:sd_m
set /a check=0
if exist M:\apps set /a check=%check%+1
if %check%==1 set sdcard=M
goto sd_n
:sd_n
set /a check=0
if exist N:\apps set /a check=%check%+1
if %check%==1 set sdcard=N
goto sd_o
:sd_o
set /a check=0
if exist O:\apps set /a check=%check%+1
if %check%==1 set sdcard=O
goto sd_p
:sd_p
set /a check=0
if exist P:\apps set /a check=%check%+1
if %check%==1 set sdcard=P
goto sd_r
:sd_r
set /a check=0
if exist R:\apps set /a check=%check%+1
if %check%==1 set sdcard=R
goto sd_s
:sd_s
set /a check=0
if exist S:\apps set /a check=%check%+1
if %check%==1 set sdcard=S
goto sd_t
:sd_t
set /a check=0
if exist T:\apps set /a check=%check%+1
if %check%==1 set sdcard=T
goto sd_u
:sd_u
set /a check=0
if exist U:\apps set /a check=%check%+1
if %check%==1 set sdcard=U
goto sd_w
:sd_w
set /a check=0
if exist W:\apps set /a check=%check%+1
if %check%==1 set sdcard=W
goto sd_x
:sd_x
set /a check=0
if exist X:\apps set /a check=%check%+1
if %check%==1 set sdcard=X
goto sd_y
:sd_y
set /a check=0
if exist Y:\apps set /a check=%check%+1
if %check%==1 set sdcard=Y
goto sd_z
:sd_z
set /a check=0
if exist Z:\apps set /a check=%check%+1
if %check%==1 set sdcard=Z
goto sd_card_show
:sd_card_show
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
if %sdcard%==NotDefined echo An SD card was not found in the system.
if %sdcard%==NotDefined echo Please connect SD Card and press any button to try again.
if not %sdcard%==NotDefined goto 5_sd_card_defined
pause>NUL
goto 5
:sd_card_defined
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Current SD Card Letter: %sdcard%
echo Do you want to change SD Card drive letter?
echo.
echo ---------------------------------------------------------------------------------------------------------------------------
echo 1. Continue and copy files to SD Card             2. Change drive letter                  3. Exit
set /p s=
if %s%==1 goto sd_card_copying
if %s%==2 goto change_sd_card_letter
if %s%==3 goto end
goto sd_card_defined
:change_sd_card_letter
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Current SD Card Letter: %sdcard%
echo.
echo Type in new drive letter (e.g H)
set /p sdcard=
goto sd_card_defined
:sd_card_error
mode %mode%
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo There was an error while copying files.
pause
goto 5
:sd_card_copying
set /a copyingsdcard=1
set /a errorcopying=0
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.
echo Please wait... copying.
copy "feeds.xml" "%sdcard%:\" >NUL || set /a errorcopying=1
if %errorcopying%==1 goto sd_card_error
goto end
:end
set /a exiting=10
set /a timeouterror=1
timeout 1 /nobreak >NUL && set /a timeouterror=0
goto end1
:end1
mode %mode%
cls
echo RSSMii Feeds Creator - (C) KcrPL. v%version%. (Compiled on %last_build% at %at%)
echo -------------------------------------------------------------------------------------------------------------------------------
echo.

echo Creating feeds.xml is done.
echo Now, please open RSSMii and apply these feeds.
echo.
if %copyingsdcard%==1 echo The file has been copied to SD Card.
echo.
echo Exiting the patcher in...
if %exiting%==10 echo :----------: 10
if %exiting%==9 echo :--------- : 9
if %exiting%==8 echo :--------  : 8
if %exiting%==7 echo :-------   : 7
if %exiting%==6 echo :------    : 6
if %exiting%==5 echo :-----     : 5
if %exiting%==4 echo :----      : 4
if %exiting%==3 echo :---       : 3
if %exiting%==2 echo :--        : 2
if %exiting%==1 echo :-         : 1
if %exiting%==0 echo :          :
if %exiting%==0 exit
if %timeouterror%==0 timeout 1 /nobreak >NUL
if %timeouterror%==1 ping localhost -n 2 >NUL
set /a exiting=%exiting%-1
goto end1







