// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟怪[2;37;0m[2;37;0m", ({"kiringwai"}));        
        set("gender", "男性");                
        set("long", "这是传说中的神兽麒麟怪。[2;37;0m
它是乐海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kychung");
        set("owner_name", "乐海");
        set_temp("owner", "kychung");
        set_temp("owner_name", "乐海");
        ::setup();
}
