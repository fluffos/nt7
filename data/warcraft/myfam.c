// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "女性");                
        set("long", "一匹马[2;37;0m
它是大刀无敌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "myfam");
        set("owner_name", "大刀无敌");
        set_temp("owner", "myfam");
        set_temp("owner_name", "大刀无敌");
        ::setup();
}
