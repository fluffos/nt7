//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"树林"NOR);
        set("long", @LONG
忽然景色一转，前面变成了一片幽深的树林。你看看了看四周，
觉得周围有些地方不太对头，但是却说上不上来。树林里面似乎有些
声音传来。到底该怎么办呢？你不由踌躇起来。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ])); 
/*        set("objects", ([   
             "/d/city/npc/xdh-guard" : 2,   
            ]));
            */   
	set("coor/x", -10);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();            
}


int valid_leave(object me, string dir)
{
        int total_steps;

        if( query("bunch/bunch_name", me) == "小刀会" )
        {
                total_steps = 1; 
        } else
                       
                total_steps = 20;
        
        if (dir == "north")
                addn_temp("shulin/steps", 1, me);

        if (dir == "south")
                addn_temp("shulin/steps", -1, me);

        if( query_temp("shulin/steps", me) == total_steps )
        {
                me->move("/d/city/xdhzb");
                delete_temp("shulin/steps", me);
                write("你终于到了小刀会。\n");
                return -1;
        }  

        if( query_temp("shulin/steps", me) == -total_steps )
        {  
                me->move("/d/city/shulin1");
                delete_temp("shulin/steps", me);
                write("你走了半天又回到了原地。\n");
                return -1;
        }

        return ::valid_leave(me,dir);
}