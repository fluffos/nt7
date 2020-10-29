#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"东区旗点"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "west" :__DIR__"ce5",
         "southwest":__DIR__"bne5",
         "northwest":__DIR__"rse5",
        ]));        
        setup();
}