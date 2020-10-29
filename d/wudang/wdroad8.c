inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
这里是陕西境内。一条静悄悄的黄土路，两旁有些小土屋，疏疏
落落的。但路上行人很少，都行色匆匆向前赶路。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "northeast" : __DIR__"wdroad7",
                "west"      : __DIR__"sanbuguan",
        ]));
        set("objects", ([
                __DIR__"obj/shitou":1,
        ]));
        set("coor/x", -320);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
