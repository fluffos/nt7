// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m大概[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "威猛无敌2B一个[2;37;0m
它是如花的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "flower");
        set("owner_name", "如花");
        set_temp("owner", "flower");
        set_temp("owner_name", "如花");
        ::setup();
}
