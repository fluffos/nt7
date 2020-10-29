// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("枣红马[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "枣红马[2;37;0m
它是周仓陆的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "btk");
        set("owner_name", "周仓陆");
        set_temp("owner", "btk");
        set_temp("owner_name", "周仓陆");
        ::setup();
}
