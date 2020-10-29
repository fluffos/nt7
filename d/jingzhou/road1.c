inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向脂粉
之都的襄阳，折向西南则通往西南重镇荆洲。
LONG );
        set("exits", ([
                "northeast" : "/d/xiangyang/caodi6",
                "southwest" : __DIR__"road2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "city");

        set("coor/x", -300);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
