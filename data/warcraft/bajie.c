// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大花猪[2;37;0m[2;37;0m", ({"bajiebb"}));        
        set("gender", "女性");                
        set("long", "大花猪[2;37;0m
它是八戒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bajie");
        set("owner_name", "八戒");
        set_temp("owner", "bajie");
        set_temp("owner_name", "八戒");
        ::setup();
}
