
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        object *ob;
        int i;
        string msg;
        
        if( !living(me) ) {
                message("vision", me->name() + "痛苦地呻吟了一声。\n", environment(me), me);
        }
        else {
                tell_object(me,HIR"你只觉丹田中一股真气逆行，胸中烦恶欲呕！\n" NOR );
                message_vision(HIW"$N眼睛中射出异样光芒，口中喃喃自语。\n"NOR,me);
        }
        
        set_temp("die_reason", "修炼七伤拳走火入魔死了", me);
        me->receive_wound("qi", 1000);
        
        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( query("race", ob[i]) != "人类"
                ||  ob[i]==me || !me->visible(ob[i])) 
                        continue;
                tell_object(me, "\n"+ob[i]->name()+"对著你喝道：「"
                        + RANK_D->query_rude(me)+"！今日不是你死就是我活！」\n\n");
                tell_object(me, HIR "如果你要和" + ob[i]->name()
                        + "性命相搏，请你也对这个人下一次 kill 指令。\n"NOR);
                me->want_kill(ob[i]);
                me->kill_ob(ob[i]);
                ob[i]->fight_ob(me);
        }

        me->apply_condition("qs_damage", duration - 1);
        
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}