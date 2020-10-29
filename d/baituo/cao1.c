inherit ROOM;

void create()
{
        set("short", "草丛");
        set("long", @LONG
这里是乱草丛。东边是扇拱月形小敞门。其余三面都是齐腰高的
蒿草，常有蛇出没。
LONG );
        set("exits", ([
                "west" : __FILE__,
                "north" : __DIR__"cao2",
                "east" : __DIR__"ximen",
                "south" : __FILE__,
        ]));
        set("objects", ([
                "/clone/beast/jinshe" : random(2),
        ]));
        set("quarrys", ([
                "caihuashe"  : 100000,
                "dushe"      : 50000,
                "jinshe"     : 40000,
                "qingshe"    : 40000,
                "yanjingshe" : 5000,
                "mangshe"    : 3000,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -50000);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
