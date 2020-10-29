// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("有你与[2;37;0m[2;37;0m", ({"papayb"}));        
        set("gender", "男性");                
        set("long", "有你与[2;37;0m
它是女乃大的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "papaya");
        set("owner_name", "女乃大");
        set_temp("owner", "papaya");
        set_temp("owner_name", "女乃大");
        ::setup();
}
