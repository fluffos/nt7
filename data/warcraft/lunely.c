// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("御剑乘风来[2;37;0m[2;37;0m", ({"lvlely"}));        
        set("gender", "女性");                
        set("long", "除魔天地间[2;37;0m
它是高处肾寒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lunely");
        set("owner_name", "高处肾寒");
        set_temp("owner", "lunely");
        set_temp("owner_name", "高处肾寒");
        ::setup();
}
