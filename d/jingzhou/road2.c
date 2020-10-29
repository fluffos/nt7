inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
这是一条青石大道。东面隐约可以看到襄阳城的城墙。向西看去，
只见群山起伏，青翠碧绿，不知通向哪里。
LONG );
        set("exits", ([
                "northeast" : __DIR__"road1",
                "southwest" : __DIR__"road3",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "city");

        set("coor/x", -310);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
