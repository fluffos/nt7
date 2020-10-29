// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神龙尔尔[2;37;0m[2;37;0m", ({"shenlongbbb"}));        
        set("gender", "男性");                
        set("long", "神龙尔尔[2;37;0m
它是神龙号二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shenlongic");
        set("owner_name", "神龙号二");
        set_temp("owner", "shenlongic");
        set_temp("owner_name", "神龙号二");
        ::setup();
}
