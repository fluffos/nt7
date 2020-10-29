// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽衣[2;37;0m[2;37;0m", ({"aas"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是于药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fats");
        set("owner_name", "于药");
        set_temp("owner", "fats");
        set_temp("owner_name", "于药");
        ::setup();
}
