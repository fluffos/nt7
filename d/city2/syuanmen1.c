// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "辕门外"NOR);
        set("long", @LONG
这里就是「大宋」军营驻扎地了，远远地可以看见一面大旗，上
面书着一个斗大的隶书「宋」字，再走近些就到军营了，寻常人还是
不要靠近的好，省得被当成细作捉起来。西边一个石门通向箭楼，上
面一个铁门通向城墙。
LONG );
        set("defence",120);
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" : __DIR__"sying",
               "east"  : __DIR__"conglin4",
               "west"  : __DIR__"sying6",
               "up"    : __DIR__"sying5",
        ]));    

        create_door("up", "铁门", "down", DOOR_CLOSED);
        create_door("west", "石门", "east", DOOR_CLOSED);
        setup();
}
              
void init()
{
        object me = this_player();

        if( query_temp("warquest/party", me) == "meng" )
                add_action("do_break", "break");
        else
        if( query_temp("warquest/party", me) == "song" )
                add_action("do_repair", "repair");
}

int do_repair()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if (WAR_D->query_stones(me) < 200)
                return notify_fail("由于缺少足够的石头及木材,辕门的防御工事无法修理！\n");

        if( query("defence", room)>999 )
                return notify_fail("辕门的防御工事已经修理好了！\n");
        else
        {
                if( query_temp("warquest/group", me) < 1 )
                        return notify_fail("你还是带领队伍来抢修着辕门的防御工事吧！\n");

                message_vision(
                        HIW "$N带着一支队伍紧张地抢修着辕门的防御工事！\n" NOR, me);
                addn("defence", random(query_temp("warquest/group", me)), room);
                WAR_D->expend_stones(me, 200);
                me->start_busy(1 + random(2));
                return 1;
        }
}

int do_break()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())        
                return notify_fail("你正忙着呢！\n");

        if( query("defence", room)<1 )
        {
                set("defence", 0, room);
                write("辕门的的防御已经被击破了，快冲进去啊！\n");
                return 1; 
        } else
        {
                message_vision(
                        HIY "$N带着一支攻城队伍正加紧攻击着辕门的防御工事！\n" NOR,me);
                addn("defence", -random(query_temp("warquest/group", me)), room);
                me->start_busy(2 + random(2));
                return 1;
        }
}

