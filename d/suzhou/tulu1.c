// Room: /d/suzhou/tulu1.c
// Last Modified by Lonely on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long",@long
你来到了一条土路上，西南边不远好象有条江。北边是去苏州的官
道。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "north"     : __DIR__"road4",
                "southwest" : __DIR__"tulu2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1050);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}