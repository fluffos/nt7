// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥煤[2;37;0m[2;37;0m", ({"nmride"}));        
        set("gender", "女性");                
        set("long", "泥煤[2;37;0m
它是鱼晴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nmf");
        set("owner_name", "鱼晴");
        set_temp("owner", "nmf");
        set_temp("owner_name", "鱼晴");
        ::setup();
}
