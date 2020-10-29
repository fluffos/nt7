// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("杨生蓝雀[2;37;0m[2;37;0m", ({"woi"}));        
        set("gender", "女性");                
        set("long", "杨生蓝雀!!![2;37;0m
它是夜世的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "woii");
        set("owner_name", "夜世");
        set_temp("owner", "woii");
        set_temp("owner_name", "夜世");
        ::setup();
}
