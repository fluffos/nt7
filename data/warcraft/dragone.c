// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"dragon_e"}));        
        set("gender", "女性");                
        set("long", "龙[2;37;0m
它是龙王五的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dragone");
        set("owner_name", "龙王五");
        set_temp("owner", "dragone");
        set_temp("owner_name", "龙王五");
        ::setup();
}
