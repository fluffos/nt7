// practice.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string skillname;
        string base_skname;
        int skill, skill_basic, times, i;
        int c, r;
        int difficult, diff, improve;
        int neili_cost, qi_cost, qi;
        int t1, t2, t3, t4;
        int t = time();
        int n;

        if( !where ) return notify_fail("你目前的位置有问题，还是先找巫师解决吧！\n");

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( t == query_temp("time/practice", me) )
                return notify_fail("你刚刚才练习过（如果你要连续练习，可以指明练习的次数）。\n");

        if( me->is_fighting() )
                return notify_fail("你已经在战斗中了，学一点实战经验吧。\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            query("doing", me) != "scheme" )
                return notify_fail("你无法在这个地方安心练习。\n");

        if( !arg ) return (__DIR__"enable")->main(me, arg);

        if( (sscanf(arg, "%s %d", base_skname, times) != 2) ) {
                times = 1;
                base_skname = arg;
        }

        c=200+me->query_all_buff("practice_times");

        if( query("special_skill/wisdom", me) )
                c += 500;
        if( objectp(where) && query("dongtianfudi", where) )//洞天福地
                c += query("dongtianfudi", where);

        if( n = ACTION_D->query_action("lianxi_times") )
                c *= n;
        if( times < 1 || times > c )
                return notify_fail("练习次数必须大于一次，但不能超过" + chinese_number(c) + "次。\n");

        if( !stringp(skillname = me->query_skill_mapped(base_skname)) )
                return notify_fail("你只能练习用 enable 指定的特殊技能。\n");

        skill_basic = me->query_skill(base_skname, 1);
        skill = me->query_skill(skillname, 1);
        if( skill < 1 )
                return notify_fail("你好像还没有学过这项技能吧？最好先去请教别人。\n");

        if( skill_basic < 1 )
                return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");

        if( skill_basic <= skill )
                return notify_fail("你的" + to_chinese(base_skname) +
                                   "火候不够，难以继续提升你" +
                                   to_chinese(skillname) + "的水平。\n");

        notify_fail("你现在不能练习这项技能。\n");

        if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

        if( !XUE_CMD->can_learn(me, skillname) )

        notify_fail("你试着练习" + to_chinese(skillname) + "，但是并没有任何进步。\n");
        if( !me->can_improve_skill(skillname) )
                return notify_fail("也许是缺乏实战经验，你的练习总没法进步。\n");

        set_temp("time/practice", t, me);

        if( skill >= 2000 )
                improve = skill_basic / 4;
        else
        if( skill >= 1000 )
                improve = skill_basic / 2;
        else
                improve = skill_basic;

        if( intp(r=me->query_all_buff("practice_effect")) )
        {
                if( r > 2000 ) r = 2000;
                improve += improve * r / 100;
        }

        if( query("special_skill/wisdom", me) )
                improve += improve * 50 / 100;

        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;
        
        // 帮派荣誉点
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "lianxi") )
                improve += improve * 20 / 100;

        if( me->query_family() && BUNCH_D->query_family_efficient(me->query_family(), "lianxi") )
                improve += improve * 20 / 100;
                
        diff = SKILLS_D->query_skill_difficult(skillname);
        difficult = SKILL_D(skillname)->difficult_level();
        if( !diff) diff = difficult;
        if( !diff) diff = 100;
        improve = improve / (diff/100 + 1);

        if( !SKILL_D(skillname)->practice_skill(me) )
                return 0;

        neili_cost = diff / 20 + 20;
        qi_cost = diff / 10 + 10;

        t1=query("neili", me)/neili_cost+1;
        t2=query("qi", me)/qi_cost+1;
        t3 = min(t1, t2);

        if( t3 > times ) t3 = times;
        t4 = t3 - 1;

        if( t4 < 1 ) t4 = 1;
        me->receive_damage("qi", qi_cost * t4);
        addn("neili", -neili_cost*t4, me);

        me->improve_skill(skillname, improve * (t3 + 1),
                          skill_basic > skill? 0: 1);

        if( t3 > 0 )
                write(HIC "你试着把" + to_chinese(skillname) +
                      "练了" + chinese_number(t3)+"趟。\n" NOR);

        if( t3 >= times )
                return 1;

        return 1;
}

int help(object me)
{
        write(@TEXT
指令格式：practice|lian <技能种类> <次数>

这个指令让你练习某个种类的技能，这个技能必须是经过 enable 的专业技能。

如果你对这方面的基本技能够高，可以经由练习直接升级，而且升级的上限只跟
你基本技能的等级有关，换句话说，勤加练习是使你的所学「青出于蓝胜于蓝」
的唯一途径，当然，在这之前你必须从实际运用中获得足够的经验以提升你的基
本技能。
TEXT );
        return 1;
}

