
inherit "/inherit/room/house_base";

void create()
{
    set("short", "钻天坡");
    set("long", @LONG
此处背依“一线天”，坡势甚缓，古木参天自成一林。燕雀欢鸣
林间，流泉飞瀑林外。林中浅雾略现迷蒙，一条穿林小径曲折通向树
林深处。林深处依稀见一座青砖黛瓦的大宅院，似为某个帮会驻地之
所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/emei/taohua-wu",
    ]));

    set("outdoors", "emei");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
