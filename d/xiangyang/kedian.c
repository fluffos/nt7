// Room: /d/xiangyang/kedian.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "襄阳客栈");
        set("long", @LONG
这是一家对江湖人士来说很有名气的客栈。人们到襄阳来一般都
住在这里，一是便宜，二能听到江湖上的许多事情。近年来，襄阳退
敌数十次，南来北往的人们经过襄阳更是打尖在这儿，顺便拜访一下
郭靖等侠义之士。
LONG );
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("valid_startroom", 1);

        set("exits", ([
                "east" : __DIR__"westroad1",
        ]));
        set("objects", ([
                __DIR__"npc/wudunru" : 1,
        ]));
        set("coor/x", -7850);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}