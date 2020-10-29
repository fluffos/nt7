#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",CYN"中区东路"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "east":__DIR__"ce5",
         "west":__DIR__"ce3",
        ]));        
        setup();
}