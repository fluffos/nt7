// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m天行者[2;37;0m[2;37;0m", ({"tianxing"}));        
        set("gender", "女性");                
        set("long", "$HIC$天行者[2;37;0m
它是段路的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dckr");
        set("owner_name", "段路");
        set_temp("owner", "dckr");
        set_temp("owner_name", "段路");
        ::setup();
}
