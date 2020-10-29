// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("四号[2;37;0m[2;37;0m", ({"cafe"}));        
        set("gender", "女性");                
        set("long", "四号[2;37;0m
它是咖啡四号的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ccftony");
        set("owner_name", "咖啡四号");
        set_temp("owner", "ccftony");
        set_temp("owner_name", "咖啡四号");
        ::setup();
}
