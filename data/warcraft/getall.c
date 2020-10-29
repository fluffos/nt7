// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("强大生物[2;37;0m[2;37;0m", ({"dalong"}));        
        set("gender", "女性");                
        set("long", "强大生物[2;37;0m
它是拿元宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "getall");
        set("owner_name", "拿元宝");
        set_temp("owner", "getall");
        set_temp("owner_name", "拿元宝");
        ::setup();
}
