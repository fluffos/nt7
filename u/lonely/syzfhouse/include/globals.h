// globals.h
// this file will be automatically included by the driver
// for XKX mudlib, by Xiang

// Important directories
#define BACKUP_DIR      "/backup/"
#define COMMAND_DIR     "/cmds/"
#define CONFIG_DIR      "/adm/etc/"
#define DANGPU_DIR      "/clone/dangpu/"
#define DATA_DIR        "/data/"
#define HEIDIAN_DIR     "/clone/heidian/"
#define HELP_DIR        "/doc/"
#define INC_DIR         "/include/"
#define LOG_DIR         "/log/"
#define STORY_DIR       "/adm/daemons/story/"
#define TEMP_DIR        "/temp/"
#define SHADOW_DIR      "/shadow/"

// Daemons
#define ALIAS_D         "/adm/daemons/aliasd"
#define BACKUP_D        "/adm/daemons/backupd"
#define BAN_D           "/adm/daemons/band"
#define CHANNEL_D       "/adm/daemons/channeld"
#define CHAR_D          "/adm/daemons/chard"
#define CHINESE_D       "/adm/daemons/chinesed"
#define CLONE_D         "/adm/daemons/cloned"
#define CONFIG_D        "/adm/daemons/configd"
#define COMBAT_D        "/adm/daemons/combatd"
#define COMMAND_D       "/adm/daemons/commandd"
#define DANGPU_D        "/adm/daemons/dangpud"
#define DBASE_D         "/adm/daemons/dbased"
#define EMOTE_D         "/adm/daemons/emoted"
#define FACTION_D       "/adm/daemons/factiond"
#define FINGER_D        "/adm/daemons/fingerd"
#define FTP_D           "/adm/daemons/ftpd"
#define HEIDIAN_D       "/adm/daemons/heidiand"
#define HOUSE_D         "/adm/daemons/housed"
#define INQUIRY_D       "/adm/daemons/inquiryd"
#define KILLREWARD_D    "/adm/daemons/killreward"
#define LANGUAGE_D      "/adm/daemons/languaged"
#define LAZY_D			"/adm/daemons/lazyd"
#define LOGIN_D         "/adm/daemons/logind"
#define MAIL_D			"/adm/daemons/maild"
#define MONEY_D         "/adm/daemons/moneyd"
#define MESSAGE_D       "/adm/daemons/network/messaged"
#define NATURE_D        "/adm/daemons/natured"
#define NEWS_D          "/adm/daemons/newsd"
#define NPC_D           "/adm/daemons/npcd"
#define OTHER_D         "/adm/daemons/otherd"
#define PIG_D           "/adm/daemons/pigd"
#define PROFILE_D       "/adm/daemons/profiled"
#define PROTECT_D       "/adm/daemons/protectd"
#define RANK_D          "/adm/daemons/rankd"
#define REBOOT_D        "/adm/daemons/rebootd"
#define SECURITY_D      "/adm/daemons/securityd"
#define STORY_D         "/adm/daemons/storyd"
#define UPDATE_D        "/adm/daemons/updated"
#define VIRTUAL_D       "/adm/daemons/virtuald"
#define WEAPON_D        "/adm/daemons/weapond"
#define X_BOAT_D        "/adm/daemons/x_boatd"
#define X_PATH_D        "/adm/daemons/x_pathd"

#define QUEST_BEG_D(x)  ("/quest/beg/qbeg" + x)
#define CLASS_D(x)      ("/kungfu/class/" + x)
#define SKILL_D(x)      ("/kungfu/skill/" + x)
#define CONDITION_D(x)  ("/kungfu/condition/" + x)
#define PFM_D(x)        ("/kungfu/perform/" + x)

// Clonable/Non-inheritable Standard Objects
#define WTCORPSE_OB     "/clone/misc/wtcorpse"
#define PATE_OB         "/clone/misc/pate"
#define COIN_OB         "/clone/money/coin"
#define CORPSE_OB       "/clone/misc/corpse"
#define GOLD_OB         "/clone/money/gold"
#define LOGIN_OB        "/clone/user/login"
#define MASTER_OB       "/adm/obj/master"
#define MAILBOX_OB      "/clone/misc/mailbox"
#define SILVER_OB       "/clone/money/silver"
#define SIMUL_EFUN_OB   "/adm/obj/simul_efun"
#define USER_OB         "/clone/user/user"
#define VOID_OB         "/clone/misc/void"

// Inheritable Standard Objects
#define BANK            "/inherit/room/bank"
#define BULLETIN_BOARD  "/inherit/misc/bboard"
#define BOARDCAST_BOARD "/inherit/misc/wboard"
#define CHARACTER       "/inherit/char/char"
#define COMBINED_ITEM   "/inherit/item/combined"
#define EQUIP           "/inherit/misc/equip"
#define FORCE           "/inherit/skill/force"
#define ITEM            "/inherit/item/item"
#define LIQUID          "/inherit/food/liquid"
#define MONEY           "/inherit/item/money"
#define NPC             "/inherit/char/npc"
#define PILL            "/inherit/medicine/pill"
#define POWDER          "/inherit/medicine/powder"
#define ROOM            "/inherit/room/room"
#define DOOR            "/inherit/room/door"
#define NEWROOM         "/inherit/room/newroom"
#define SKILL           "/inherit/skill/skill"

// User IDs
#define ROOT_UID        "Root"
#define BACKBONE_UID    "Backbone"

// Features
#define F_ACTION        "/feature/action.c"
#define F_ALIAS         "/feature/alias.c"
#define F_APPRENTICE    "/feature/apprentice.c"
#define F_ATTACK        "/feature/attack.c"
#define F_ATTRIBUTE     "/feature/attribute.c"
#define F_AUTOLOAD      "/feature/autoload.c"
#define F_CLEAN_UP      "/feature/clean_up.c"
#define F_COMMAND       "/feature/command.c"
#define F_CONDITION     "/feature/condition.c"
#define F_DAMAGE        "/feature/damage.c"
#define F_DANGPU_LAOBAN "/feature/dangpu_laoban.c"
#define F_DBASE         "/feature/dbase.c"
#define F_DEALER        "/feature/dealer.c"
#define F_EDIT          "/feature/edit.c"
#define F_ENCODING      "/feature/encoding.c"
#define F_EQUIP         "/feature/equip.c"
#define F_FINANCE       "/feature/finance.c"
#define F_FOOD          "/feature/food.c"
#define F_HEIDIAN       "/feature/heidian.c"
#define F_HEIDIAN_HUOJI "/feature/heidian_huoji.c"
#define F_HOUSE         "/feature/house.c"
#define F_LIQUID        "/feature/liquid.c"
#define F_MASTER        "/inherit/char/master.c"
#define F_MESSAGE       "/feature/message.c"
#define F_MORE          "/feature/more.c"
#define F_MOVE          "/feature/move.c"
#define F_NAME          "/feature/name.c"
#define F_RIDE          "/feature/ride.c"
#define F_SAVE          "/feature/save.c"
#define F_SHADOW        "/feature/shadow.c"
#define F_SKILL         "/feature/skill.c"
#define F_TEAM          "/feature/team.c"
#define F_TREEMAP       "/feature/treemap.c"
#define F_VENDOR        "/feature/dealer.c"
#define F_SSERVER       "/feature/sserver.c"
#define F_UNIQUE        "/feature/unique.c"
#define F_VI            "/feature/vi"

// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#undef PROFILE_COMMANDS
