// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥煤[2;37;0m[2;37;0m", ({"nmride"}));        
        set("gender", "女性");                
        set("long", "泥煤[2;37;0m
它是晴鱼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nmg");
        set("owner_name", "晴鱼");
        set_temp("owner", "nmg");
        set_temp("owner_name", "晴鱼");
        ::setup();
}
