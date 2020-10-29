
inherit "/inherit/room/house_base";

void create()
{
    set("short", "侯监集丁号");
    set("long", @LONG
这里位于侯监集南侧一条行人稀少的幽长小巷之内，四周聚集着
很多的民宅，安静而优雅。街道两侧划分出了一个个的地块，供来自
各地的英雄豪杰们在此修筑豪宅美院。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"houjianji_03",
        "south" : __DIR__"houjianji_08",
    ]));

    set("outdoors", "houjianji");
    set("max_build", 4);
    set("can_build", "user");

    setup();
    restore();
}
