// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("第四青龙[2;37;0m[2;37;0m", ({"sleepbagd"}));        
        set("gender", "男性");                
        set("long", "第四青龙[2;37;0m
它是小妖四号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoyaod");
        set("owner_name", "小妖四号");
        set_temp("owner", "xiaoyaod");
        set_temp("owner_name", "小妖四号");
        ::setup();
}
