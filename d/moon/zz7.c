// ken 1999.12.9

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "树林");
	set("long", @LONG
走到这里，眼前是大片的树丛，一片白芒芒的雾气，挡住了去路。夜暮已
渐渐降临，四下里静无人声，只听到猫头鹰在不远的枯树上诡异地咕咕作响，
你不禁开始感到有些毛骨耸然。
LONG
	);
	set("exits", ([ 
  "south" : __DIR__"zz1",
]));

        set("item_desc", ([
   "雾气": "一片白芒芒的雾气，弥漫在这片树林之中，如果能站得高些，或许...\n",
   "枯树": "一棵早已干枯了的树，树干上已开始腐朽。\n",
        ]) );
	set("coor/x",-10);
	set("coor/y",1010);
	set("coor/z",0);
	setup();
}

void init()
{	
	add_action("do_climb","climb");
}

int climbbusy(object me)
{  object room;
         room = find_object("/u/moon/treetop");
        if(!objectp(room)) room=load_object("/u/moon/treetop");
        me->move(room); 
         message_vision("\n$N小心翼翼地沿着快要朽断的树干慢慢地爬了上来。\n",me); 
        return 1;
}

int do_climb(string arg)
{
        object room;
        object me;
        if(!arg || arg=="")
        {
                write("你要爬什么？\n");
                return 1;
        }
        if( arg == "kushu" || arg == "枯树" )
        {
        me = this_player();
message_vision("\n\n$N抬头看了看枯树的顶端，手脚并用，向上爬去......\n\n",me);
	me->start_busy(1);
        call_out("climbbusy",1,me);
        me->stop_busy();
        return 1;
        }
        else
         write("你要爬什么？\n");
                return 1;
}

