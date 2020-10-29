
inherit "/inherit/room/house_base";

void create()
{
    set("short", "安定门外");
    set("long", @LONG
安定门外是一条宽阔笔直的大道，通向北京城外的远方，路上的
景色显得萧瑟得许多，那是进入更北方的显兆。回头看看南方，还能
看见北京城高大的城墙和门楼。道旁有一片宅院，看上去似乎是某个
帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east" : "/d/shanhai-guan/guandao1",
    ]));

    set("outdoors", "beijing");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
