
inherit "/inherit/room/house_base";

void create()
{
    set("short", "永定街辛号");
    set("long", @LONG
永定东街位于京城之南，永定门内大街的东部。街道两侧划出了
很多地块，供来自各地的大富豪们在此修筑豪宅美院。青石板铺就的
道路颇为宽阔，扫洗得光可鉴人。路两旁绿树成荫，掩映着其间的一
栋栋民宅，显得安静而优雅。
LONG);

    set("exits",
    ([
        "north" : "/d/beijing/yongding-dongjie4",
        "west"  : __DIR__"beijings_06",
    ]));

    set("outdoors", "beijing-s");
    set("max_build", 4);
    set("can_build", "user");

    setup();
    restore();
}
