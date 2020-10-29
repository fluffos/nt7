// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("如风[2;37;0m[2;37;0m", ({"shen"}));        
        set("gender", "男性");                
        set("long", "小猫猫[2;37;0m
它是沈沧海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xinxiner");
        set("owner_name", "沈沧海");
        set_temp("owner", "xinxiner");
        set_temp("owner_name", "沈沧海");
        ::setup();
}
