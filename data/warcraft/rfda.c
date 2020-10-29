// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"srfda"}));        
        set("gender", "男性");                
        set("long", "AAAA[2;37;0m
它是冷风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rfda");
        set("owner_name", "冷风");
        set_temp("owner", "rfda");
        set_temp("owner_name", "冷风");
        ::setup();
}
