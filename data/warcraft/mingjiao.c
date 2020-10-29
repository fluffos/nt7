// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是九阳秘籍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mingjiao");
        set("owner_name", "九阳秘籍");
        set_temp("owner", "mingjiao");
        set_temp("owner_name", "九阳秘籍");
        ::setup();
}
