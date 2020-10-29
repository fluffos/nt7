// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuq"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是接不归的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jbg");
        set("owner_name", "接不归");
        set_temp("owner", "jbg");
        set_temp("owner_name", "接不归");
        ::setup();
}
