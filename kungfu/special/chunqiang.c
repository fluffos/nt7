#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "唇枪舌剑" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你拥有异人之口才，能够混淆是非，颠倒黑白。于炎黄黑店、普通NPC商店购买\n"
                           "物品可获得市价9折的优惠。同时，具备八面玲珑的相关特效。不需要运用。\n");
}

