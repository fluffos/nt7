// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m火凤凰[2;37;0m[2;37;0m", ({"zhuzhu"}));        
        set("gender", "男性");                
        set("long", "$HIR$火凤凰[2;37;0m
它是开门见山的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "opendoor");
        set("owner_name", "开门见山");
        set_temp("owner", "opendoor");
        set_temp("owner_name", "开门见山");
        ::setup();
}
