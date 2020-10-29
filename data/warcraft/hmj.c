// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小奇[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "凶猛[2;37;0m
它是独孤求钱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hmj");
        set("owner_name", "独孤求钱");
        set_temp("owner", "hmj");
        set_temp("owner_name", "独孤求钱");
        ::setup();
}
