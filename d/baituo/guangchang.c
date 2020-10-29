inherit ROOM;

void create()
{
        set("short", "广场");
        set("long", @LONG
这里是一块不小的广场，上面堆着农家晒的谷物。北上是白驼山
庄。东面有间小农舍，西边有块菜地，南方是一座小桥。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "east"    : __DIR__"nongshe",
                "northup" : __DIR__"shijie",
                "west"    : __DIR__"shanlu",
                "south"   : __DIR__"bridge",
        ]));
        set("objects",([
                __DIR__"npc/kid" : 2,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}