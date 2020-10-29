#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
        object room;
        object obb;
        object* inv;
        int i;

        if (duration < 1) return 0;  
        
        me->apply_condition("jobshadi_limit", duration - 1);  

        room = environment(me);     
        if( query_temp("guo_shoucheng/where", me) )
        if( query_temp("guo_shoucheng/where", me) != room
         && !query_temp("guo_shoucheng/job_over", me) )
        {
                message_vision(HIY "一个宋兵跑过来对$N说道：叫你守城，你却到处闲逛，我去报告郭大人！\n" NOR, me);
                set_temp("guo_shoucheng/failed", 1, me);
                me->apply_condition("jobshadi_limit", 0);  
        }

        if( query_temp("guo_shoucheng/start_job", me )
         && query_temp("guo_shoucheng/where", me) == room )
         message_vision(HIY"$N正站在城墙上密切注视着城下"HIR"蒙古兵"HIY"的一举一动。\n"NOR,me);

        if (me->is_ghost())
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_limit", 0);
                return 0;
        }

        if( duration == 1 && query_temp("guo_shoucheng/where", me) == room )
        {
                message_vision(HIW "这时从蒙古军营传来阵阵战鼓声音，攻城的蒙古大军忽然开始撤退了！\n" NOR, me);   

                message_vision(CYN "\n一个守城宋兵跑过来说道：蒙古靼子暂时被击退了，$N可以回去复命了！\n" NOR, me);
                if( query_temp("guo_shoucheng/start_job", me) )
                        set_temp("guo_shoucheng/job_over", 1, me);
                delete_temp("guo_shoucheng/start_job", me);
                inv = all_inventory(room);
        
                for (i = 0; i < sizeof(inv); i++) 
                {
                        obb = inv[i];

                        if( obb->is_character() && !userp(obb) && query("is_guojob", obb )
                         && query("want_kill", obb) == me )
                                destruct(obb);
                        else continue;  
                }
                me->apply_condition("jobshadi_limit", 0);     
        }
        return CND_CONTINUE;      
}