// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽王之王[2;37;0m[2;37;0m", ({"ant"}));        
        set("gender", "女性");                
        set("long", "    [2;37;0m
它是猫王的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "logoo");
        set("owner_name", "猫王");
        set_temp("owner", "logoo");
        set_temp("owner_name", "猫王");
        ::setup();
}
