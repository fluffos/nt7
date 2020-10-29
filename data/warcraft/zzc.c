// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛟龙[2;37;0m[2;37;0m", ({"jiaolong"}));        
        set("gender", "男性");                
        set("long", "天下无敌[2;37;0m
它是牛君的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zzc");
        set("owner_name", "牛君");
        set_temp("owner", "zzc");
        set_temp("owner_name", "牛君");
        ::setup();
}
