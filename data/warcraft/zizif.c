// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("放依依[2;37;0m[2;37;0m", ({"zizifff"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是姿放的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zizif");
        set("owner_name", "姿放");
        set_temp("owner", "zizif");
        set_temp("owner_name", "姿放");
        ::setup();
}
