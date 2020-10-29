inherit ROOM;

void create()
{
        set("short", "岔路");
        set("long", @LONG
这是一条小岔路，东面不远是唐家堡的主路，不是还能看到
几个行色匆匆的人来往，西面是高耸的山壁，一条羊肠小路沿着
山壁弯弯曲曲的向远方延伸。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
        "northwest" : __DIR__"ycl1",
        "east" : __DIR__"gd2",
        "west" : __DIR__"syang",
        "south" : __DIR__"tuzai1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
