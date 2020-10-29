// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[30m世京[2;37;0m[2;37;0m", ({"solqmago"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$BLK$世京[2;37;0m
它是要夺的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "solqmb");
        set("owner_name", "要夺");
        set_temp("owner", "solqmb");
        set_temp("owner_name", "要夺");
        ::setup();
}
