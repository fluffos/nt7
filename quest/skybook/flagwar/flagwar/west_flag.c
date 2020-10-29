#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"西区旗点"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "east" :__DIR__"cw5",
       	 "southeast":__DIR__"bnw5",
       	 "northeast":__DIR__"rsw5",
        ]));        
        setup();
}