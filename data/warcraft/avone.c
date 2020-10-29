// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎虎虎[2;37;0m[2;37;0m", ({"avtiger"}));        
        set("gender", "男性");                
        set("long", "虎虎虎[2;37;0m
它是苍老师的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "avone");
        set("owner_name", "苍老师");
        set_temp("owner", "avone");
        set_temp("owner_name", "苍老师");
        ::setup();
}
