// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("接啊[2;37;0m[2;37;0m", ({"aodhoa"}));        
        set("gender", "男性");                
        set("long", "接啊[2;37;0m
它是搬运工的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "byg");
        set("owner_name", "搬运工");
        set_temp("owner", "byg");
        set_temp("owner_name", "搬运工");
        ::setup();
}
