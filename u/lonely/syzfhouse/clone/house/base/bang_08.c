
inherit "/inherit/room/house_base";

void create()
{
    set("short", "得胜山侧");
    set("long", @LONG
这里是扬州的东城门郊外，再向东便通向得胜山了。从这里看去
山上山下树木长得特别茂盛，平时行人稀少。北面座落着好大的一片
宅院，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "southeast" : "/d/city/jiaowai",
    ]));

    set("outdoors", "city");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
