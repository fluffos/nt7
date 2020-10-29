// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天皇[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "日本天皇[2;37;0m
它是不会下毒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xxguiji");
        set("owner_name", "不会下毒");
        set_temp("owner", "xxguiji");
        set_temp("owner_name", "不会下毒");
        ::setup();
}
