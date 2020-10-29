// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m老龟[2;37;0m[2;37;0m", ({"wuwu"}));        
        set("gender", "男性");                
        set("long", "老龟[2;37;0m
它是八路的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "eight");
        set("owner_name", "八路");
        set_temp("owner", "eight");
        set_temp("owner_name", "八路");
        ::setup();
}
