
inherit "/inherit/room/house_base";

void create()
{
    set("short", "山间松林");
    set("long", @LONG
这里树木参天，鸟语阵阵，倒是清静所在。山高风自凉，林中穿
行，自觉松涛阵阵，时如古韵琴声，时如溪水潺潺，时如旷野放歌，
时如浊浪排空，四时不同。松林深处一处庄院，好像是江湖中哪个帮
会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/qingcheng/xionger-shan",
    ]));

    set("outdoors", "qingcheng");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
