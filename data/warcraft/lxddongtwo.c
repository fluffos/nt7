// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞儿鸟[2;37;0m[2;37;0m", ({"flyqueque"}));        
        set("gender", "女性");                
        set("long", "飞[2;37;0m
它是风冰凝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lxddongtwo");
        set("owner_name", "风冰凝");
        set_temp("owner", "lxddongtwo");
        set_temp("owner_name", "风冰凝");
        ::setup();
}
