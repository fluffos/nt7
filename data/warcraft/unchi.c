// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金朱[2;37;0m[2;37;0m", ({"pigpigs"}));        
        set("gender", "女性");                
        set("long", "金朱[2;37;0m
它是不大的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "unchi");
        set("owner_name", "不大");
        set_temp("owner", "unchi");
        set_temp("owner_name", "不大");
        ::setup();
}
