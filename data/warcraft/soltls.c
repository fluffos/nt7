// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拜拜[2;37;0m[2;37;0m", ({"seebye"}));        
        set("gender", "女性");                
        set("long", "拜拜[2;37;0m
它是第五言福的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "soltls");
        set("owner_name", "第五言福");
        set_temp("owner", "soltls");
        set_temp("owner_name", "第五言福");
        ::setup();
}
