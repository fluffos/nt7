// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神龙翼翼[2;37;0m[2;37;0m", ({"shenlongaaa"}));        
        set("gender", "男性");                
        set("long", "神龙翼翼[2;37;0m
它是神龙号一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shenlongid");
        set("owner_name", "神龙号一");
        set_temp("owner", "shenlongid");
        set_temp("owner_name", "神龙号一");
        ::setup();
}
