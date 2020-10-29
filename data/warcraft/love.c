// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("思琪[2;37;0m[2;37;0m", ({"lovew"}));        
        set("gender", "女性");                
        set("long", "思琪[2;37;0m
它是夜琉璃的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "love");
        set("owner_name", "夜琉璃");
        set_temp("owner", "love");
        set_temp("owner_name", "夜琉璃");
        ::setup();
}
