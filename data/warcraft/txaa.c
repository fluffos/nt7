// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱[2;37;0m[2;37;0m", ({"zzzzz"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是头彩阿阿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txaa");
        set("owner_name", "头彩阿阿");
        set_temp("owner", "txaa");
        set_temp("owner_name", "头彩阿阿");
        ::setup();
}
