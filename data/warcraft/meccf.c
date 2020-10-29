// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("远古[2;37;0m[2;37;0m", ({"meccfpet"}));        
        set("gender", "男性");                
        set("long", "远古[2;37;0m
它是阿兰啸的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "meccf");
        set("owner_name", "阿兰啸");
        set_temp("owner", "meccf");
        set_temp("owner_name", "阿兰啸");
        ::setup();
}
