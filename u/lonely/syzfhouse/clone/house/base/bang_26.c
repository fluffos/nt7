
inherit "/inherit/room/house_base";

void create()
{
    set("short", "山间草地");
    set("long", @LONG
此间位于石经峪西侧。放眼望去，一片青翠之中点缀着星星点点
的野花，或粉白或蕊黄或奼紫或嫣红，煞是好看。一座黛瓦粉墙的山
庄设在草地一头，好像是江湖中哪个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/taishan/shijin",
    ]));

    set("outdoors", "taishan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
