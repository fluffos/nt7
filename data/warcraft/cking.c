// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美丽的童话[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "女性");                
        set("long", "美丽的童话[2;37;0m
它是阿杰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cking");
        set("owner_name", "阿杰");
        set_temp("owner", "cking");
        set_temp("owner_name", "阿杰");
        ::setup();
}
