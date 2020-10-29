// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "后山");
        set("long", 
"这是后山，山崖上光秃秃的寸草不生，更无一株树木。山风呼啸而过，\n"
"显得分外的荒凉。\n"
);
                set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"shanlu2",
                        "west" : __DIR__"teleport",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,20);
        set("owner_level", 1);
        
        setup();
}


void init()
{
        object me = this_player();
        object gcroom = get_object(__DIR__"guangchang.c");
        
        if (gcroom->owner_level(me)>0) {
                //tell_room(this_object(), "is_owner!\n");
                set_temp("dongtian/invite/hold_time", query("hold_time", gcroom), me);
        } else {
                //tell_room(this_object(), "not_owner!\n");
                if (query("online_time", me) < 86400) {
                        tell_object(me, NOR "你在线时间还不足一天玩什么洞天，一边玩新手帮助去。\n" NOR);  
                        me->command("go west");
                        return;
                }
                set_temp("dongtian/houshan/hold_time", query("hold_time", gcroom), me);
                tell_object(me, NOR "小心这里的防卫力量，你如果往西溜走还来得及。\n" NOR);  
                if (query_temp("dongtian/houshan/chat_time") < time()) {
                        set_temp("dongtian/houshan/chat_time", time() + 60);
                        CHANNEL_D->channel_broadcast("dt", NOR + HIW + "据说有人悄悄潜入了" + NOR + HIC + __DIR__"guangchang.c"->load_name() + NOR + HIW + "洞天仙府。\n" + NOR);
                }
        }
        //tell_room(this_object(), "init end!\n");

        me->start_busy(3);
        
        ::init();
}

int valid_leave(object me, string dir)
{
        object gcroom = get_object(__DIR__"guangchang.c");

                if(query("hold_time", gcroom) < 2 && wiz_level(me) < 5 && dir=="south") {
                                tell_object(me, NOR "你发现对面是个未知的洞天，不敢潜入。\n" NOR);  
                                me->start_busy(2);
                                return -1;      
                }
                
        return ::valid_leave(me, dir);
}





