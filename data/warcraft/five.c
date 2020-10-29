// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小五子[2;37;0m[2;37;0m", ({"fivefive"}));        
        set("gender", "男性");                
        set("long", "就是一条龙[2;37;0m
它是太上忘情的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "five");
        set("owner_name", "太上忘情");
        set_temp("owner", "five");
        set_temp("owner_name", "太上忘情");
        ::setup();
}
