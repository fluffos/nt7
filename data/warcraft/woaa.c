// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小麻雀[2;37;0m[2;37;0m", ({"woaaa"}));        
        set("gender", "男性");                
        set("long", "小麻雀!!![2;37;0m
它是夜九的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "woaa");
        set("owner_name", "夜九");
        set_temp("owner", "woaa");
        set_temp("owner_name", "夜九");
        ::setup();
}
