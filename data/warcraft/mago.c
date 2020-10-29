// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("吉他[2;37;0m[2;37;0m", ({"guide"}));        
        set("gender", "男性");                
        set("long", "吉他[2;37;0m
它是疯狂无敌的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mago");
        set("owner_name", "疯狂无敌");
        set_temp("owner", "mago");
        set_temp("owner_name", "疯狂无敌");
        ::setup();
}
