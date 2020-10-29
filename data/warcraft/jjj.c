// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("华山小[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "女性");                
        set("long", "华山小[2;37;0m
它是华山大的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jjj");
        set("owner_name", "华山大");
        set_temp("owner", "jjj");
        set_temp("owner_name", "华山大");
        ::setup();
}
