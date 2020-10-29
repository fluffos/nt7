// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m兽兽[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "男性");                
        set("long", "$RED$兽兽[2;37;0m
它是剑魔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pker");
        set("owner_name", "剑魔");
        set_temp("owner", "pker");
        set_temp("owner_name", "剑魔");
        ::setup();
}
