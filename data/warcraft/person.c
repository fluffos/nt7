// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("旖旎[2;37;0m[2;37;0m", ({"graceful"}));        
        set("gender", "女性");                
        set("long", "婀娜多姿[2;37;0m
它是翘楚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "person");
        set("owner_name", "翘楚");
        set_temp("owner", "person");
        set_temp("owner_name", "翘楚");
        ::setup();
}
