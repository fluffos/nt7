// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m麒麟怪[2;37;0m[2;37;0m", ({"kirin"}));        
        set("gender", "男性");                
        set("long", "这是一只怪怪的麒麟。[2;37;0m
它是司徒拔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "stupid");
        set("owner_name", "司徒拔");
        set_temp("owner", "stupid");
        set_temp("owner_name", "司徒拔");
        ::setup();
}
