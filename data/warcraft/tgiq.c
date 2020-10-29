// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青龙[2;37;0m[2;37;0m", ({"tgiqd"}));        
        set("gender", "男性");                
        set("long", "这其实是宝马[2;37;0m
它是先天杨威的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tgiq");
        set("owner_name", "先天杨威");
        set_temp("owner", "tgiq");
        set_temp("owner_name", "先天杨威");
        ::setup();
}
