// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("第飞翔[2;37;0m[2;37;0m", ({"xixiddd"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是喜第的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixid");
        set("owner_name", "喜第");
        set_temp("owner", "xixid");
        set_temp("owner_name", "喜第");
        ::setup();
}
