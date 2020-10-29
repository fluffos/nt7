// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIW$白虎[2;37;0m
它是霸刀的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "badao");
        set("owner_name", "霸刀");
        set_temp("owner", "badao");
        set_temp("owner_name", "霸刀");
        ::setup();
}
