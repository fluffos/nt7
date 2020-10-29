#include <ansi.h>

#include <login.h>

int update_condition(object me, int duration)
{
        object room;
        object ob;
          object obb;
        object* inv;
        int i;
                
        ob=this_player();
        room = environment(ob);     

        if( query_temp("where", me)){
        if( query_temp("where", me) != environment(me)){
                message_vision(HIY"一个宋兵跑过来对$N说道：叫你守城，你却到处闲逛，我去报告郭大人！\n"NOR,me);
                set_temp("job_failed", 1, me);
                return 0;
        }
        }

        if( query_temp("start_job", me)){
        message_vision(HIY"$N正站在城墙上密切注视着城下"HIR"蒙古兵"HIY"的一举一动。\n"NOR,ob);
        }
        me->apply_condition("jobshadi_limit", duration - 1);

        if(duration<1)
        {
                message_vision(CYN"\n一个守城宋兵跑过来说道：蒙古靼子暂时被击退了，$N可以回去复命了！\n"NOR,ob);
        if( query_temp("start_job", me)){
                set_temp("job_over", 1, ob);
        }
                delete_temp("start_job", ob);
                inv=all_inventory(room);
                for (i = 0; i < sizeof(inv); i++) {
                     obb=inv[i];
                        if (obb->is_character()) {
                        if( query("ygjg", obb) == ob)destruct(obb);
                    }
                        continue;
                }
                return 0;
        }
        return 1;
}