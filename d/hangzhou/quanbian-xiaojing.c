// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "泉边小径");
        set("long", @LONG
绕过玉泉，眼前出现一条蜿蜒的曲径。人在窄窄的山道上行走，
两旁是青翠的林木，头顶是掩映的花树，略带松脂香味的湿润空气轻
轻地散逸着，微风吹过，林颤云摇，时不时传来的声声鸟语，更衬托
出这片山谷的清幽静寂。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/shandao1",
                "south" : "/d/hangzhou/yuquan",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}