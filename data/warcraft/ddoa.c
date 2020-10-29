// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m小蛇[2;37;0m[2;37;0m", ({"dragon_a"}));        
        set("gender", "女性");                
        set("long", "$BLK$小蛇[2;37;0m
它是符文一号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ddoa");
        set("owner_name", "符文一号");
        set_temp("owner", "ddoa");
        set_temp("owner_name", "符文一号");
        ::setup();
}
