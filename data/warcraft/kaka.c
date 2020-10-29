// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"xing"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是咔咔的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kaka");
        set("owner_name", "咔咔");
        set_temp("owner", "kaka");
        set_temp("owner_name", "咔咔");
        ::setup();
}
