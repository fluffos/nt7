// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "男性");                
        set("long", "墨鱼墨鱼[2;37;0m
它是遥甲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "uliann");
        set("owner_name", "遥甲");
        set_temp("owner", "uliann");
        set_temp("owner_name", "遥甲");
        ::setup();
}
