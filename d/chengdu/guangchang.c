// Room: guangchang.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "蜀都广场");
        set("long", @LONG
这里是成都提督府前广场。好空旷的地方，只有稀稀落落几个没
精打采的行人。北面就是提督府了，南边是提督街。广场周围种了一
圈遮阳树，但骄阳仍把青石广场地面晒得滚烫冒烟。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"  : __DIR__"shuduroad1",
            "west"  : __DIR__"shuduroad2",
            "south" : __DIR__"tiduroad",
            "north" : __DIR__"tidugate",
        ]));
//        set("no_clean_up", 0);
        set("objects", ([
            "/d/city/npc/wujiang" : 2,
                "/clone/npc/walker"  : 1, 
        ]));
        set("coor/x", -15220);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}