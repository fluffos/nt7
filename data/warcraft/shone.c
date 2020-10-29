// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"mjt"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是月影的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shone");
        set("owner_name", "月影");
        set_temp("owner", "shone");
        set_temp("owner_name", "月影");
        ::setup();
}
