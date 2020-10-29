// File(/data/room/blz/caidi2.c) of blz's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "逍遥洞菜地");
	set ("long", @LONG
这片菜园子几畦地里种了一些时鲜蔬菜。另外有几个木桩搭起的
菜架子，供一些爬藤的蔬菜生长，不过你举目看去，老大的一片菜园
子，居然疏疏落落的没有几棵菜。 
LONG );

        set("exits", ([
                "west" : __DIR__"dayuan",
        ]));
        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "暴雪");
        set("room_name", "逍遥洞");
        set("room_id", "blz");
        set("room_owner_id", "blz");
        set("room_position", "青砖路");
}
