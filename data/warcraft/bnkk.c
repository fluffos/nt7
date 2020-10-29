// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m走火入魔[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$RED$走火入魔[2;37;0m
它是毒虫虫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bnkk");
        set("owner_name", "毒虫虫");
        set_temp("owner", "bnkk");
        set_temp("owner_name", "毒虫虫");
        ::setup();
}
