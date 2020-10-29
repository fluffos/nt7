// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火机[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "火机[2;37;0m
它是阿青的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aqing");
        set("owner_name", "阿青");
        set_temp("owner", "aqing");
        set_temp("owner_name", "阿青");
        ::setup();
}
