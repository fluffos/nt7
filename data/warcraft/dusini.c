// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("知了知了[2;37;0m[2;37;0m", ({"zlzl"}));        
        set("gender", "女性");                
        set("long", "知了叫了[2;37;0m
它是肚丝腻的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dusini");
        set("owner_name", "肚丝腻");
        set_temp("owner", "dusini");
        set_temp("owner_name", "肚丝腻");
        ::setup();
}
