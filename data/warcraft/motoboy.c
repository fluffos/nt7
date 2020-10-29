// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m老[2;37;0m[2;37;0m", ({"ayia"}));        
        set("gender", "男性");                
        set("long", "千年的老王八[2;37;0m
它是朱七七的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "motoboy");
        set("owner_name", "朱七七");
        set_temp("owner", "motoboy");
        set_temp("owner_name", "朱七七");
        ::setup();
}
