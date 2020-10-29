//Room: xiaojia-sleep.c

inherit ROOM;

void create ()
{
        set ("short", "卧室");
        set("long", @LONG
没想好呢！呵呵！
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/xiaojiadt",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yahuan" : 1,
        ]));

        set("coor/x", -10660);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}