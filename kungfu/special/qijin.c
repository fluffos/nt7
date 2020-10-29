// qijin.c 奇筋异骨
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "奇筋异骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIG "此天性者天生骨骼精奇，乃百年难遇的练武奇才。\n"
                               "拥有此技能者可使研究技能次数限制加倍，即如果你\n"
                               "目前每次可以研究300次， 则拥有该技能后可每次研\n"
                               "究600次。同时， 拥有该技能者在研究技能时所消耗\n"
                               "的潜能减少10%，即如果你研究600次所消耗的潜能原\n"
                               "为600点，则此时为540点。如研究次数小于10次则不\n"
                               "产生减少潜能消耗10%的效果。\n" NOR);

}
