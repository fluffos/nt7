// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "假山");
	set("long", @LONG
 刚进庄门，一座高大的假山就挡住了你的视线。虽看不见庄内的情形，
但耳中却听得不远处隐隐传来人声。
LONG	);
set("exits", ([ 
  "south" : __DIR__"door",
]));
        set("objects",([
			__DIR__"obj/jiashan" : 1,
       	]) );
	set("coor/x",-30);
	set("coor/y",1080);
	set("coor/z",40);
	setup();
}
void init()
{	
	add_action("do_around","around");
}

int do_around(string arg)
{       
        object room;
        object me;
        if(!arg || arg=="")
        {
                write("你要转过什么？\n");
                return 1;
        }
        if( arg == "jiashan" || arg == "假山" )
        {
        me = this_player();
        room = find_object("/n/moon/fgaden");
        if(!objectp(room)) room=load_object("/u/moon/fgaden");
       
        message_vision("\n$N在假山中东一转，西一转，眼前突然现出一片辉煌。\n\n",me); 
        me->move(room); 
        return 1;
        }
        else
         write("你要转过什么？\n");
                return 1;
}
