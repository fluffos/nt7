// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaoyyy"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药越狱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoyy");
        set("owner_name", "药越狱");
        set_temp("owner", "yaoyy");
        set_temp("owner_name", "药越狱");
        ::setup();
}
