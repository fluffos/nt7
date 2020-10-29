// This program is a part of NITAN MudLIB  
// redl 2015/10
#include <ansi.h>  
#include <room.h>  
inherit BUILD_ROOM; 

void create()
{
        set("short","不周山·626米");
        set("long", "这里是不周山，相传不周山是人界唯一能够到达天界的路径，\n"
"只可惜不周山终年寒冷，长年飘雪，非凡夫俗子所能徒步到达。传\n"
"言曾有凡人为见神仙一面而只身上山，但却未曾见其返乡。\n");
        set("outdoors", "yangzhou");
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_magic", 1); 
        set("no_user_kill", 1); 
        set("no_sleep_room", 1);  
        set("exits",(["down":__DIR__"bzs_6","up":__DIR__"bzs_8"]));setup();
}

int do_look(string arg)
{
        object me = this_player();
        if ( arg && arg=="up" ) {
                        tell_object(me, NOR "你凝聚目力望过去，只见云雾飘渺。\n" NOR);
                        return -1;
        }
        return 0;
}

int valid_leave(object me, string dir)
{
                if (dir=="up") {
                        if ( file_size(query("exits/up") + ".c") < 1 )
                                return notify_fail(NOR "一个声音喝止你：你是从山脚拜上来的吗？\n" NOR);
                }
                
        return ::valid_leave(me, dir);
}

int init() 
{ 
        add_action("do_look", "look");
} 

