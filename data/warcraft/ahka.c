// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神雀[2;37;0m[2;37;0m", ({"hahaha"}));        
        set("gender", "女性");                
        set("long", "宇宙最强[2;37;0m
它是完美男生的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ahka");
        set("owner_name", "完美男生");
        set_temp("owner", "ahka");
        set_temp("owner_name", "完美男生");
        ::setup();
}
