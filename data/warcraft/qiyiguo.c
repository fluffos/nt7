// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("望望望[2;37;0m[2;37;0m", ({"lalala"}));        
        set("gender", "女性");                
        set("long", "很开心的样子[2;37;0m
它是奇意果的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qiyiguo");
        set("owner_name", "奇意果");
        set_temp("owner", "qiyiguo");
        set_temp("owner_name", "奇意果");
        ::setup();
}
