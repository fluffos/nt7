// File(/data/room/dpt/dayuan.c) of dpt's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "游戏基地大院");
	set ("long", @LONG
这是一个宽阔的院落，种着各种树木，阳光照下来透过树荫投下
层层影子。一条大路通向里面，踩得非常平滑的，看来是经常有人来
往。 
LONG );

        set("exits", ([
                "north"  : __DIR__"qianting",
                "east"   : __DIR__"caidi2",
                "west"   : __DIR__"caidi1",
                "out"    : "/d/xiakedao/haibin",
        ]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "多炮塔");
        set("room_name", "游戏基地");
        set("room_id", "gamebase");
        set("room_owner_id", "dpt");
        set("room_position", "南海之滨");
}
