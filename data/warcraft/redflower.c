// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m乾龙[2;37;0m[2;37;0m", ({"qianlong"}));        
        set("gender", "男性");                
        set("long", "厉害的哟[2;37;0m
它是红花的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "redflower");
        set("owner_name", "红花");
        set_temp("owner", "redflower");
        set_temp("owner_name", "红花");
        ::setup();
}
