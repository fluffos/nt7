// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m血汪洋[2;37;0m[2;37;0m[2;37;0m", ({"xuehai"}));        
        set("gender", "男性");                
        set("long", "昆仑剑出血汪洋，万里直驱黄河黄[2;37;0m
它是木中寒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "drollor");
        set("owner_name", "木中寒");
        set_temp("owner", "drollor");
        set_temp("owner_name", "木中寒");
        ::setup();
}
