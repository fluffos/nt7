// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白色圣诞[2;37;0m[2;37;0m", ({"christmas"}));        
        set("gender", "女性");                
        set("long", "上主，怜悯我这卑微的罪人。 [2;37;0m
它是甜姊儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shelly");
        set("owner_name", "甜姊儿");
        set_temp("owner", "shelly");
        set_temp("owner_name", "甜姊儿");
        ::setup();
}
