#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"红队东路"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "southeast":__DIR__"rse2",
         "northwest":__DIR__"red_entry",
        ]));        
        setup();
}