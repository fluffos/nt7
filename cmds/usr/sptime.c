// time.c                                          
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int cur_time = time();  
        object ob;
        string sp = "";

        if( !wizardp(me) && cur_time-query_temp("last_service", me)<5 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        set_temp("last_service", cur_time, me);

        if( arg && wizardp(me) )
        {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
        } else
                ob = me;

        if( MEMBER_D->is_valid_member(ob) ) 
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR); 
        else 
        {
                if( query("online_time", ob)/3<query("offline_time", ob) ) 
                        set("offline_time",query("online_time",  ob)/3, ob); 
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR, 
                              time_period(query("online_time", ob)/3-query("offline_time", ob))); 
        } 
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "下线保留物品时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/quit_save", ob)-time()) > 0 ? time_period(query("srv/quit_save", ob)-time()) : "零秒");
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "离线原地登陆时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/start_room", ob)-time()) > 0 ? time_period(query("srv/start_room", ob)-time()) : "零秒");
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "乾坤袋增容量时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/qiankun_volume", ob)-time()) > 0 ? time_period(query("srv/qiankun_volume", ob)-time()) : "零秒");
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "九头蛇领地权时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/enter_jtshe", ob)-time()) > 0 ? time_period(query("srv/enter_jtshe", ob)-time()) : "零秒");
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "师门飞鸽传书时间还剩下 " NOR + HIW "%s\n" NOR,
                      (query("srv/quest_letter", ob)-time()) > 0 ? time_period(query("srv/quest_letter", ob)-time()) : "零秒");
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                      time_period(query("time_reward/quest", ob)));
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                      time_period(query("time_reward/study", ob)));

        me->start_more(sp);
        return 1;
}

int help(object me)
{
     write(@HELP
指令格式: service

这个指令告诉你购买的各种服务到期的时间。

HELP
    );
    return 1;
}
