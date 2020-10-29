// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是神剑传说的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "learner");
        set("owner_name", "神剑传说");
        set_temp("owner", "learner");
        set_temp("owner_name", "神剑传说");
        ::setup();
}
