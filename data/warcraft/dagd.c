// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火凤凰[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火凤凰[2;37;0m
它是朵朵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dagd");
        set("owner_name", "朵朵");
        set_temp("owner", "dagd");
        set_temp("owner_name", "朵朵");
        ::setup();
}
