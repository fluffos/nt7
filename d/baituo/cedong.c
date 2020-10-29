inherit ROOM;

void create()
{
        set("short", "侧洞");
        set("long", @LONG
这里是一个小小的侧洞，里面有张梳妆台，上边凌乱的摆放着些
女人的用品。
LONG );
        set("exits", ([
                "east" : __DIR__"dongnei",
        ]));
        set("objects", ([
                __DIR__"npc/jinhua" : 1,
        ]));
        set("coor/x", -49960);
        set("coor/y", 20050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}