
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "逆转乾坤" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你天生受到上天的青睐，拥有逆转乾坤之神力，具备以下特殊能力：\n"
                           "命中提升：+10%\n"
                           "研究次数：+10 次\n"
                           "内力上限：+500\n"
                           "精力上限：+500\n"
                           "其他特效：如有[仙风道骨]技能可再额外提升研究次数10次\n"
                           "不需要运用。\n");
}

