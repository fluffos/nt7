inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
这里是陕西境内的一条静悄悄的黄土路，两旁有些小土屋，疏疏
落落的。路上行人很少，都行色匆匆地向前赶路。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
            "south"      : __DIR__"house",
            "southeast"  : __DIR__"wdroad5",
            "west"       : __DIR__"wdroad7",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -300);
        set("coor/y", -150);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
