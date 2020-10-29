// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("别摸我[2;37;0m[2;37;0m", ({"biudi"}));        
        set("gender", "女性");                
        set("long", "摸一下1000gold[2;37;0m
它是一根葱的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gaokeyub");
        set("owner_name", "一根葱");
        set_temp("owner", "gaokeyub");
        set_temp("owner_name", "一根葱");
        ::setup();
}
