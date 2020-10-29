// Room: northroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在北大街的青石地上，发现这里热闹非凡。原来东北角就是
金牛武馆，据说每个武师都有绝活。许多江湖人物都慕名前来，搬运
行李被褥的人不绝如缕。往东南是东大街，一直向西的是北大街。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "west"       : __DIR__"northroad2",
            "southeast"  : __DIR__"eastroad1",
            "northeast"  : __DIR__"wuguan",
        ]));
        set("objects", ([
            "/d/huashan/npc/haoke" : 2,
            "/d/taishan/npc/jian-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}