// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"dsyb"}));        
        set("gender", "男性");                
        set("long", "$HIR$着是一只火红的朱雀[2;37;0m
它是古墓暗影的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dsya");
        set("owner_name", "古墓暗影");
        set_temp("owner", "dsya");
        set_temp("owner_name", "古墓暗影");
        ::setup();
}
