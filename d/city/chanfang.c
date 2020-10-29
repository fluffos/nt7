// Room: chanfang.c
#include <ansi.h>  
inherit ROOM;

void create()
{
        set("short",HIW"扬州产房"NOR);
        set("long", @LONG
这是一间专门为孕妇准备的产房，你的妻子要生Baby就赶快来哟。
LONG );
        set("no_fight",1);
        set("no_sleep_room",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_study",1);
        set("no_yun",1);

        set("exits", ([
           "down":  __DIR__"yaopu"
        ]));

	set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
}