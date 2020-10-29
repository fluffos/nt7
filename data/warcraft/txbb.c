// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱[2;37;0m[2;37;0m", ({"zzzz"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是头彩宝宝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txbb");
        set("owner_name", "头彩宝宝");
        set_temp("owner", "txbb");
        set_temp("owner_name", "头彩宝宝");
        ::setup();
}
