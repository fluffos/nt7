// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m翱翔凤凰[2;37;0m[2;37;0m", ({"qmee"}));        
        set("gender", "女性");                
        set("long", "翱翔凤凰[2;37;0m
它是草原清风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qme");
        set("owner_name", "草原清风");
        set_temp("owner", "qme");
        set_temp("owner_name", "草原清风");
        ::setup();
}
