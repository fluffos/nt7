// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是力劈华山的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lpq");
        set("owner_name", "力劈华山");
        set_temp("owner", "lpq");
        set_temp("owner_name", "力劈华山");
        ::setup();
}
