// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m世京[2;37;0m[2;37;0m", ({"gogogo"}));        
        set("gender", "女性");                
        set("long", "$BLK$世京[2;37;0m
它是何为仙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "myjobs");
        set("owner_name", "何为仙");
        set_temp("owner", "myjobs");
        set_temp("owner_name", "何为仙");
        ::setup();
}
