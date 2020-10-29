
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "练武奇才" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你出生于武学世家，天生聪颖，乃练武上等之材。研究技能时可提升5%效率。不需要运用。\n");
}

