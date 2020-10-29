// queen.c  九天玄女

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "九天玄女" NOR; }

int perform(object me, string skill)
{
        return notify_fail("九天玄女这项技能不需要运用。\n");
}
