// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是思春春的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zzcc");
        set("owner_name", "思春春");
        set_temp("owner", "zzcc");
        set_temp("owner_name", "思春春");
        ::setup();
}
