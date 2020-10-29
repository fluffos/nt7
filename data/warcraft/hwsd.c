// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是华山小贼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hwsd");
        set("owner_name", "华山小贼");
        set_temp("owner", "hwsd");
        set_temp("owner_name", "华山小贼");
        ::setup();
}
