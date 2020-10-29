// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>

void apply_boss(object me, int btype, int guarder);

int valid_leave(object me, string dir)
{
        int nt, nk, ng, kar;
        
        if (!query_temp("xzz/kar", me)) set_temp("xzz/kar", 15 + random(19), me); //防止意外出现在林子里的玩家出现异常
        ng = query("ngroup", environment(me));
        kar = 100 + query_temp("xzz/kar", me);

        if (ng == 1) //外围
        {
                addn_temp("xzz/ntrip", 10, me);//移动惩罚增加
                addn_temp("xzz/nkill", -2, me);
                nt = query_temp("xzz/ntrip", me);
                nk = query_temp("xzz/nkill", me);
        }
        else if (ng == 2) //深处
        {
                addn_temp("xzz/ntrip2", 10, me);//移动惩罚增加
                addn_temp("xzz/nkill2", -1, me);
                nt = query_temp("xzz/ntrip2", me);
                nk = query_temp("xzz/nkill2", me);
        }
        
        //tell_object(me, HIC" [" + ng + ", kar:"+ kar +"] 测试 - > nt:" + nt + " nk:" + nk + "\n"NOR);  //测试
        
        if (ng && playerp(me) && nt>=to_int(400 * kar / 100)) 
        {
                if (ng == 1) //外围
                {
                        if (nk < to_int(960 * kar / 100))
                        {
                if (random(5) == 0)
                {
                        me->start_busy(6+random(5));
                        return notify_fail(CYN"突闻一丝异香飘过，你心中警觉顿生，伸手捂住鼻子，脚步也停了下来。\n"NOR);
                }
            }
            else//boss努尔海
            {
                apply_boss(me, ng, 6 + random(3));
                                return notify_fail(CYN"努尔海冲着你一指，你被几个武士挡住了去路。\n"NOR);
            }
                }
                else if (ng == 2) //深处
                {
                        if (nk < to_int(770 * kar / 100))
                        {
                                if (!query_temp("xzz/poison", me)) //新中毒
                                {
                                        set_temp("xzz/poison", 10, me);
                                        message_vision(HIY"$N突然剧烈咳嗽起来，紧闭的双眼泪水不绝涌出。\n"NOR, me);
                                        call_out("update_beisu", 6, me);
                                        me->start_busy(5);
                                        return notify_fail(NOR "你中的「" + HIG + "悲酥清风" + NOR + "」毒发，手酸足软！\n" NOR);
                                }
                                else if (query_temp("xzz/poison", me)<=1000)
                                {
                                        addn_temp("xzz/poison", 5, me);
                                }
                        }
                        else//boss赫连铁树
                        {
                apply_boss(me, ng, 2 + random(2));
                                return notify_fail(CYN"赫连铁树冲着你一指，你被几个武士挡住了去路。\n"NOR);
                        }
                }
        }
        
        return ::valid_leave(me, dir);
}


void update_beisu(object me)
{
        int nrnd = random(100);
        
        if( !me ) return;
        if (!query_temp("xzz/poison", me)) return;
        if (query_temp("xzz/poison", me)<=0)
        {
                delete_temp("xzz/poison", me);
                return;
        }
        addn_temp("xzz/poison", -1, me);
        
        if (nrnd < 25)
        {
                tell_object(me, NOR "你中的「" + HIG + "悲酥清风" + NOR + "」毒发，目不能视！\n" NOR );
                set_temp("block_msg/all", 1, me);
                call_out("cimu_end", 3+random(3), me);
        }
        else if (nrnd <75)
        {
                tell_object(me, NOR "你中的「" + HIG + "悲酥清风" + NOR + "」毒发，手酸足软！\n" NOR );
                me->start_busy(4+random(3));
        }
        else
        {
                me->apply_condition("no_exert", 3+random(4)); 
        }
        me->apply_condition("no_perform", 3+random(4)); 
        
        call_out("update_beisu", 6, me);
}


void cimu_end(object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target)) tell_object(target, HIR "你勉强睁开泪眼，看得见一些景象了。\n" NOR);
                delete_temp("block_msg/all", target);
        }
        return;
}

void apply_boss(object me, int btype, int guarder)
{
        object ob, where;

        me->start_busy(3);
        where = this_object(); //environment(me);
        message_vision(YEL "一阵铁蹄疾踏声中，树林里突然冲出来" + chinese_number(guarder+1) + "骑人马将$N团团围住...\n" NOR, me);
        if (btype == 1)
        {
                while (guarder--) {
                        ob = new(__DIR__"npc/wushi9");
                        ob->move(where); 
                        ob->set_leader(me);
                }
                set_temp("xzz/ntrip", 0, me);
                set_temp("xzz/nkill", 0, me);
                ob = new(__DIR__"npc/bossnu");
        }
        else
        {
                while (guarder--) {
                        ob = new(__DIR__"npc/wushi2345");
                        ob->move(where); 
                        ob->set_leader(me);
                }
                set_temp("xzz/ntrip2", 0, me);
                set_temp("xzz/nkill2", 0, me);
                ob = new(__DIR__"npc/bosshe");
        }
        ob->move(where); 
        ob->set_leader(me);
}




