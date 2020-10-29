// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("红色逼毛[2;37;0m[2;37;0m", ({"xcggzq"}));        
        set("gender", "男性");                
        set("long", "一根红色的逼毛[2;37;0m
它是胡搞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xcgg");
        set("owner_name", "胡搞");
        set_temp("owner", "xcgg");
        set_temp("owner_name", "胡搞");
        ::setup();
}
