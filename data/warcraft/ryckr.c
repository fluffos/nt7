// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m天猫[2;37;0m[2;37;0m", ({"tianmao"}));        
        set("gender", "男性");                
        set("long", "$HIR$天猫[2;37;0m
它是东方楚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ryckr");
        set("owner_name", "东方楚");
        set_temp("owner", "ryckr");
        set_temp("owner_name", "东方楚");
        ::setup();
}
