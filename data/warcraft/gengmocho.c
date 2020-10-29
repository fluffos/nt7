// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("紫金葫芦[2;37;0m[2;37;0m", ({"cho"}));        
        set("gender", "女性");                
        set("long", "ff[2;37;0m
它是君莫愁的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gengmocho");
        set("owner_name", "君莫愁");
        set_temp("owner", "gengmocho");
        set_temp("owner_name", "君莫愁");
        ::setup();
}
