#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"红队西路"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "southwest":__DIR__"rsw4",
         "northeast":__DIR__"rsw2",
        ]));        
        setup();
}