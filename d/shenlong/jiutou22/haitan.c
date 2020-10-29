#include <ansi.h>
inherit ROOM;

void home(object ob);

void create()
{
        set("short", "海滩");
        set("long", @LONG
你被一阵风吹得头晕目眩，似乎又回到了海滩。
LONG);


        setup();
}

void init()
{

	this_player()->move("/d/shenlong/haitan");
}
