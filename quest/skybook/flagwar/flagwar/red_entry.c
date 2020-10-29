#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"红队起点"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        set("stab_flag", 1);
        set("party","red");
        set("exits",([
         "south":__DIR__"rc1",
         "southeast":__DIR__"rse1",
         "southwest":__DIR__"rsw1",		         	
        ]));        
        setup();
}
void open_exit() {
        set("exits",([
         "south":__DIR__"rc1",
         "southeast":__DIR__"rse1",
         "southwest":__DIR__"rsw1",		         	
        ]));    
}