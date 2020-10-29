// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("履带[2;37;0m[2;37;0m", ({"tanktank"}));        
        set("gender", "男性");                
        set("long", "汤唯[2;37;0m
它是梅卡瓦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tank");
        set("owner_name", "梅卡瓦");
        set_temp("owner", "tank");
        set_temp("owner_name", "梅卡瓦");
        ::setup();
}
