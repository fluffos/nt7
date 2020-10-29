// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马儿跑[2;37;0m[2;37;0m", ({"maerpao"}));        
        set("gender", "女性");                
        set("long", "马儿跑[2;37;0m
它是极无极的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "driver");
        set("owner_name", "极无极");
        set_temp("owner", "driver");
        set_temp("owner_name", "极无极");
        ::setup();
}
