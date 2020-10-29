#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山顶");
        set("long", @LONG
这里是一座高山的山顶，临江一面是陡峭的悬崖，仔细望去，有
一些石窝可以落脚，西看去，只见云雾中有好象有几栋房子。
LONG );
        set("exits", ([
                  "eastdown" :  __DIR__"shudao8",
                "west" : __DIR__"shudao10",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15070);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}