// globals.h
// this file will be automatically included by the driver

#ifndef __SENSIBLE_MODIFIERS__
#define nosave          static
#define protected       static
#endif

#ifndef  __PACKAGE_LONELY__
#include "winconf.h"
#else
#include "unixconf.h"
#endif

#define NO_FEE
#define BUSY_MESSAGE     "你现在忙得很，无法做任何事情。\n"
#define DEBUG_CHANNEL(x) CHANNEL_D->channel_broadcast("debug", "调试精灵："+(string)x)
//#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "I2D 精灵："+(string)x)

// Important directories
#define INC_DIR                 "/include/"
#define BACKUP_DIR              "/backup/"
#define COMMAND_DIR             "/cmds/"
#define CONFIG_DIR              "/adm/etc/"
#define DATA_DIR                "/data/"
#define DUMP_DIR                "/dump/"
#define EVENT_DIR               "/adm/daemons/event/"
#define GROUP_QUEST_DIR         "/adm/daemons/group_quest/"
#define HELP_DIR                "/help/"
#define ITEM_DIR                "/data/item/"
#define LOG_DIR                 "/log/"
#define QUEST_DIR               "/adm/daemons/quest/"
#define SHADOW_DIR              "/shadow/"
#define STORY_DIR               "/adm/daemons/story/"
#define ARMOR_DIR               "/clone/armor/"              //护具
#define WEAPON_DIR              "/clone/weapon/"             //兵器
#define BOOK_DIR                "/clone/book/"               //书籍
#define MONEY_DIR               "/clone/money/"              //货币
#define ANIMAL_DIR              "/clone/animal/"             //动物
#define JEWELRY_DIR             "/clone/jewelry/"            //珠宝
#define FOOD_DIR                "/clone/food/"               //食物
#define FRUIT_DIR               "/clone/food/fruit/"         //水果
#define LIQUID_DIR              "/clone/food/liquid/"        //饮料
#define TEA_DIR                 "/clone/food/tea/"           //茶水
#define FODDER_DIR              "/clone/food/fodder/"        //饲料
#define CLOTH_DIR               "/clone/cloth/"              //衣服
#define HEAD_DIR                "/clone/cloth/head/"         //盔帽
#define BOOT_DIR                "/clone/cloth/boot/"         //鞋靴
#define NOSTRUM_DIR             "/clone/medicine/nostrum/"   //成药
#define POISON_DIR              "/clone/medicine/poison/"    //毒药
#define VEGETABLE_DIR           "/clone/medicine/vegetable/" //草药
#define SHOP_DIR                "/clone/shop/"               //商店
#define TEMP_DIR                "/temp/"
#define TEMPLATE_DIR            "/template/"
#define WORK_DIR                "/adm/daemons/work/"

// Daemons
#define ABILITY_D               "/adm/daemons/abilityd"
#define ACTION_D                "/adm/daemons/actiond"
#define AHACK_D                 "/adm/daemons/ahackerd"
#define ALIAS_D                 "/adm/daemons/aliasd"
#define ANALECTA_D              "/adm/daemons/analectad"
#define ARENA_D                 "/adm/daemons/arenad"
#define BAN_D                   "/adm/daemons/band"
#define BACKUP_D                "/adm/daemons/backupd"
#define BATTLEFIELD_D           "/adm/daemons/battlefieldd"
#define BOARD_D                 "/adm/daemons/boardd"
#define ANNIE_D                 "/adm/daemons/buffd"
#define BUFF_D                  "/adm/daemons/buffd"
#define BUSINESS_D              "/adm/daemons/businessd"
#define BUNCH_D                 "/adm/daemons/bunchd"
#define CHANNEL_D               "/adm/daemons/channeld"
#define CHAR_D                  "/adm/daemons/chard"
#define CHINESE_D               "/adm/daemons/chinesed"
#define CLOSE_D                 "/adm/daemons/closed"
#define COMBAT_D                "/adm/daemons/combatd"
#define COMPETE_D               "/adm/daemons/competed"
#define COMMAND_D               "/adm/daemons/commandd"
#define CONFIG_D                "/adm/daemons/configd"
#define CONTEST_D               "/adm/daemons/contestd"
#define CPU_D                   "/adm/daemons/cpud"
#define CRON_D                  "/adm/daemons/crond"
#define CRUISE_D                "/adm/daemons/cruised"
#define DATABASE_D              "/adm/daemons/databased"
#define DBASE_D                 "/adm/daemons/dbased"
#define BBASE_D                 "/adm/daemons/bbased"
#define DB_D                    "/adm/daemons/dbd"
#define EMOTE_D                 "/adm/daemons/emote_d"
#define EQUIPMENT_D             "/adm/daemons/equipmentd"
#define EVENT_D                 "/adm/daemons/eventd"
#define EXAMINE_D               "/adm/daemons/examined"
#define FAMILY_D                "/adm/daemons/familyd"
#define FESTIVAL_D              "/adm/daemons/festivald"
#define FINGER_D                "/adm/daemons/fingerd"
#define FTP_D                   "/adm/daemons/ftpd"
#define FUBEN_D                 "/adm/daemons/fubend"
#define GIFT_D                  "/adm/daemons/giftd"
#define GROUP_QUEST_D           "/adm/daemons/group_questd"
#define HISTORY_D               "/adm/daemons/historyd"
#define HTML_D                  "/adm/daemons/html_d"
#define IDENTIFY_D              "/adm/daemons/identifyd"
#define INQUIRY_D               "/adm/daemons/inquiryd"
#define INTERMUD2_D             "/adm/daemons/intermud2_d"
#define ITEM_D                  "/adm/daemons/itemd"
#define LEAGUE_D                "/adm/daemons/leagued"
#define LANGUAGE_D              "/adm/daemons/languaged"
#define LOGIN_D                 "/adm/daemons/logind"
#define MAIL_D                  "/adm/daemons/maild"
#define MAP_D                   "/adm/daemons/mapd"
#define MASTER_D                "/adm/daemons/masterd"
#define MAZE_D                  "/adm/daemons/mazed"
#define MEMBER_D                "/adm/daemons/memberd"
#define MESSAGE_D               "/adm/daemons/network/messaged"
#define MODULE_D                "/adm/daemons/moduled"
#define MONEY_D                 "/adm/daemons/moneyd"
#define MONITOR_D               "/adm/daemons/monitord"
#define MONEY_D                 "/adm/daemons/moneyd"
#define MINE_D			"/adm/daemons/mined"
#define MRTG_D                  "/adm/daemons/mrtgd"
#define MUDLIST_D               "/adm/daemons/mudlistd"
#define MYGIFT_D                "/adm/daemons/mygiftd"
#define NAME_D                  "/adm/daemons/named"
#define NAMES_D                 "/adm/daemons/namesd"
#define NATURE_D                "/adm/daemons/natured"
#define NPC_D                   "/adm/daemons/npcd"
#define NEWS_D                  "/adm/daemons/newsd"
#define NUMBER_D                "/adm/daemons/numberd"
#define PARTY_QUEST_D           "/adm/daemons/party_questd"
#define PK_D                    "/adm/daemons/pkd"
#define PIG_D                   "/adm/daemons/pigd"
#define PROFILE_D               "/adm/daemons/profiled"
#define QUEST_D                 "/adm/daemons/questd"
#define XYWAR_D                 "/adm/daemons/xyward"
#define X_NameD                 "/adm/daemons/x_named"
#define X_PointD                "/adm/daemons/x_pointd"
#define X_QuestD                "/adm/daemons/x_questd"
#define RANK_D                  "/adm/daemons/rankd"
#define REALNEWS_D              "/adm/daemons/realnewsd"
#define SOCKET_D                "/adm/daemons/socketd"
#define SCHEDULE_D              "/adm/daemons/scheduled"
#define SECURITY_D              "/adm/daemons/securityd"
#define SERIAL_NUMBER_D         "/adm/daemons/serial_numberd"
#define SHOP_D                  "/adm/daemons/shopd"
#define SKILLS_D                "/adm/daemons/skillsd"
#define SKYBOOK_D               "/adm/daemons/skybookd"
#define SMTP_D                  "/adm/daemons/smtpd"
#define SYSTEM_D                "/adm/daemons/systemd"
#define SCBORN_D                "/adm/daemons/scbornd"
#define STOCK_D                 "/adm/daemons/stockd"
#define STORY_D                 "/adm/daemons/storyd"
#define TASK_D                  "/adm/daemons/taskd"
#define TEMPLATE_D              "/adm/daemons/templated"
#define TIME_D                  "/adm/daemons/timed"
#define TOPTEN_D                "/adm/daemons/toptend"
#define ULTRA_QUEST_D           "/adm/daemons/ultra_questd"
#define UPDATE_D                "/adm/daemons/updated"
#define VERSION_D               "/adm/daemons/versiond"
#define VIRTUAL_D               "/adm/daemons/virtuald"
#define VRM_SERVER              "/adm/daemons/vrm_server"
#define WAR_D                   "/adm/daemons/ward"
#define WEAPON_D                "/adm/daemons/weapond"
#define WORK_D                  "/adm/daemons/workd"
#define XINRUI_D                "/adm/daemons/xinruid"
#define ZHOUTIAN_D              "/adm/daemons/zhoutiand"

#define CLASS_D(x)              ("/kungfu/class/" + x)
#define CONDITION_D(x)          ("/kungfu/condition/" + x)
#define DRUG_D(x)               ("/clone/drug/" + x)
#define SKILL_D(x)              ("/kungfu/skill/" + x)
#define SPECIAL_D(x)            ("/kungfu/special/" + x)

// Added for questing
#define QUESTH_D(x)             ("/quest/qhlist" + x)
#define QUESTS_D(x)             ("/quest/qslist" + x)
#define QUESTW_D(x)             ("/quest/qwlist" + x)

// Clonable/Non-inheritable Standard Objects
#define COIN_OB                 "/clone/money/coin"
#define CORPSE_OB               "/clone/misc/corpse"
#define EXPLIST                 "/clone/quest/explist"
#define GOLD_OB                 "/clone/money/gold"
#define LOGIN_OB                "/clone/user/login"
#define MASTER_OB               "/adm/kernel/master"
#define SIMUL_EFUN_OB           "/adm/kernel/simul_efun"
#define SILVER_OB               "/clone/money/silver"
#define TEMP_OB                 "/clone/misc/temp"
#define THGOLD_OB               "/clone/money/thousand-gold"
#define THCASH_OB               "/clone/money/thousand-cash"
#define USER_OB                 "/clone/user/user"
#define VOID_OB                 "/clone/misc/void"

// Inheritable Standard Objects
#define BANK                    "/inherit/room/bank"
#define BABY                    "/inherit/char/baby"
#define BOSS                    "/inherit/char/boss"
#define BOOK                    "/inherit/item/book"
#define BAOXIANG_ITEM           "/inherit/item/baoxiang"
#define BUILD_ROOM              "/inherit/room/buildroom"
#define BULLETIN_BOARD          "/inherit/misc/bboard"
#define BULLETIN_JBOARD         "/inherit/misc/jboard"
#define BUNCHER                 "/inherit/char/buncher"
#define CHALLENGER              "/inherit/char/challenger"
#define CHARACTER               "/inherit/char/char"
#define COMBINED_ITEM           "/inherit/item/combined"
#define CHOUQIAN                "/inherit/misc/chouqian"
#define DEMONROOM               "/inherit/room/demonroom"
#define DATABASE_BOARD          "/inherit/misc/dboard"
#define DREAM_NPC               "/inherit/char/dream_npc"
#define EQUIP                   "/inherit/misc/equip"
#define EQUIP_SOUL              "/inherit/item/equipsoul"
#define FIGHTER                 "/inherit/char/fighter"
#define FORCE                   "/inherit/skill/force"
#define HOCKSHOP                "/inherit/room/hockshop"
#define ILLNESS                 "/inherit/condition/illness"
#define ITEM                    "/inherit/item/item"
#define KNOWER                  "/inherit/char/knower"
#define LIQUID                  "/inherit/food/liquid"
#define MONEY                   "/inherit/item/money"
#define NPC                     "/inherit/char/npc"
#define NPC_SAVE                "/inherit/char/npcsave"
#define NPC_TRAINEE             "/inherit/char/trainee"
#define WAITER                  "/inherit/char/waiter"
#define PIG_ROOM                "/inherit/room/pigroom"
#define PILL                    "/inherit/medicine/pill"
#define POWDER                  "/inherit/medicine/powder"
#define POISON                  "/inherit/condition/poison"
#define POISON_INSECT           "/inherit/char/insect"
#define PRIVATE_ROOM            "/inherit/room/privateroom"
#define QUARRY                  "/inherit/char/quarry"
#define QUEST                   "/inherit/quest"
#define RESTROOM_IN             "/inherit/room/restroom_in"
#define RESTROOM_OUT            "/inherit/room/restroom_out"
#define RIVER                   "/inherit/room/river"
#define ROOM                    "/inherit/room/room"
#define SHAOLIN_SKILL           "/inherit/skill/shaolin"
#define SHOP                    "/inherit/room/shop"
#define SKILL                   "/inherit/skill/skill"
#define SKI_ZHEN                "/inherit/skill/array"
#define SMITH                   "/inherit/char/smith"
#define SNAKE                   "/inherit/char/snake"
#define TASK                    "/inherit/item/task"
#define TESSERA                 "/inherit/item/tessera"
#define WAREHOUSE               "/inherit/room/warehouse"
#define WORM                    "/inherit/char/worm"
#define SKILL_MODEL_UNARMED     "/inherit/meskill/skill_model_unarmed.c"
#define SKILL_MODEL_WEAPON      "/inherit/meskill/skill_model_weapon.c"
#define SKILL_MODEL_DEFAULT     "/inherit/meskill/skill_model_default.c"

#define MENGZHU                 "/adm/npc/meng-zhu"
#define FAE                     "/adm/npc/fa-e"
#define SHANGSHAN               "/adm/npc/shang-shan"

// User IDs

#define ROOT_UID                "Root"
#define BACKBONE_UID            "Backbone"

// Features

#define F_ACTION                "/feature/action.c"
#define F_ALIAS                 "/feature/alias.c"
#define F_APPRENTICE            "/feature/apprentice.c"
#define F_ATTACK                "/feature/attack.c"
#define F_ATTRIBUTE             "/feature/attribute.c"
#define F_AUTOLOAD              "/feature/autoload.c"
#define F_BACKUP                "/feature/backup.c"
#define F_DTIME			"/feature/dtime.c"
#define F_BANKER                "/feature/banker.c"
#define F_BUSINESS              "/feature/business.c"
#define F_CLEAN_UP              "/feature/clean_up.c"
#define F_COAGENT               "/feature/coagent.c"
#define F_COMMAND               "/feature/command.c"
#define F_CONDITION             "/feature/condition.c"
#define F_CUTABLE               "/feature/cutable.c"
#define F_DAMAGE                "/feature/damage.c"
#define F_DBASE                 "/feature/dbase.c"
#define F_DEALER                "/feature/dealer.c"
#define F_EDIT                  "/feature/edit.c"
#define F_EQUIP                 "/feature/equip.c"
#define F_EQUIP_LIV             "/feature/equip_liv.c"
#define F_FINANCE               "/feature/finance.c"
#define F_FOOD                  "/feature/food.c"
#define F_FRUIT                 "/feature/fruit.c"
#define F_GUARDER               "/feature/guarder.c"
#define F_ITEMMAKE              "/feature/itemmake.c"
#define F_LIQUID                "/feature/liquid.c"
#define F_MASTER                "/inherit/char/master.c"
#define F_MANAGER               "/inherit/char/manager.c"
#define F_FIRST                 "/inherit/char/first.c"
#define F_MESSAGE               "/feature/message.c"
#define F_MORE                  "/feature/more.c"
#define F_MOVE                  "/feature/move.c"
#define F_NAME                  "/feature/name.c"
#define F_NOCLONE               "/feature/noclone.c"
#define F_NATURE                "/feature/nature.c"
#define F_OBSAVE                "/feature/obsave.c"
#define F_QUESTER               "/feature/quester.c"
#define F_QUEST                 "/feature/quest.c"
#define F_SAVE                  "/feature/save.c"
#define F_SHADOW                "/feature/shadow.c"
#define F_SHELL                 "/feature/shell.c"
#define F_SILENTDEST            "/feature/silentdest.c"
#define F_SKILL                 "/feature/skill.c"
#define F_SSERVER               "/feature/sserver.c"
#define F_TEAM                  "/feature/team.c"
#define F_TREEMAP               "/feature/treemap.c"
#define F_TRANSPORT             "/feature/transport.c"
#define F_VENDOR                "/feature/dealer.c"
#define F_VI                    "/feature/vi.c"
#define F_UNIQUE                "/feature/unique.c"
#define F_XIAO                  "/inherit/misc/_xiao.c"

// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#define SAVE_EXTENSION          ".o"
#define FILE_EXTENSION          ".c"

// Install information
#define INSTALL_COMBAT_TEST     1

#undef PROFILE_COMMANDS
#undef COUNT_COMMAND_TIMECOST
