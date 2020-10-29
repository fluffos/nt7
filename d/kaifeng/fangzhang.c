inherit ROOM;

void create()
{
        set("short", "方丈室");
        set("long", @LONG
方丈室内的陈设相对来说比较简单，正中的墙面上写着个大大的
『佛』字。地上铺着一张大席子，一张矮几就放在席子中间。两边是
两个锦垫。在靠里面的地方，有个蒲团，边上是个小木鱼，据说方丈
大师每天只需打坐片刻就精力充沛。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([
                  __DIR__"npc/zhiqing" : 1,
        ]));

	set("coor/x", -5020);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}