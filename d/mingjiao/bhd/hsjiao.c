// hsjiao.c 火山脚下
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIR"火山脚下"NOR);
        set("long", @LONG
你越走越热，不觉已至火山脚下。此时已可看到大火从火山中怒
喷而出，到这里你虽然是只穿单衣也是顶受不住，不觉已是口干舌燥，
遍身大汗，但见身旁已无一株树木花草，只余光秃秃、黄焦焦的岩石。
LONG );
	set("exits",([
		"east"	: __DIR__"ysroad2",
		"westup" : __DIR__"huoshan1",
	]));
	set("outdoor","冰火岛");
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "westup"){
	   me->set_leader(0);
           me->unconcious();
        }
        return ::valid_leave(me, dir); 
}
