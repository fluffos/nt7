// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱焰[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "火红的朱雀[2;37;0m
它是谬思的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mariner");
        set("owner_name", "谬思");
        set_temp("owner", "mariner");
        set_temp("owner_name", "谬思");
        ::setup();
}
