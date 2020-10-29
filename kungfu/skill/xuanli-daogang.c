// redl 2015
#include <ansi.h>;

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
inherit SKILL;
//青木白金离火玄水厚土
//《礼记·王制》“天子将出，类乎上帝” 孔颖达 疏引 庾蔚之 曰：“五行各有德，故谓五德之帝。木神仁，金神义，火神礼，水神知，土神信。” 
//宋 丘光庭 《兼明书·五行神》：“木神曰 勾芒 ，火神曰 祝融 ，土神曰 后土 ，金神曰 蓐收 ，水神曰 玄冥 。土神独称后者，后，君也，位居中，统领四行，故称君也。
string name() { return HIB "玄" HIR "离" HIW "刀罡" NOR; }


int valid_research(object me)
{
        if( query("max_neili", me)<100000 )
                return notify_fail("你的内力不够。\n");
        if( query("level", me)<50 )
                return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("force-cognize",1 )<1500 )
                return notify_fail("你的内功修养等级不够。\n");
        if( me->query_skill("martial-cognize",1 )<2500 )
                return notify_fail("你的武学修养等级不够。\n");
        if( me->query_skill("blade",1 )<3500 )
                return notify_fail("你的基本刀法等级不够。\n");
        if (me->query_skill("martial-cognize", 1) < me->query_skill("xuanli-daogang", 1))
                return notify_fail("你的武学修养太差。\n");                
        if (me->query_skill("blade", 1) / 3 < me->query_skill("xuanli-daogang", 1))
                return notify_fail("你的基本刀法太差。\n");                
        if( query("gcjinchuan_yuancizhenqi/4", me)<1 )        
                        return notify_fail(HIC "你修行"+ name() + HIC "需要的水行元磁力不够。\n" NOR);
        if( query("gcjinchuan_yuancizhenqi/5", me)<1 )        
                        return notify_fail(HIC "你修行"+ name() + HIC "需要的火行元磁力不够。\n" NOR);
        tell_object(me, NOR "你从身体里逼起一股水行元磁力，缓缓运行周身经脉。\n" NOR);          
        tell_object(me, NOR "你从身体里逼起一股火行元磁力，缓缓运行周身经脉。\n" NOR);          
        addn("gcjinchuan_yuancizhenqi/4", -1, me);
        addn("gcjinchuan_yuancizhenqi/5", -1, me);
        return 1;
}

int valid_enable(string usage) { return usage == "taoism"; }

int difficult_level() 
{ 
        return 3200; 
} 

// string perform_action_file(string action)
// {
//         return __DIR__"qingmu-zhenqi/"+ action;
// }

int help(object me)
{
        write(HIC"\n"+name()+HIC"："NOR"\n");
        write(@HELP
    据说是上古玄冥祝融二族合创的修行功法，借元磁力修炼的道术，可以充分
调动刀法的各种绝技。后来又衍生出两仪元磁刀法。
        学习要求：
                等级50
                内力100000
                内功修养1500
                武学修养2500
                基本刀法3500
HELP
        );
        return 1;
}

