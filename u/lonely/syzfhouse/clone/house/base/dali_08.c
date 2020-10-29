inherit "/inherit/room/house_base";

void create()
{
    set("short", "镇南街辛号");
    set("long", @LONG
这是位于镇南街畔的新辟住宅区，四周绿树成荫，藤蔓垂依，阻
隔了喧闹的人声，环境颇为优雅，静谧而闲适。沿着街道划出了不少
地块，供来自各地的大富豪们在此修筑豪宅美院。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"dali_07",
        "north" : __DIR__"dali_06",
    ]));

    set("outdoors", "dali");
    set("max_build", 4);
    set("can_build", "user");

    setup();
    restore();
}