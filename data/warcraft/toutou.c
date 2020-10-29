// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟头子[2;37;0m[2;37;0m", ({"guitou"}));        
        set("gender", "男性");                
        set("long", "乌龟头子[2;37;0m
它是偷遍天的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "toutou");
        set("owner_name", "偷遍天");
        set_temp("owner", "toutou");
        set_temp("owner_name", "偷遍天");
        ::setup();
}
