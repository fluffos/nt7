#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "乾坤精魄" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你天生比一般人拥有更高的精气修为，可提升最大精气值30%。不需要运用。\n");
}

