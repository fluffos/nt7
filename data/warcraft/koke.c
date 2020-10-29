// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雀神[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "一只凤凰[2;37;0m
它是月容的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "koke");
        set("owner_name", "月容");
        set_temp("owner", "koke");
        set_temp("owner_name", "月容");
        ::setup();
}
