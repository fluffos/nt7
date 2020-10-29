// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("髅梵[2;37;0m[2;37;0m", ({"annd"}));        
        set("gender", "女性");                
        set("long", "若有若无，飘渺无影[2;37;0m
它是伏魔鸿禧的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jicks");
        set("owner_name", "伏魔鸿禧");
        set_temp("owner", "jicks");
        set_temp("owner_name", "伏魔鸿禧");
        ::setup();
}
