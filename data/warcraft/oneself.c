// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m强[1;36m盗[2;37;0m[2;37;0m", ({"self"}));        
        set("gender", "女性");                
        set("long", "哦[2;37;0m
它是愿藏的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "oneself");
        set("owner_name", "愿藏");
        set_temp("owner", "oneself");
        set_temp("owner_name", "愿藏");
        ::setup();
}
