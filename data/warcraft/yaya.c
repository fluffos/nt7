// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小悠[2;37;0m[2;37;0m", ({"yoyo"}));        
        set("gender", "女性");                
        set("long", "性感的小龙[2;37;0m
它是小雅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yaya");
        set("owner_name", "小雅");
        set_temp("owner", "yaya");
        set_temp("owner_name", "小雅");
        ::setup();
}
