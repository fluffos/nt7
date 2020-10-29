// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿猫[2;37;0m[2;37;0m", ({"ccat"}));        
        set("gender", "女性");                
        set("long", "一只小猫[2;37;0m
它是阿曼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aman");
        set("owner_name", "阿曼");
        set_temp("owner", "aman");
        set_temp("owner_name", "阿曼");
        ::setup();
}
