// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽期[2;37;0m[2;37;0m", ({"aay"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是组药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "faty");
        set("owner_name", "组药");
        set_temp("owner", "faty");
        set_temp("owner_name", "组药");
        ::setup();
}
