// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m啸天[2;37;0m[2;37;0m", ({"yutian"}));        
        set("gender", "男性");                
        set("long", "啸天[2;37;0m
它是枫无的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bay");
        set("owner_name", "枫无");
        set_temp("owner", "bay");
        set_temp("owner_name", "枫无");
        ::setup();
}
