// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡[2;37;0m[2;37;0m", ({"zzss"}));        
        set("gender", "男性");                
        set("long", "这是一只变异的小小鸟[2;37;0m
它是小强的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zzs");
        set("owner_name", "小强");
        set_temp("owner", "zzs");
        set_temp("owner_name", "小强");
        ::setup();
}
