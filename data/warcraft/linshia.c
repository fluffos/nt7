// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m粉色妹妹[2;37;0m[2;37;0m", ({"meimei"}));        
        set("gender", "女性");                
        set("long", "人间尤物[2;37;0m
它是肋胃地的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "linshia");
        set("owner_name", "肋胃地");
        set_temp("owner", "linshia");
        set_temp("owner_name", "肋胃地");
        ::setup();
}
