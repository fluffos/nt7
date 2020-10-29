// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是力捧巨擘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lpx");
        set("owner_name", "力捧巨擘");
        set_temp("owner", "lpx");
        set_temp("owner_name", "力捧巨擘");
        ::setup();
}
