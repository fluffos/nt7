// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m泡泡泡沫[2;37;0m[2;37;0m", ({"pao"}));        
        set("gender", "男性");                
        set("long", "三炮大美女[2;37;0m
它是灰烬的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hui");
        set("owner_name", "灰烬");
        set_temp("owner", "hui");
        set_temp("owner_name", "灰烬");
        ::setup();
}
