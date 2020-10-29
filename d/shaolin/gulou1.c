// Room: /d/shaolin/gulou1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鼓楼一层");
        set("long", @LONG
这里是塔楼的底层，一缕缕阳光从墙上的花砖缝隙里透射进来，
在青砖地上投下别致的光影，如同一格格棋盘相似。往上看，长长的
木楼梯盘绕而上，似乎永无尽头。墙角，梯级都相当洁净，看来经常
有僧人打扫。
LONG );
        set("exits", ([
                "up" : __DIR__"gulou2",
                "out" : __DIR__"gulou",
        ]));
        set("objects",([
                __DIR__"npc/saodi-seng" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
