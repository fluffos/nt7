
inherit "/inherit/room/house_base";

void create()
{
    set("short", "南湖柳岸");
    set("long", @LONG
这里是南湖水岸，湖畔柔柳如烟。独立柳下可见南湖旖旎风光。
最是阴雨天气，烟霭似纱，雨丝如雾。岸边不远处有一处青瓦粉墙的
崭新大院，好像是江湖某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "south"  : "/d/fuzhou/nanhu1",
    ]));

    set("outdoors", "fuzhou");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
