// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m伍雪[2;37;0m[2;37;0m", ({"matlpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是雪伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matl");
        set("owner_name", "雪伍");
        set_temp("owner", "matl");
        set_temp("owner_name", "雪伍");
        ::setup();
}
