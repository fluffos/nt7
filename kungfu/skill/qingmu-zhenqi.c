//大木真气
// redl 2014
#include <ansi.h>;

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
inherit SKILL;
//青木白金离火玄水厚土
string name() { return HIG "青木真气" NOR; }

// int valid_learn(object me)
// {
//         return notify_fail( name() + HIC "无法通过简单学习获得提升。\n" NOR);
// }

int valid_research(object me)
{
        if( query("max_neili", me)<100000 )
                return notify_fail("你的内力不够。\n");
        if( me->query_skill("huisheng-jue",1 )<2000 )
                return notify_fail("你的回生诀等级不够。\n");
        if( query("level", me)<50 )
                return notify_fail("你的人物等级不够。\n");
        if (me->query_skill("martial-cognize", 1) < me->query_skill("damu-zhenqi", 1))
                return notify_fail("你的武学修养太差。\n");                
        if( query("gcjinchuan_yuancizhenqi/2", me)<1 )        
                        return notify_fail(HIC "你修行"+ name() + HIC "需要的木行元磁力不够。\n" NOR);
        tell_object(me, NOR "你从身体里逼起一股木行元磁力，缓缓运行周身经脉。\n" NOR);          
        addn("gcjinchuan_yuancizhenqi/2", -1, me);
        return 1;
}

int valid_enable(string usage) { return usage == "taoism"; }

int difficult_level() 
{ 
        return 2800; 
} 

string perform_action_file(string action)
{
        return __DIR__"qingmu-zhenqi/"+ action;
}

int help(object me)
{
        write(HIC"\n"+name()+HIC"："NOR"\n");
        write(@HELP
    据说是上古句芒氏族的修行功法，借元磁力修炼，可以恢复气血，并大幅提高精气。
        学习要求：
                等级50
                内力100000
                回生诀2000
HELP
        );
        return 1;
}

