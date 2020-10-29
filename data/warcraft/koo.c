// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m不准打脸[2;37;0m[2;37;0m", ({"gooo"}));        
        set("gender", "男性");                
        set("long", "$HIY$不准打脸[2;37;0m
它是板凳的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "koo");
        set("owner_name", "板凳");
        set_temp("owner", "koo");
        set_temp("owner_name", "板凳");
        ::setup();
}
