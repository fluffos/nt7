// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鹅鹅鹅[2;37;0m[2;37;0m", ({"yaoeee"}));        
        set("gender", "男性");                
        set("long", "鹅鹅鹅[2;37;0m
它是药夜夜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoee");
        set("owner_name", "药夜夜");
        set_temp("owner", "yaoee");
        set_temp("owner_name", "药夜夜");
        ::setup();
}
