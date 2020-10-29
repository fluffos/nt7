// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m考拉[2;37;0m[2;37;0m", ({"kaola"}));        
        set("gender", "女性");                
        set("long", "考拉[2;37;0m
它是露茜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lucy");
        set("owner_name", "露茜");
        set_temp("owner", "lucy");
        set_temp("owner_name", "露茜");
        ::setup();
}
