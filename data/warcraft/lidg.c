// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咖啡色[2;37;0m[2;37;0m", ({"kfx"}));        
        set("gender", "男性");                
        set("long", "咖啡色[2;37;0m
它是炼水的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidg");
        set("owner_name", "炼水");
        set_temp("owner", "lidg");
        set_temp("owner_name", "炼水");
        ::setup();
}
