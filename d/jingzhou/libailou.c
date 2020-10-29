inherit ROOM;

void create()
{
        set("short", "饭馆");
        set("long", @LONG
这是一家湘西的小饭馆，布置颇为简易，顾客多是匆匆的行人，
买点包子、鸡腿、米酒就赶路去了。
LONG );
        set("exits", ([
                "west" : __DIR__"beidajie2",
               ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x", -450);
        set("coor/y", -180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
