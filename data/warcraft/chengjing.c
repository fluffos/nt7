// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m工作[2;37;0m[2;37;0m", ({"workhood"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$MAG$工作[2;37;0m
它是程静的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chengjing");
        set("owner_name", "程静");
        set_temp("owner", "chengjing");
        set_temp("owner_name", "程静");
        ::setup();
}
