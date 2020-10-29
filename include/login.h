// login.h
// Originally from ES2
// Modified for XKX

#ifndef __LOGIN__
#define __LOGIN__

#define LOGIN_TIMEOUT           360

#define WELCOME                 "/adm/etc/welcome"
#define NEW_PLAYER_INFO         "/adm/etc/new_player"
#define UNREG_MOTD              "/adm/etc/unreg_motd"
#define MOTD                    "/adm/etc/motd"
#define NOTICE                  "/adm/etc/notice"
#define NOTICE_MOTD             "/adm/etc/notice_motd"
#define WIZLIST                 "/adm/etc/wizlist"

#define REGISTER_ROOM           "/d/register/regroom"
#define BORN_ROOM               "/d/register/entry"
#define WIZARD_ROOM             "/d/wizard/wizard_room"
#define START_ROOM              "/d/city/kedian"
#define DEATH_ROOM              "/d/death/gate"
#define REVIVE_ROOM             "/d/city/wumiao"
#define CHAT_ROOM               "/inherit/room/chatroom" 
#define ENABLE_MD5_PASSWORD 

// This is how much users can 'enter' the mud actually. Maintained
// by LOGIN_D. The max number of connections can be built between
// server(MudOS) and users' client(telnet) is specified in MudOS
// config file, which must be larger than MAX_USER to allow users
// including wizards and admins have chance to connect.
// By Annihilator (02-22-95)
#define MAX_USERS                ((int) CONFIG_D->query_int("max users"))

// This defines the minimum wiz_level of users that are allowed to 
// enter the mud. Note players has wiz_level 0.
#define WIZ_LOCK_LEVEL          ((int) CONFIG_D->query_int("wiz lock"))

#endif
