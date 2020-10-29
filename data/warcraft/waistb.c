// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无敌中[2;37;0m[2;37;0m", ({"waistblong"}));        
        set("gender", "男性");                
        set("long", "八粉[2;37;0m
它是腰带仓二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "waistb");
        set("owner_name", "腰带仓二");
        set_temp("owner", "waistb");
        set_temp("owner_name", "腰带仓二");
        ::setup();
}
