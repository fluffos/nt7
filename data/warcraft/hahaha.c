// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嘻嘻[2;37;0m[2;37;0m", ({"xixixi"}));        
        set("gender", "男性");                
        set("long", "xxx[2;37;0m
它是哈哈尔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hahaha");
        set("owner_name", "哈哈尔");
        set_temp("owner", "hahaha");
        set_temp("owner_name", "哈哈尔");
        ::setup();
}
