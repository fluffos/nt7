// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("先女[2;37;0m[2;37;0m", ({"yunv"}));        
        set("gender", "女性");                
        set("long", "美如天先[2;37;0m
它是廖郁桦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "liaoyuhua");
        set("owner_name", "廖郁桦");
        set_temp("owner", "liaoyuhua");
        set_temp("owner_name", "廖郁桦");
        ::setup();
}
