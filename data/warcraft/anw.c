// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m妖兽[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "$HIG$妖兽[2;37;0m
它是暗舞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "anw");
        set("owner_name", "暗舞");
        set_temp("owner", "anw");
        set_temp("owner_name", "暗舞");
        ::setup();
}
