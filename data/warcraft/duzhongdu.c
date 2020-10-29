// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m烽火红尘路[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "红尘炼心路。[2;37;0m
它是大牛魔王的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "duzhongdu");
        set("owner_name", "大牛魔王");
        set_temp("owner", "duzhongdu");
        set_temp("owner_name", "大牛魔王");
        ::setup();
}
