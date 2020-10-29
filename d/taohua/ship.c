// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>

inherit ROOM;
void create()
{
       set("short","海船");
       set("long", @LONG
这是辽阔的海面，海风「呼呼」在你耳边吹过，海浪一个接着一个向
你泼打过来，突然一个巨浪打来几乎把你所乘的船掀翻。你快要陷入这个
旋涡中了，还是催促渔夫赶紧摇船走出着鬼地方吧。
LONG );


//        set("exits", ([
//                "east" : __FILE__,
//                "west" : __DIR__"dahai2",
//                "south" : __DIR__"dahai3",
//                "north" : __DIR__"dahai4",
//        ]));
        setup();

}

/*
int valid_leave(object me, string dir)
{
        if ( dir == "west")
            addn_temp("mark/steps", 1, me);
        if ( dir == "east")
            addn_temp("mark/steps", -1, me);
        if ( dir == "north")
            addn_temp("mark/nsteps", 1, me);

        if( query_temp("mark/steps", me) == 10 )
         {
            me->move("/d/shenlong/tanggukou");
            delete_temp("mark/steps", me);
             return notify_fail("终于你看见了前方的陆地，啊，谢天谢地 ！\n");
         }

     if( query_temp("mark/steps", me) == -10 )
            {
               me->move("/d/shenlong/haian");
           delete_temp("mark/steps", me);
             return notify_fail("终于你看见了前方的陆地，啊，谢天谢地 ！\n");
        }

      if( query_temp("mark/nsteps", me) == 10 )
         {
            me->move("/d/shenlong/lushunkou");
            delete_temp("mark/nsteps", me);
             return notify_fail("终于你看见了前方的陆地，啊，谢天谢地 ！\n");
         }


        return ::valid_leave(me,dir);
}

void init()
{
        object me = this_player();

        if( interactive(me = this_player()) )
        {
            remove_call_out("arrive");
            call_out("arrive", 10);
        }

}

void arrive()
{
        message("vision", "渔夫说：“大陆到啦，上岸吧”。\n",this_player());
        this_player()->move("/d/shenlong/tanggu");
}
*/

int valid_leave(object me, string dir)
{
        object room;

        if ( !::valid_leave(me, dir) )
                return 0;

        if(!(room = find_object(__FILE__)) )
                room = load_object(__FILE__);
        if(objectp(room))
        {
                addn_temp("person_inside", -1, room);
                if( room->addn_temp("person_inside",-1) <= 0 )
                        delete_temp("person_inside", room);
        }

        return 1;
}
