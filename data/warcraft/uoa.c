// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("批批熊[2;37;0m[2;37;0m", ({"vva"}));        
        set("gender", "男性");                
        set("long", "批批熊[2;37;0m
它是可乐汉堡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "uoa");
        set("owner_name", "可乐汉堡");
        set_temp("owner", "uoa");
        set_temp("owner_name", "可乐汉堡");
        ::setup();
}
