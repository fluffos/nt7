inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
顺山而走，山势渐渐陡了起来，杂草荆棘丛生， 使你难以行走。
LONG );
        set("exits", ([
                "southwest" : __DIR__"road5",
                "eastup" : __DIR__"qingshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -360);
        set("coor/y", -190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
