#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "五毒珠" NOR, ({ "wudu zhu", "wudu", "zhu" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "此乃五毒教练功之神品，乃是从数百种天下奇毒中提炼而成，服用\n"
                                "后可大大增加自身体内毒性。但若无五毒教心法配合，一旦服用立\n"
                                "即暴毙。（服用限制参见 help dazhao，此珠下线不丢失)。\n" NOR);
                set("value", 500000);
                set("unit", "颗");             
                set("only_do_effect", 1);
                set("do_effect", 1);
        }
}

int do_effect(object me)
{
        if (environment(this_object()) != me)
                return notify_fail("你身上没有这样东西。\n");
                
        if (query("do_effect") < 1)
                return notify_fail("五毒珠已经被服用过了。\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你内力修为不足，恐怕服用后难以吸收毒性。\n");

        if( query("neili", me)<10000 )
                return notify_fail("你内力不足，服用后恐怕难以运功抵御剧毒。\n");

        if( query("can_perform/qianzhu-wandushou/suck_time", me) >= 5 )
                return notify_fail("你已经吸收了足够的毒素，不需要再重复吸取了。\n");
        
        if( time()-query("last_eating_wudu_zhu", me)<3600 )
                return notify_fail("你刚吸收过毒素，不宜再吸收！\n");

        message_vision(HIM "$N" HIM "服下一颗五毒珠，毒珠入口即化，片刻，$N" HIM "面色凝重，似乎剧毒正在\n"
                       "周身游走 ……\n" NOR, me);
                       
        if (me->query_skill("wudu-qishu", 1) < 300 || me->query_skill("wudu-jing", 1) < 200 ||
            me->query_skill("qianzhu-wandushou",1)<800 || query("family/family_name", me) != "五毒教" )
        {
                if( !query("special_skill/zhuha", me) )
                {
                        message_vision(HIR "\n$N" HIR "突然痛苦无比，倒地暴毙，模样十分恐怖！\n" NOR, me);
                        set_temp("die_reason", "服用五毒珠后暴毙", me);
                        me->die();                        
                        destruct(this_object());
                        return 1;
                }
                else
                {
                        tell_object(me, HIW "由于你有朱蛤奇毒附身，五毒珠剧毒已被全部化解。\n" NOR);
                        destruct(this_object());
                        return 1;                        
                }
        }
        
        set("do_effect", 0);

        set("last_eating_wudu_zhu", time(), me);
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, 0);
        
        //destruct(this_object());
        return 1;
}

void start_xishou(object me, int i)
{
        string* msg = ({
                "你开始运功抵御五毒珠的剧毒，真气已由丹田升起，并迅速在全身游走 ……\n",
                "你感觉五毒珠剧毒凶猛无比，普通真气竟难以与之抗衡，情急之下忙运起五毒教密门心法 ……\n",
                "渐渐地，五毒珠剧毒开始有规律地运动，并随着五毒教心法的牵引而游走 ……\n",
                "你开始施展千蛛万毒手心法，吸收五毒珠中的毒素 ……\n",
                "一柱香后，毒素开始向你的十指移动，并开始与你体内的真气融合 ……\n",        
        });
        
        int ran;
        
        if (! objectp(me))
        {
                destruct(this_object());
                return;
        }
        
        if (environment(this_object()) != me)
        {
                tell_object(me, HIG "五毒珠已丢失，吸取失败！\n" NOR);
                destruct(this_object());
                return;
        }
        
        if (i >= sizeof(msg))
        {
                // zhuha玩家60%几率吸收成功，其他玩家30%吸收成功
                if( query("special_skill/zhuha", me) )
                {
                        ran = 6;        
                }
                else
                {
                        ran = 3;
                }
                
                if (random(10) >= ran) // 吸收失败
                {
                        tell_object(me, HIG "突然间，你感觉五毒珠中的剧毒消失得无影无踪，竟未被你体内真气吸收，实在遗憾。\n" NOR);
                        destruct(this_object());
                        return;
                }
                
                tell_object(me, HIG "顷刻间，你只觉得所有毒素已被你真气吸收，融合在一起，聚集在体内，为你所用！\n" NOR);
                tell_object(me, HIG "你将真气运回丹田，感觉舒泰无比！\n" NOR);
                tell_object(me, HIR "恭喜你，成功吸收了五毒珠中的剧毒！\n" NOR);
                addn("can_perform/qianzhu-wandushou/suck_time", 1, me);
                if( query("can_perform/qianzhu-wandushou/suck_time", me) >= 5 )
                {
                        tell_object(me, HIM "恭喜你，已经练成了举世无双的绝学—万毒穿心手！\n" NOR);
                        set("can_perform/qianzhu-wandushou/chuan", 1, me);
                        me->save();
                }
                destruct(this_object());
                return;        
        }

        tell_object(me, HIW + msg[i] + NOR);
        
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, i + 1);
        
}

int query_autoload()
{
                return 1;
}
