// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猫[2;37;0m[2;37;0m", ({"mao"}));        
        set("gender", "女性");                
        set("long", "小花猫[2;37;0m
它是行云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gogo");
        set("owner_name", "行云");
        set_temp("owner", "gogo");
        set_temp("owner_name", "行云");
        ::setup();
}
