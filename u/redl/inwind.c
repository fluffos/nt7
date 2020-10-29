// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create()
{
        set("short", "天地间");
        set("long", 
"流岚曼舞，妩媚千重。踏云随风，逍遥苍穹。\n"
);

                set("no_fight", 1); 
                set("no_magic", 1); 
                set("no_rideto", 1);
                set("no_flyto", 1);
        
        setup();
}

void init()
{
                object me = this_player();
                if (playerp(me)) {
                        me->start_busy(3);
                        call_out("do_sui", 1, me); 
                }
}


int do_sui(object me)
{
                if (!query_temp("can_redlinwind", me)) set_temp("can_redlinwind", 1, me);
                if (query_temp("can_redlinwind", me) < 12) {
                        addn_temp("can_redlinwind", 1, me);
                message_vision(YEL "$N的影子越来越远，随着清风徐徐往远处飘去...\n" NOR, me);
                me->move(__DIR__"inwind");
                } else {
                        delete_temp("can_redlinwind", me);
                        me->stop_busy();
                message_vision(YEL "$N的思绪还在飘飘荡荡之中，突然脚下一震，$N睁目一看...\n" NOR, me);
                me->move(__DIR__"lake");
                tell_object(me, YEL "清风将你缓缓托到湖边放下，注视着眼前这一切，你久久不想挪动脚步。\n" NOR);
                }
                return 1;
}


