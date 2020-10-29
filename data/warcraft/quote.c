// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"myhorse"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是引用党的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "quote");
        set("owner_name", "引用党");
        set_temp("owner", "quote");
        set_temp("owner_name", "引用党");
        ::setup();
}
