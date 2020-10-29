// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡[2;37;0m[2;37;0m", ({"zzww"}));        
        set("gender", "男性");                
        set("long", "这是一只变异的小小鸟[2;37;0m
它是不死小强的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zzw");
        set("owner_name", "不死小强");
        set_temp("owner", "zzw");
        set_temp("owner_name", "不死小强");
        ::setup();
}
