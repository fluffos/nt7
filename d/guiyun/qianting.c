// Room: /d/guiyun/qianting.c
// Last Modified by Lonely on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","前厅");
        set("long",@LONG
这是归云庄的前厅。平常招待客人都在这里进行。厅中陈设华美，
雕梁画栋，极穷巧思。
LONG
);
        set("objects",([
                __DIR__"npc/zhuangding1" : 2,
        ]));  
        set("exits",([
                "east" : __DIR__"dayuan",
                "west" : __DIR__"zhongting",
        ]) );
        set("no_clean_up",0);
        set("coor/x", 270);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}