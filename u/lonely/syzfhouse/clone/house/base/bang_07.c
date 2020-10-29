
inherit "/inherit/room/house_base";

void create()
{
    set("short", "西山脚下");
    set("long", @LONG
西山龙门为西南一绝景，此处位于西山的山脚之下，一条崎岖的
山路蜿蜒曲折，通向远处好大的一片宅院，看上去似乎并非西山附近
常见的庙宇，而象是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east" : "/d/dali/xishan-lu",
    ]));

    set("outdoors", "dali");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
