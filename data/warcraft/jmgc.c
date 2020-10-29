// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小叶珠子[2;37;0m[2;37;0m", ({"plh"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是狙魔三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jmgc");
        set("owner_name", "狙魔三");
        set_temp("owner", "jmgc");
        set_temp("owner_name", "狙魔三");
        ::setup();
}
