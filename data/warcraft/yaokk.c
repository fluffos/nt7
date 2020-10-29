// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咔咔咔[2;37;0m[2;37;0m", ({"yaokkk"}));        
        set("gender", "男性");                
        set("long", "咔咔咔[2;37;0m
它是药可控的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaokk");
        set("owner_name", "药可控");
        set_temp("owner", "yaokk");
        set_temp("owner_name", "药可控");
        ::setup();
}
