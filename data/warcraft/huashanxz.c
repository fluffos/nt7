// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("华山青龙[2;37;0m[2;37;0m", ({"hsdragon"}));        
        set("gender", "男性");                
        set("long", "华山青龙[2;37;0m
它是张华山的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huashanxz");
        set("owner_name", "张华山");
        set_temp("owner", "huashanxz");
        set_temp("owner_name", "张华山");
        ::setup();
}
