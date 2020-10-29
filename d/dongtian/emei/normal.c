// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void fullnow(object me)
{
        mapping my;
                me->remove_all_enemy(1);
                me->remove_call_out("revive");
                me->remove_call_out("unconcious");
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        me->clear_condition();
        me->stop_busy();
        me->clear_weak();
        me->full_self();
        if( query_temp("block_msg/all", me) ) {
                        tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR);
                        delete_temp("block_msg/all", me);
        }
        me->set_short_desc(0);//去掉修炼等描述
}

int user_cant_die(object me)
{
        if (userp(me)) {
            fullnow(me);
                if (__DIR__"guangchang.c"->owner_level(me)) {
                        message_vision(append_color(NOR CYN "$N" NOR CYN "痛呼一声，把腰里的行囊扔了...\n" NOR, YEL), me);
                        me->command("drop all");//支持不杀人而越货
                                message_vision(append_color(NOR YEL "虚空中穿过来一只大如山岳的巨掌，对着$N" NOR YEL "拦腰一捞，再缩回去就此不见了。\n" NOR, YEL), me);
                                set_temp("dongtian/user_cant_die", 1, me);
                                me->move(__DIR__"dadian");
                        message_vision(append_color(NOR YEL "$N" NOR YEL "啪哒一声从天上摔了下来。\n" NOR, YEL), me);
                } else {
                __DIR__"shuilao.c"->throwing(me, 30);
            }
        }
        return 1;
}

int user_cant_unconcious(object me)
{
        if (userp(me)) {
                fullnow(me);
                user_cant_die(me);
        }
        return 1;
}

int discmds() 
{ 
        tell_object(this_player(), "你不能在这里毛手毛脚。\n");  
        return -1;  
} 

int disyanjiu() 
{ 
        tell_object(this_player(), "你不能在这里研究练习。\n");  
        return -1;  
} 

int disget()
{
        tell_object(this_player(), "你不能在这里乱拿乱扔。\n");  
        return -1;  
}

void init()
{
        object *inv;
        int countp;
        object me = this_player();
        
        //if ( wiz_level(me) > 5 ) return;
        
        if (playerp(me))  {     
                        inv = all_inventory();
                        if( sizeof(inv) > 0 ) {
                foreach( object ob2 in inv ) {
                        if ( playerp(ob2) ) countp ++;
                }
                }
                
            if(query("max_carry_user") && query("max_carry_user")<countp && query("max_carry_exit")) {
                        tell_object(me, "\n你发现因为人数超载，这空间出现不稳定的状态，吓得赶紧退出。\n\n");  
                        me->command(query("max_carry_exit"));
                        return;         
        }
        
        }

                if ((playerp(me) && wiz_level(me) < 6) || (base_name(me)=="/clone/user/baby")) add_action("discmds", ({  
                        "steal", "cast", "conjure", "array", "fight", "hit",   
                        "quit", "home", "exit", "recall", "ansuan", "touxi", //"kill", 
                        "surrender", "exert", "team", "chatroom", "rideto", "array", "battle", "accept", "swear",
                }));  
                
        if (query("no_get")) add_action("disget", ({"get", "uget", "drop"})); 
        if (query("no_yanjiu")) add_action("disyanjiu", ({"research", "yanjiu", "practice", "lian", "read", "du", "study"})); 

}

int valid_leave(object me, string dir)
{
        object horse, room, *inv;
        int countp;

        //npc应该要能follow
        if (me->is_busy()) return -1;
        if (playerp(me) && !interactive(me)) return -1;
        
        if (objectp(horse=query_temp("is_riding", me)) && objectp(query_temp("is_rided_follow", horse))) {
                tell_object(me, NOR "先让你马背上的家伙下来。\n" NOR);  
                return -1;
        }
        
                if (query("exits/" + dir)) room = get_object(query("exits/" + dir));
                
                if (playerp(me) && room && objectp(room) && query("owner_level", room) && wiz_level(me) < 5) {
                        if (__DIR__"guangchang.c"->owner_level(me) < query("owner_level", room)) {
                                tell_object(me, NOR "那不是你可以进去的地方。\n" NOR);  
                                me->start_busy(2);
                                return -1;      
                        }
                }
        
                if (playerp(me) && room && objectp(room) && query("max_carry_user", room)) {
                        inv = all_inventory(room);
                        if( sizeof(inv) > 0 ) {
                foreach( object ob3 in inv ) {
                        if ( playerp(ob3) ) countp ++;
                }
                }

                if(query("max_carry_user", room) < countp + 1 && wiz_level(me) < 5) {
                                tell_object(me, NOR "你发现对面的人太多了，空间不稳定不敢过去。\n" NOR);  
                                me->start_busy(2);
                                return -1;      
                }
                }
                
        return ::valid_leave(me, dir);
}



