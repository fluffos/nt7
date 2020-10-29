// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m甲甲[2;37;0m[2;37;0m", ({"jiajia"}));        
        set("gender", "男性");                
        set("long", "$HIG$甲甲[2;37;0m
它是阿甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ajia");
        set("owner_name", "阿甲");
        set_temp("owner", "ajia");
        set_temp("owner_name", "阿甲");
        ::setup();
}
