// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小香猪[2;37;0m[2;37;0m", ({"xxz"}));        
        set("gender", "男性");                
        set("long", "小香猪[2;37;0m
它是不通护甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btarmor");
        set("owner_name", "不通护甲");
        set_temp("owner", "btarmor");
        set_temp("owner_name", "不通护甲");
        ::setup();
}
