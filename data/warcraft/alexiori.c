// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m鸟人[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "男性");                
        set("long", "鸟人[2;37;0m
它是九天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "alexiori");
        set("owner_name", "九天");
        set_temp("owner", "alexiori");
        set_temp("owner_name", "九天");
        ::setup();
}
