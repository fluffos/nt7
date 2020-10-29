// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血魔[2;37;0m[2;37;0m", ({"xuemo"}));        
        set("gender", "男性");                
        set("long", "来自地狱----------->死亡代言者[2;37;0m
它是找死的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "die");
        set("owner_name", "找死");
        set_temp("owner", "die");
        set_temp("owner_name", "找死");
        ::setup();
}
