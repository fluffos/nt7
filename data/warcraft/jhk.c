// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("稻香[2;37;0m[2;37;0m", ({"jhkkkk"}));        
        set("gender", "男性");                
        set("long", "什么[2;37;0m
它是味道的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jhk");
        set("owner_name", "味道");
        set_temp("owner", "jhk");
        set_temp("owner_name", "味道");
        ::setup();
}
