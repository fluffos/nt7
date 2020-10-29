// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宁小二[2;37;0m[2;37;0m", ({"ningbbb"}));        
        set("gender", "女性");                
        set("long", "宁小二[2;37;0m
它是宁二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ningb");
        set("owner_name", "宁二");
        set_temp("owner", "ningb");
        set_temp("owner_name", "宁二");
        ::setup();
}
