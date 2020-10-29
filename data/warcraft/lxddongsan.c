// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("萌虎[2;37;0m[2;37;0m", ({"menghu"}));        
        set("gender", "女性");                
        set("long", "呼呼~ [2;37;0m
它是风冰彤的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lxddongsan");
        set("owner_name", "风冰彤");
        set_temp("owner", "lxddongsan");
        set_temp("owner_name", "风冰彤");
        ::setup();
}
