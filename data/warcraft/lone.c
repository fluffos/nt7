// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m鬼雕[2;37;0m[2;37;0m", ({"eagle"}));        
        set("gender", "男性");                
        set("long", "它是神雕的兄弟鬼雕。[2;37;0m
它是独孤仁的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lone");
        set("owner_name", "独孤仁");
        set_temp("owner", "lone");
        set_temp("owner_name", "独孤仁");
        ::setup();
}
