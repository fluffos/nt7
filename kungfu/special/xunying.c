// xunying.c 遁影擒踪
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "遁影擒踪" NOR; }

int perform(object me, string skill)
{        
        
        if (me->query("special2/xunying") && ! me->query("thborn/ok"))
        {
                // 2转后可使用一次
                if (me->query("special2/thborn_xunying"))        
                        return notify_fail("对不起，你在今生已经使用过该绝技，无法再次使用了。\n");
        }
        
                if (me->query("combat_exp") < 2700000)
                        return notify_fail("您的实战经验小于270万，无法施展该技能。\n");
                
        if (me->query_temp("special2/xunying"))
        {
                me->set_skill("count", 300);
                me->set_skill("mathematics", 300);
                me->set("special2/xunying", 1);
                if (me->query("thborn/ok"))
                        me->set("special2/thborn_xunying", 1);
                me->save();
                return notify_fail("你获得了阴阳八卦及算术三百级。\n");
        }
        else
        {
                me->set_temp("special2/xunying", 1);
        
                      return notify_fail("你在转生过程中纵观天象，察觉到了人世\n"
                                                "间的诸多奥秘，众生百态尽收眼底。此后\n"
                                             "不再受到架力卸招之技的迷惑。转生后使\n"
                                             "用该绝技可获得阴阳八卦及算术等级三百\n"
                                             "级，但一生仅能使用一次，如果你决定现\n"
                                             "在使用请再输入一次 " HIY "special xunying" NOR " 。\n");
       }
}
