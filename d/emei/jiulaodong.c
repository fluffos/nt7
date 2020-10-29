inherit ROOM;

void create()
{
        set("short", "九老洞");
        set("long", @LONG
这就是峨嵋第一大洞，洞内深窈无比，神秘难测。你一走进来，
便发觉洞中叉洞多如迷宫，怪异莫测似乎黝黑无底。还是快快离开吧。
LONG );
        set("objects", ([
                "/clone/quarry/fu" : 4,
        ]));
        set("exits", ([
                "out"   : __DIR__"jldongkou",
                "north" : __DIR__"jldongnei",
        ]));
        set("coor/x", -520);
        set("coor/y", -250);
        set("coor/z", 130);
        set("coor/x", -520);
        set("coor/y", -250);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}