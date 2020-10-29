// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱神[2;37;0m[2;37;0m", ({"winner"}));        
        set("gender", "女性");                
        set("long", "天下有情人终成眷属[2;37;0m
它是郭襄的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "guoxiang");
        set("owner_name", "郭襄");
        set_temp("owner", "guoxiang");
        set_temp("owner_name", "郭襄");
        ::setup();
}
