//Room: xiaojia-qianyuan.c

inherit ROOM;
void create ()
{
        set ("short", "萧家前院");
        set("long", @LONG
没想好呢！呵呵！
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/liande-dadao5",
                "east" : "/d/changan/xiaojiadt",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/guanjia" : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10670);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}