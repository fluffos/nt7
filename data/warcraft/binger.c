// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火凤凰[2;37;0m[2;37;0m", ({"huofeng"}));        
        set("gender", "女性");                
        set("long", "全身火红的动物[2;37;0m
它是冰儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "binger");
        set("owner_name", "冰儿");
        set_temp("owner", "binger");
        set_temp("owner_name", "冰儿");
        ::setup();
}
