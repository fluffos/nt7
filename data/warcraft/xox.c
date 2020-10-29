// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呵呵呵[2;37;0m[2;37;0m", ({"oso"}));        
        set("gender", "男性");                
        set("long", "                          [2;37;0m
它是黑夜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xox");
        set("owner_name", "黑夜");
        set_temp("owner", "xox");
        set_temp("owner_name", "黑夜");
        ::setup();
}
