#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"蓝队起点"NOR);
        set("long",@LONG
抢旗战场

叙述征求，一格 2 玄黄
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        set("stab_flag", 1);
        set("party","blue");
        set("exits",([
         "north":__DIR__"bc1",
         "northeast":__DIR__"bne1",
         "northwest":__DIR__"bnw1",		
        ]));        
        setup();
}

void open_exit() {
        set("exits",([
         "north":__DIR__"bc1",
         "northeast":__DIR__"bne1",
         "northwest":__DIR__"bnw1",		
        ]));  
}