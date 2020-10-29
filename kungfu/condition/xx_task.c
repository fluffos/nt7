
// xx_task.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                message_vision(HIW"突然天空中飞下一只白鸽，降在$N的肩头。\n"NOR, me);
                if( query_temp("job_type", me) == 1 )
                        tell_object(me,BLU"这是一封飞鸽传书，原来老仙已经对杀不杀「"+query_temp("xx_target", me)+"」的事不感兴趣了！\n"NOR);
                else if( query_temp("job_type", me) == 2 )
                        {
                                tell_object(me,BLU"这是一封飞鸽传书，原来老仙已经对「"+query_temp("xx_target", me)+"」不感兴趣了！\n"NOR);
                                if( query("xx_points", me)>10 )
                                        addn("xx_points", -1, me);
                                delete_temp("xx_bonus", me);
                                delete_temp("xx_time", me);
                                delete_temp("xx_pot", me);
                                delete_temp("job_id", me);
                                me->clear_condition("xx_task");
                                delete_temp("xx_target", me);
                                me->apply_condition("wait_xx_task", 10);
                                return 0;
                        }
                delete_temp("xx_bonus", me);
                delete_temp("xx_time", me);
                delete_temp("xx_pot", me);
                delete_temp("job_id", me);
                me->clear_condition("xx_task");
                delete_temp("xx_target", me);
                me->apply_condition("wait_xx_task", 10);
                return 0;
        }
        me->apply_condition("xx_task", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}