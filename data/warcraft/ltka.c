// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小波多[2;37;0m[2;37;0m", ({"pdp"}));        
        set("gender", "女性");                
        set("long", "小小波多[2;37;0m
它是立库一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ltka");
        set("owner_name", "立库一");
        set_temp("owner", "ltka");
        set_temp("owner_name", "立库一");
        ::setup();
}
