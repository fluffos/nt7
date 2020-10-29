// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "山道");
        set("long", @LONG
你正漫步在一条蜿蜒的山道上，两边繁茂的树木散发出淡淡的宜
人的气息，溪流在沟谷中流淌，水声潺潺如幻。花香满径，山光树色，
绿影葱茏，辉映成画。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/shandao2",
                "west"  : "/d/hangzhou/wenxin-quan",
                "south" : "/d/hangzhou/quanbian-xiaojing",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}