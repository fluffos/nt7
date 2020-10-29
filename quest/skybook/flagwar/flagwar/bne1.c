#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"蓝队东路"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northeast":__DIR__"bne2",
         "southwest":__DIR__"blue_entry",
        ]));        
        setup();
}