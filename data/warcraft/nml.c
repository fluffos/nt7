// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥煤[2;37;0m[2;37;0m", ({"nmride"}));        
        set("gender", "女性");                
        set("long", "泥煤[2;37;0m
它是鱼湾弯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nml");
        set("owner_name", "鱼湾弯");
        set_temp("owner", "nml");
        set_temp("owner_name", "鱼湾弯");
        ::setup();
}
