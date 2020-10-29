// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m光头龙[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "光头龙[2;37;0m
它是小球球的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ovo");
        set("owner_name", "小球球");
        set_temp("owner", "ovo");
        set_temp("owner_name", "小球球");
        ::setup();
}
