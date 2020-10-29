// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波多结衣[2;37;0m[2;37;0m", ({"plf"}));        
        set("gender", "男性");                
        set("long", "不解释[2;37;0m
它是狙魔一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jmga");
        set("owner_name", "狙魔一");
        set_temp("owner", "jmga");
        set_temp("owner_name", "狙魔一");
        ::setup();
}
