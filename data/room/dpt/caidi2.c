// File(/data/room/dpt/caidi2.c) of dpt's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "游戏基地菜地");
	set ("long", @LONG
这片菜园子几畦地里种了一些时鲜蔬菜。另外有几个木桩搭起的
菜架子，供一些爬藤的蔬菜生长，不过你举目看去，老大的一片菜园
子，居然疏疏落落的没有几棵菜。 
LONG );

        set("exits", ([
                "west" : __DIR__"dayuan",
        ]));
        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "多炮塔");
        set("room_name", "游戏基地");
        set("room_id", "gamebase");
        set("room_owner_id", "dpt");
        set("room_position", "南海之滨");
}
