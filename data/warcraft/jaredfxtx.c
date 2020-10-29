// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米麒麟[2;37;0m[2;37;0m", ({"toucai"}));        
        set("gender", "女性");                
        set("long", "米色的麒麟[2;37;0m
它是吸吸吸的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jaredfxtx");
        set("owner_name", "吸吸吸");
        set_temp("owner", "jaredfxtx");
        set_temp("owner_name", "吸吸吸");
        ::setup();
}
