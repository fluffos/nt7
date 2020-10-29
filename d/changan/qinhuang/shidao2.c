// This is a room made by wsl.

inherit ROOM;

void create()
{
    set("short", "石道");
        set("long", @LONG
这是一条阴森的道路，四周是一个个的俑坑，还有无数的骸骨，
看来秦始皇建好这座陵墓后，把全部的施工者都杀死在这里了，你只
觉得有点毛骨悚然。
LONG );
        set("exits", ([
           "west":__DIR__"swordroom",
           "north":__DIR__"shidao3",
           "east":__DIR__"uroom",
]));
        set("objects", ([
            __DIR__"obj/skeleton" : 1+random(10),
]));
    setup();
}