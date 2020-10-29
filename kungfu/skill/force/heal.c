// heal.c
// Updated by Lonely

// 参考于侠客行
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **\
 * heal.c 内功治疗内伤功能                                              *
 *                                                                      *
 * 内功应该拥有几种共有的功能，像已有的打坐、吐呐、运气、运精、运精力， *
 * 以及开放中的比拼内力。其中运转内息治疗内伤也应该是所有内功都应该有的 *
 * 功能。                                                               *
 * 泥潭现有的伤害系统，在内伤和外伤完全没有区别。内伤外伤是两码子事，当 *
 * 内功高，内伤自然容易好。外伤却未必，又不是神功一运，立即镇伤生肌，那 *
 * 变成生化人了。所以外伤在大部份情况下只能借助于外界药物的辅助来治疗。 *
 * 基本上普通内伤都可以通过运转内息来治疗，所差者不过於不同内功在於治疗 *
 * 方面效果的好坏，而且如果伤势越重，效果越小，不像以前侠客行一次多少内 *
 * 力、就固定恢复多少。通过内伤的康复，慢慢会加快治愈速度。而外伤的康愈 *
 * 速度，多半则取决于其伤势的程度，所用药物的药性，以及本身的肌肉构造， *
 * 也就是泥潭里面的con。                                       *
 * 至于如何体现出内外伤的不同，而将这泥潭的伤害系统做得更合理性，这些是 *
 * 以后所要改变的，这里所要说明的只是以下功能只是以内伤作为前提考虑，所 *
 * 以或许对于泥潭现有的伤害系统会有少许的不合理性。                     *
 *                                                                      *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/


#include <ansi.h>

mapping eff_heal = ([
        "yinyang-shiertian"     : 21,   // 转世技能，最强的内功。
        "jiuyin-shengong"       : 10,   // 大宗师内功超强。
        "bluesea-force"         : 10,   // 大宗师内功超强。
        "never-defeated"        : 10,   // 大宗师内功超强。
        "kuihua-mogong"         : 10,   // 大宗师内功超强。
        "jiuyang-shengong"      : 9,    // 九阳神功在疗伤方面的效果无可置疑。
        "taixuan-gong"          : 9,    // 参考九阳神功。
        "yijinjing"             : 9,
        "hunyuan-yiqi"          : 8,    // 鉴於易筋经以及九阳神功在疗伤方面的效果。
        "zixia-shengong"        : 8,    // 紫霞神功及混元功在自疗方面没有什么提及，但是有鉴
                                        // 於其疗人的效果，以及岳不群曾经想让令狐冲自习紫霞
                                        // 神功来治疗内伤，可见於自疗方面的效果，或许可以与
                                        // 易筋经相媲美。就算是有所不及，考虑到当今紫霞神功
                                        // 没有什么特别的 exert，也应当让紫霞神功在治疗方面
                                        // 的效果相对於其他内功更好。
        "taiji-shengong"        : 8,
        "xiantian-gong"         : 8,    // 书中有相当篇幅提到武当九阳功与全真玄门内功的疗伤。
        "kurong-changong"       : 7,    // 大理内功在疗人方面的效果很好，可是在自疗方面却没
                                        // 有什么特别之处。
        "linji-zhuang"          : 7,    // 峨嵋内功在疗伤方面没有什么特别描述，不过因其是九
                                        // 阳一系。
        "bibo-shengong"         : 6,
        "yunu-xinfa"            : 6,
        "xiaowuxiang"           : 5,
        "sanku-shengong"        : 5,    // 三苦神功，为唐门内功，疗伤一般,在疗毒方面超强。
        "huntian-qigong"        : 4,    // 混天功、蛤蟆功、龙象般若功走的都是刚猛一路的内功，
        "hamagong"              : 4,    // 因此在疗伤方面会相对弱些。
        "longxiang-gong"        : 4,
        "beiming-shengong"      : 3,    // 北冥神功吸人内力，体内真气相冲会影响疗伤时的效果。
        "huagong-dafa"          : 2,    // 化功大法以毒练功，在疗伤方面效果应该最为不好。
        "dulong-dafa"           : 2,
        "hongming-xuangong"     : 1,
        "ding-force"            : 1,    // 以上三种内功书中未有提及，被列为不可考。
]);


int exert(object me, object target)
{
        string force;
        mapping msg;

        if (me->is_fighting())
                return notify_fail("战斗中运功疗伤？找死吗？\n");

        if (me->is_busy())
                return notify_fail("等你忙完了手头的事情再说！\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("先激发你的特殊内功。\n");

        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail("你现在气血充盈，不需要疗伤。\n");

        if ((int)me->query_skill(force, 1) < 20)
                return notify_fail("你的" + to_chinese(force) + "修为还不够。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me)/5 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");
        
        msg = SKILL_D(force)->heal_msg(me);
                
        if (! msg || undefinedp(msg["start_self"]))
                write(HIW "你全身放松，坐下来开始运功疗伤。\n" NOR);
        else 
                write(msg["start_self"]);               

        set_temp("pending/healing", 1, me);
        
        if (! msg || undefinedp(msg["apply_short"]))
                me->set_short_desc("正坐在地下运功疗伤。");                
        else    
                me->set_short_desc(msg["apply_short"]);

        if (! msg || undefinedp(msg["start_other"]))
                tell_room(environment(me), HIW + me->name() + "盘膝坐下，开始运功疗伤。\n" NOR, me);
        else
                tell_room(environment(me), msg["start_other"], me); 
                                
        me->start_busy((:call_other, __FILE__, "healing" :),
                       (:call_other, __FILE__, "halt_healing" :));

        return 1;
}

// 疗伤中
int healing(object me)
{
        string force;
        int recover_points, lvl, con, eff;
        mapping msg;

        force = me->query_skill_mapped("force");
        if (! stringp(force))
        {
                // 没有特殊内功了？
                tell_object(me, "你一时难以定夺如何运用内力，只好先暂停疗伤。\n");
                set_temp("pending/healing", 0, me);
                me->set_short_desc(0);
                message_vision("$N叹了口气，摇摇晃晃的站了起来。\n", me);
                return 0;
        }
        
        msg = SKILL_D(force)->heal_msg(me);

        if( query("eff_qi", me)<query("max_qi", me) )
        {
                // 需要继续疗伤
                if( query("neili", me)<50 )
                {
                        if (! msg || undefinedp(msg["unfinish_self"]))
                                tell_object(me, "你觉得真气不济，难以在经脉中继续运转疗伤，只得暂缓疗伤，站起身来。\n");
                        else    
                                tell_object(me, msg["unfinish_self"]);
                                
                        set_temp("pending/healing", 0, me);
                        me->set_short_desc(0);
                        
                        if (! msg || undefinedp(msg["unfinish_other"]))
                                tell_room(environment(me), me->name() + "叹了口气，摇摇晃晃的站了起来。\n", me);
                        else    
                                tell_room(environment(me), msg["unfinish_other"], me);
                                
                        return 0;
                }
                
                //lvl = (int)me->query_skill("force") / 10;
                lvl = (int)me->query_skill("force");
                con = (int)me->query_con();
                eff = eff_heal[force];
                if (! eff ) eff = 3;

                recover_points = con + lvl * eff;
                if( query("breakup", me) )
                        recover_points *= 3;
                if( query("yuanshen_level", me) )
                        recover_points *= 2;
                if (recover_points < 1) recover_points = 1;
                me->receive_curing("qi", recover_points);                                
                addn("neili", -50, me);
                
                if (! msg || undefinedp(msg["heal_msg"]))
                {
                        switch (random(10))
                        {
                        case 0:
                                tell_object(me, "你运用" + to_chinese(force) + "沿着"
                                                "诸大穴慢慢运转，疗解伤痛。\n");
                                break;
                        case 1:
                                tell_object(me, "你将内力纳入丹田，再上行冲顶，透泥宫"
                                                "，顿觉精神爽快。\n");
                                break;
                        case 2:
                                tell_object(me, "你将内力运入四肢百赅，复又回收丹田，"
                                                 "伤势痊愈不少。\n");
                                break;
                        }
                        return 1;
                } else
                {
                        tell_object(me, msg["heal_msg"]);
                        return 1;
                }
        }

        // 恢复完毕
        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        if (! msg || undefinedp(msg["finish_self"]))
                tell_object(me, HIY "你运功完毕，吐出一口瘀血，自觉经脉顺畅，内伤尽去，神元气足地站了起来。\n" NOR);
        else    
                tell_room(me, msg["finish_self"]); 
                
        if (! msg || undefinedp(msg["finish_other"]))
                tell_room(environment(me), HIY + me->name() + "运功完毕，吐出一口瘀血，站起身来，脸色看起来好多了。\n" NOR, me);
        else
                tell_room(environment(me), msg["finish_other"], me);      
                
        return 0;
}

// 停止疗伤
int halt_healing(object me)
{
        string force;
        mapping msg;
        
        if (stringp(force = me->query_skill_mapped("force"))) 
                msg = SKILL_D(force)->heal_msg(me);
        
        if (! msg || undefinedp(msg["halt_self"]))
                tell_object(me, "你将真气收回丹田，微微喘息，站了起来。\n");
        else    
                tell_object(me, msg["halt_self"]);
                
        if (! msg || undefinedp(msg["halt_other"]))
                tell_room(environment(me), me->name() + "猛的吸一口气，突然站了起来。\n", me);
        else    
                tell_room(environment(me), msg["halt_other"], me);
                
        set_temp("pending/healing", 0, me);
        me->set_short_desc(0);
        if( query("neili", me)>100 )
                addn("neili", -100, me);
        else
                set("neili", 0, me);
        return 1;
}
