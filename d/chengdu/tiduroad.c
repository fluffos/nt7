// Room: tiduroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "提督街");
        set("long", @LONG
提督街就是因为通往提督府而得名。这一带来往行人很少，做生
意的就更是绝迹了。提督大人好象有甚麽想不开的，派了好多兵在这
里守卫，连江湖人物都不敢轻率踏入。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south"  : __DIR__"southroad2",
            "north"  : __DIR__"guangchang",
        ]));
        set("objects", ([
            "/d/city/npc/bing" : 3,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}