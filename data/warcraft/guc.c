// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宠物[2;37;0m[2;37;0m", ({"cws"}));        
        set("gender", "女性");                
        set("long", "dx[2;37;0m
它是搏叫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "guc");
        set("owner_name", "搏叫");
        set_temp("owner", "guc");
        set_temp("owner_name", "搏叫");
        ::setup();
}
