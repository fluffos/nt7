// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小火鸟[2;37;0m[2;37;0m", ({"ormerfire"}));        
        set("gender", "男性");                
        set("long", "小火鸟[2;37;0m
它是鲍俊德的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ormery");
        set("owner_name", "鲍俊德");
        set_temp("owner", "ormery");
        set_temp("owner_name", "鲍俊德");
        ::setup();
}
