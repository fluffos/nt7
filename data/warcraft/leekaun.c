// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("来福[2;37;0m[2;37;0m", ({"laifu"}));        
        set("gender", "女性");                
        set("long", "喵喵喵[2;37;0m
它是李少的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "leekaun");
        set("owner_name", "李少");
        set_temp("owner", "leekaun");
        set_temp("owner_name", "李少");
        ::setup();
}
