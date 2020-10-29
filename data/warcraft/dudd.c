// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蹬蹬马[2;37;0m[2;37;0m", ({"popa"}));        
        set("gender", "男性");                
        set("long", "口袋空空的[2;37;0m
它是艾登伯格的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dudd");
        set("owner_name", "艾登伯格");
        set_temp("owner", "dudd");
        set_temp("owner_name", "艾登伯格");
        ::setup();
}
