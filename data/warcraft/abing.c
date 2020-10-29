// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("意义[2;37;0m[2;37;0m", ({"yiyi"}));        
        set("gender", "男性");                
        set("long", "意义[2;37;0m
它是阿丙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "abing");
        set("owner_name", "阿丙");
        set_temp("owner", "abing");
        set_temp("owner_name", "阿丙");
        ::setup();
}
